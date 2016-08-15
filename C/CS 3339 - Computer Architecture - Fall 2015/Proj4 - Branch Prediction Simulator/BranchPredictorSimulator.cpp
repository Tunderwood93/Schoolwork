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
  gblTakenPreviously = 1;

  //One-bit predictor Initialization
  oneBitCorrect = 0; 
  oneBitTable = NULL;
  oneBitTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
    oneBitTable[i] = 1; 

  //Two-bit predictor Initialization
  twoBitCorrect = 0;
  twoBitTable = NULL;
  twoBitTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
      twoBitTable[i] = 2; 

  //Branch Target Buffer Initialization
  btbCorrect = 0;
  btbTable = NULL;
  btbTable = new unsigned int[tabsize];
  for(int i = 0; i < tabsize; i++)
      btbTable[i] = 0;  
}

//DONT UPDATE THE FLAG UNTIL YOU MAKE YOUR PREDICTION
static void predict(unsigned int index, unsigned int target, bool taken)
{
  //////////////////////STATIC BRANCH////////////////////////
  branches++;
  if (taken) 
    predtakencorrect++; 

  //////////////////////GLOBAL BRANCH////////////////////////

  if(gblTakenPreviously == taken)
    gblTakenCorrect++;
  else
    gblTakenPreviously = taken;

  //////////////////////ONE-BIT BRANCH////////////////////////

  if(oneBitTable[index] == taken)
  {
    oneBitCorrect++;
  }
  oneBitTable[index] = taken;

  //////////////////////TWO-BIT BRANCH//////////////////////// greater than 1 & taken == increment, !taken && count < 2 == increment. (can be 6 lines?)

  /*if(taken == 1 && (twoBitTable[index] == 2 || twoBitTable[index] == 3)) // if the val in index is = 2 or = 3 then we're taking the branch. 
  {
    if(twoBitTable[index] != 3)
      twoBitTable[index] = ((twoBitTable[index]) + 1);

    twoBitCorrect++;
  }
  else if(taken == 0 && (twoBitTable[index] == 0 || twoBitTable[index] == 1))
  {
    if(twoBitTable[index] != 0)
      twoBitTable[index] = ((twoBitTable[index]) - 1);

    twoBitCorrect++; // If the function predicts not taken, then it predicted correctly. 
  }
  else
  {
    // FILL ME IN 
  }*/

    if(taken && (twoBitTable[index] >= 2))
    {
      twoBitCorrect++;
    }
    else 
    {
      if((!taken && (twoBitTable[index] < 2)))
      twoBitCorrect++;
    }

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



  //////////////////////BTB BRANCH//////////////////////// Similar to global 

  if(btbTable[index] == target)
  {
    btbCorrect++;
  }
  else
  btbTable[index] = target;
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

