/*
BranchPredictorSimulator v1.0: This code simulates a simple branch predictor.
 
Copyright (c) 2015, Texas State University. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted for academic, research, experimental, or personal use provided
that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   * Neither the name of Texas State University nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

For all other uses, please contact the Office for Commercialization and Industry
Relations at Texas State University <http://www.txstate.edu/ocir/>.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Martin Burtscher <burtscher@txstate.edu>
*/


// To Compile " g++ -O3 BranchPredictorSimulator.cpp -o BranchPredictorSimulator"
// To Run "./BranchPredictorSimulator /home/martin/CS3339/test.br.trace 1024"

#include <cstdlib>
#include <cstdio>
#include <cassert>

//Function Prototypes
static void globalPredictor(bool taken);
static void oneBitPredictor(bool taken, unsigned int index);
static void twoBitPredictor(bool taken, unsigned int index);
static void branchTargetBuffer(unsigned int index, unsigned int target);


//Static prediction Variables
static unsigned int branches;
static unsigned int predtakencorrect;

//Global predictor Variables 
static unsigned int gblTakenCorrect; 
static unsigned int gblTakenPreviously;

//One Bit Predictor Variables
static unsigned int oneBitCorrect; 
static unsigned int *oneBitTable;

//Two Bit Predictor Variables
static unsigned int twoBitCorrect; 
static unsigned int *twoBitTable; 

//Branch Target Buffer Variables
static unsigned int btbCorrect; 
static unsigned int *btbTable;



static void initPredictors(unsigned int tabsize)
{
  //Static Branch Initialization
  branches = 0;
  predtakencorrect = 0;

  //Global Predictor Initialization
  gblTakenCorrect = 0;
  gblTakenPreviously = 1; // Flag starts at 1 (taken) before any predictions are made. 

  //One-bit predictor Initialization
  oneBitCorrect = 0; 
  oneBitTable = NULL;
  oneBitTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
    oneBitTable[i] = 1; // Table starts at 1 (taken) before any predictions are made. 

  //Two-bit predictor Initialization
  twoBitCorrect = 0;
  twoBitTable = NULL;
  twoBitTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
      twoBitTable[i] = 2;  // Table starts at 2 (taken) before any predictions are made. 

  //Branch Target Buffer Initialization
  btbCorrect = 0;
  btbTable = NULL;
  btbTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
      btbTable[i] = 0;   // Table starts at 0 (unsure of target) before any predictions are made. 
}

/*
  Global prediction attempts to predict future branches 
  simply by following the previous branch's instruction's behavior.

    * gblTakenPreviously == 1
          -The previous instruction took a jump, we will too
    * gblTakenPreviously == 0
          -The previous instruction didn't jump, we won't either. 

*/
static void globalPredictor(bool taken)
{
  if(gblTakenPreviously == taken)
    gblTakenCorrect++;
  else
    gblTakenPreviously = taken;
}

/*
  One bit prediction works a lot like looking through a history book. 
  The predictor keeps a "table" of previous related instructions predictions 

    -If the value at oneBitTable[index] == taken, history repeats itself 
    and the branch is taken and we've predicted correctly. If they aren't equal
    we have not predicted properly and do not update the counter. 

    -Either way we must update the current [index] in the table to refelect the 
    value of taken that was passed in. 
*/
static void oneBitPredictor(bool taken, unsigned int index)
{
  if(oneBitTable[index] == taken)
    oneBitCorrect++;

  oneBitTable[index] = taken;
}

/*
  Two bit prediction works a lot like a finite state machine.
  Each entry in the "table" contains a the state of a particular
  branch instruction. 

    *The states are as follows:
      (0) - Predict Not Taken
      (1) - Predict Not Taken
      (2) - Predict Taken
      (3) - Predict Taken

  As predictions are made the table constantly updates the current state based on the 
  following rules: 

    -If taken == 1 & the state at oneBitTable[index] is >= 2 
    then we've predicted correctly that we'll be taking the branch
    and we must increment our correct predictions counter. 

    -If taken != 1 & the state at oneBitTable[index] is <= 1
    then we've correctly predicited we won't be taking this particular
    branch and we increment our correct predictions counter. 

    -Regardless, if taken == 1 for a particular branch the state 
    at the [index] must be incremented by 1 (To a max value of 3).
    Conversly, if taken != we must decrement towards a "not taken" 
    state (To a minimum value of 0). Modifying the [index] towards 
    or away from a taken / not taken state serves as a sort of 
    "adaptive prediction". 
  
  Two bit predictors are more accurate when it comes to predicting
  backwards branches of loops. This is because the predictor must be wrong
  twice before the state is shifted away from the dominate state. 
*/
static void twoBitPredictor(bool taken, unsigned int index)
{
  if(taken && (twoBitTable[index] >= 2))
      twoBitCorrect++;
    
  if((!taken && (twoBitTable[index] < 2)))
      twoBitCorrect++;

  if(taken)
  {
    if(twoBitTable[index] < 3)
      twoBitTable[index]++;
  }
  else
  {
    if(twoBitTable[index] > 0)
       twoBitTable[index]--;
  }
}

/*
  Branch Target Buffers (AKA: BTB's) are simple but very accurate 
  form of branch prediction. The Branch Target Buffer works by storing a table
  of PC values (target) and comparing the currently passed PC value (target)
  against the table. 

    -If the current target passed matches the the value contained at the 
    current index in the table. We've predicted correctly and we need to 
    increment our correct predictions counter. 

    -Otherwise, we must update that index to reflect the new target
    so we can make correct predictions in the future. 
*/
static void branchTargetBuffer(unsigned int index, unsigned int target)
{
  if(btbTable[index] == target)
    btbCorrect++;
  else
    btbTable[index] = target;
}

static void predict(unsigned int index, unsigned int target, bool taken)
{
  branches++;
  if (taken) 
    predtakencorrect++; 


  globalPredictor(taken);
  oneBitPredictor(taken, index);
  twoBitPredictor(taken, index); 
  branchTargetBuffer(index, target);
}

static void finiPredictors()
{
  printf("simulated %u branches\n", branches);
  if (branches > 0) 
  {
    printf("correct predict taken: %u (%.1f%%)\n", predtakencorrect, 100.0 * predtakencorrect / branches);
    printf("correct global: %u (%.1f%%)\n", gblTakenCorrect, 100.0 * gblTakenCorrect / branches);
    printf("correct one bit: %u (%.1f%%)\n", oneBitCorrect, 100.0 * oneBitCorrect / branches);
    printf("correct two bit: %u (%.1f%%)\n", twoBitCorrect, 100.0 * twoBitCorrect / branches);
    printf("correct btb: %u (%.1f%%)\n", btbCorrect, 100.0 * btbCorrect / branches);
  }
}

int main(int argc, char* argv[])
{
  printf("Branch Predictor Simulator\n");

  if (argc != 3) 
  {
    printf("usage: %s trace_file table_size\n", argv[0]);
    return -1;
  }

  FILE* f = fopen(argv[1], "rb");  assert(f != NULL);
  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);  assert(size > 0);
  assert((size % (2 * sizeof(unsigned int))) == 0);
  size /= sizeof(int);
  unsigned int *data = new unsigned int[size];
  fseek(f, 0, SEEK_SET);
  size_t length = fread(data, sizeof(unsigned int), size, f);  assert(length == size);
  fclose(f);

  printf("%s contains %lld entries\n", argv[1], (long long)length / 2);

  unsigned int tabsize = atoi(argv[2]);
  if (tabsize == 0) {printf("table_size must be greater than 0\n"); exit(-1);}
  if ((tabsize & (tabsize - 1)) != 0) {printf("table_size must be a power of 2\n"); exit(-1);}

  printf("using a table size of %d entries\n", tabsize);

  initPredictors(tabsize);

  size_t count = 0;
  for (size_t i = 0; i < length; i += 2) {
    unsigned int PC = data[i] >> 1;
    bool taken = data[i] & 1;
    unsigned int target = data[i + 1];

    predict(PC & (tabsize - 1), target, taken);
  }

  finiPredictors();

  delete [] data;
  return 0;
}

