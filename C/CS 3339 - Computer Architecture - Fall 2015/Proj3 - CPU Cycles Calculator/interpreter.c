/*
1) Note that it initially takes five cycles to start up the pipeline.

2) Assume that no structural hazards exist and that there are no half-cycle register reads or writes

3) Further assume full data forwarding where possible. If forwarding is not possible, insert the minimum
number of bubble cycles (stalls) necessary between the instructions in question until forwarding
works.

4) All instruction inputs are needed at the beginning of the respective stage. Most
instructions need their inputs in the EX stage, except jr, beq, and bne, which need them already in
the ID stage, and the second sw input, which is only needed in the MEM1 stage (the base register is still needed in EX)

5) Do everything from the point of view of the control unit, i.e., in the ID stage. I suggest
calling a function for each source to which you pass the source register number as well as the latest
stage where this input is needed. Similarly, call a function for each instruction to which you pass
the destination register number, if any, as well as the earliest stage in which the result will be
available. Check your results using the following equation: instrs = cycles - 5 - bubbles - flushes
*/

/* 

1) Whenever an instruction needs to read an input
   register, determine, based on the content of the two arrays, whether it will be able to do so in time
    (either from the register file or from the forwarding network) or whether it has to wait, in which
     case the appropriate number of bubbles needs to be inserted.

2) I suggest
calling a function for each source to which you pass the source register number (SOURCE OF INFORMATION RS & RT) as well as the latest
stage where this input is needed. Similarly, call a function for each instruction to which you pass
the destination register number, if any, as well as the earliest stage in which the result will be
available.

*/



#include <stdlib.h>
#include <stdio.h>

#define STAGES 6 // Macro representing the # of stages in the pipeline, Change the num for easy expantion/reduction of the pipeline.                  
#define MEMSIZE 1048576
static int instDest[STAGES] = { 0 };  // Array to store an instructions destination register in regards to the pipeline. 
static int genResult[STAGES] = { 0 }; // Array to strore where an instruction(s) output is available in the pipeline.  
static int numBubbles = 0;
static int numFlushes = 0; 
static int little_endian, icount, *instruction;
static int mem[MEMSIZE / 4];
static int cycles = 5;

static void populatePipeline(int destReg, int OutputAvailable) // Function to populate your pipeline. 
{
  int i; 

  // THE CODE INSIDE YOUR FOR LOOP COULD BE WRONG.
  for(i = 1; i < (STAGES + 1)  ; i++) // The code inside this for loop is used to push data down the pipeline. 
  {
    instDest[STAGES - i] = ((instDest[STAGES - i - 1])); // Your "next" entry (STAGES - i) is now equal to the value behind it (pushing data down the pipeline)
    genResult[STAGES - i] = ((genResult[STAGES - i - 1]) - 1); // Your "next" entry (STAGES - i) is now equal to  the value behind it minus one (Because as you move down the pipeline, your output becomes available sooner) 
  }

  // Once you've pushed your data down the pipeline
  // You're free to add your passed in varables to the start of the array. 
  instDest[0] = destReg;
  genResult[0] = OutputAvailable;
}

void doIStall(int sourceReg, int needInputBy) 
{
  int i;
  int j;
  int bubsToInsert = 0; // int to "dynamically" calculate the # of bubbles to insert. 

    // Add checking to see if dest reg is $zero and then inhibit stalling.
    //printf("The source reg in do I stall is %d \n", sourceReg);

    if(sourceReg == 0)
    {
      return; 
    }
  //printf("The source reg in do I stall is %d \n", sourceReg);
  for(i = 0; i < STAGES; i++)
  {
    if(sourceReg == instDest[i]) // If the src reg is ANOTHER INSTRUCTIONS DEST. 
    {
      if(needInputBy < genResult[i]) // If this instruction needs the input before it's caluclated in the pipeline, stall.
      {
        bubsToInsert = (genResult[i] - needInputBy);
        for(j = 0; j < bubsToInsert; j++)
        {
          populatePipeline(-1, -1); // Call this function again to add "bubbles" to the array. 
        }

        numBubbles += bubsToInsert; // Increment bubbles by the # of bubbles inserted. 
        //printf(" # bubsToInsert is %d \n", bubsToInsert);
        cycles  += bubsToInsert; // If you bubble, you also need to increment your cycles by the # of bubbles. 
        i += bubsToInsert;
      }
    }
  }
}

static int Convert(unsigned int x)
{
  return (x >> 24) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | (x << 24);
}

static int Fetch(int pc)
{
  pc = (pc - 0x00400000) >> 2;
  if ((unsigned)pc >= icount) {
    fprintf(stderr, "instruction fetch out of range\n");
    exit(-1);
  }
  return instruction[pc];
}

static int LoadWord(int addr)
{
  if ((addr & 3) != 0) {
    fprintf(stderr, "unaligned data access\n");
    exit(-1);
  }
  addr -= 0x10000000;
  if ((unsigned)addr >= MEMSIZE) {
    fprintf(stderr, "data access out of range\n");
    exit(-1);
  }
  return mem[addr / 4];
}

static void StoreWord(int data, int addr)
{
  if ((addr & 3) != 0) {
    fprintf(stderr, "unaligned data access\n");
    exit(-1);
  }
  addr -= 0x10000000;
  if ((unsigned)addr >= MEMSIZE) {
    fprintf(stderr, "data access out of range\n");
    exit(-1);
  }
  mem[addr / 4] = data;
}

//  IF(0), ID(1), EX(2), MEM1(3), MEM2(4), and WB(5). (holds the destination reg # of the instruction)
//static int pipelineInstrucDest[6]; //  IF, ID, EX, MEM1, MEM2, and WB. (holds the destination reg # of the instruction)
//static int pipelineResult[6]; // IF, ID, EX, MEM1, MEM2, and WB. (for each instruction in the pipeline, in which stage it generates its result)
static void Interpret(int start) // I CHECK TO SEE IF I NEED TO STALL, THEN I 
{
  int instr, opcode, rs, rt, rd, shamt, funct, uimm, simm, addr;
  int pc, hi, lo;
  int reg[32];
  int cont = 1, count = 0, i; // modify count to start at 5 so you don't need to add the 5 cycles it takes to start the pipeline later. 
  long long wide;


  lo = hi = 0;
  pc = start;
  for (i = 1; i < 32; i++) reg[i] = 0;
  reg[28] = 0x10008000;  // gp
  reg[29] = 0x10000000 + MEMSIZE;  // sp

  while (cont) {
    count++;
    instr = Fetch(pc);
    pc += 4;
    reg[0] = 0;  // $zero

    opcode = (unsigned)instr >> 26;
    rs = (instr >> 21) & 0x1f;
    rt = (instr >> 16) & 0x1f;
    rd = (instr >> 11) & 0x1f;
    shamt = (instr >> 6) & 0x1f;
    funct = instr & 0x3f;
    uimm = instr & 0xffff;
    simm = ((signed)uimm << 16) >> 16;
    addr = instr & 0x3ffffff;
    // I CHECK TO SEE IF I NEED TO STALL, THEN I POPULATE THE PIPELINE. 
    //stallcheck(src reg, input needed by)
    //Populate(rd, stage available)
    //IF(0), ID(1), EX(2), MEM1(3), MEM2(4), WB(5)
      switch (opcode) {
      case 0x00:
        switch (funct) {
          case 0x00: /* sll */reg[rd] = reg[rs] << shamt; doIStall(rs, 2); populatePipeline(rd, 2); break; // added 
          case 0x03: /* sra */ reg[rd] = reg[rs] >> shamt; doIStall(rs, 2); populatePipeline(rd, 2); break; // added
          case 0x08: /* jr */ pc = reg[rs]; doIStall(rs, 1); populatePipeline(-1, -1); numFlushes+=1; break; // added, INPUT NEEDED IN ID STAGE, MUST FLUSH BY 1 CYCLE 
          case 0x10: /* mfhi */ reg[rd] = hi; doIStall(32, 2); populatePipeline(rd, 2); break; // added reg[rd]=hi; 
          case 0x12: /* mflo */ reg[rd] = lo; doIStall(32, 2); populatePipeline(rd, 2); break;
          case 0x18: /* mult */ wide = reg[rs]; wide *= reg[rt]; lo = wide & 0xffffffff; hi = wide >> 32; doIStall(rs, 2); doIStall(rt, 2); populatePipeline(32, 3); break; // RESULT AVAIL IN MEM 1
          case 0x1a: /* div */ if (reg[rt] == 0) {fprintf(stderr, "division by zero: pc = 0x%x\n", pc - 4); cont = 0;} else {lo = reg[rs] / reg[rt]; hi = reg[rs] % reg[rt]; doIStall(rs, 2); doIStall(rt, 2); populatePipeline(32, 5);} break; // RESULT AVAIL IN WB (CANNOT BE FORWARDED)
          case 0x21: /* addu */ reg[rd] = reg[rs] + reg[rt]; doIStall(rs, 2); doIStall(rt, 2); populatePipeline(rd, 2); break; // added reg[rd] = reg[rs] + reg[rt];
          case 0x23: /* subu */ reg[rd] = reg[rs] - reg[rt]; doIStall(rs, 2); doIStall(rt, 2); populatePipeline(rd, 2); break;
          case 0x2a: /* slt */ reg[rd] = (reg[rs] < reg[rt]); doIStall(rs, 2); doIStall(rt, 2); populatePipeline(rd, 2); break; //COME BACK
          default: fprintf(stderr, "unimplemented instruction: pc = 0x%x\n", pc - 4); cont = 0;
        }
        break;
      case 0x02: /* j */ pc = (pc & 0xf0000000) + addr * 4;  populatePipeline(-1, -1);  numFlushes+=1; break; //MUST FLUSH BY 1 CYCLE IF TAKEN
      case 0x03: /* jal */ reg[31] = pc; pc = (pc & 0xf0000000) + addr * 4; populatePipeline(31, 1); numFlushes+=1; break; // RESULT AVAILABLE IN ID STAGE, MUST FLUSH BY 1 CYCLE IF TAKEN
      case 0x04: /* beq */ if(reg[rs] == reg[rt]){pc = pc + simm * 4; numFlushes+=1;} doIStall(rs, 1); doIStall(rt, 1); populatePipeline(-1, -1); break; // Could be pc = (reg[rs] == reg[rt]) ? pc + simm * 4, INPUT NEEDED IN ID STAGE, MUST FLUSH BY 1 CYCLE IF TAKEN
      case 0x05: /* bne */ if(reg[rs] != reg[rt]){pc = pc + simm * 4; numFlushes+=1;} doIStall(rs, 1); doIStall(rt, 1); populatePipeline(-1, -1); break; // Could be pc = (reg[rs] != reg[rt]) ? pc + simm * 4, INPUT NEEDED IN ID STAGE, MUST FLUSH BY 1 CYCLE IF TAKEN
      case 0x09: /* addiu */ reg[rt] = reg[rs] + simm; doIStall(rs, 2); populatePipeline(rt, 2); break;
      case 0x0c: /* andi */ reg[rt] = reg[rs] & uimm; doIStall(rs, 2); populatePipeline(rt, 2); break;
      case 0x0f: /* lui */ reg[rt] = simm << 16; populatePipeline(rt, 2); break; //Found on MIPS Wiki lui can use simm or uimm 
      case 0x1a: /* trap */ //This is already implemented with the switch 
        switch (addr & 0xf) {
          case 0x00: printf("\n"); break;
          case 0x01: printf(" %d ", reg[rs]); doIStall(rs, 2); break; // READS THE REG RS
          case 0x05: printf("\n? "); fflush(stdout); scanf("%d", &reg[rt]); populatePipeline(rt, 2); break; //WRITES REG RT. 
          case 0x0a: cont = 0; break;
          default: fprintf(stderr, "unimplemented trap: pc = 0x%x\n", pc - 4); cont = 0;
        }
        break;
      case 0x23: /* lw */ reg[rt] = LoadWord(reg[rs]  + simm); doIStall(rs, 2); populatePipeline(rt, 4); break;  // call LoadWord function. // RESULT AVAILABLE IN MEM 2
      case 0x2b: /* sw */ StoreWord(reg[rt], reg[rs] + simm); doIStall(rs, 2); doIStall(rt, 3); populatePipeline(-1, -1); break;  // call StoreWord function // SECOND INPUT AVAIL IN MEM 1, BASE REG INPUT IN EX STAGE. 
      default: fprintf(stderr, "unimplemented instruction: pc = 0x%x\n", pc - 4); cont = 0;
    }
  }

  printf("\nprogram finished at pc = 0x%x (%d instructions executed)\n", pc, count);
  printf("The number of cycles is: %d \n", cycles +=count + numFlushes);
  printf("The number of flushes is: %d \n", numFlushes);
  printf("The number of bubbles is: %d \n", numBubbles);
}

int main(int argc, char *argv[])
{
  int c, start;
  FILE *f;

  printf("CS 3339 - MIPS Interpreter\n");
  if (argc != 2) {fprintf(stderr, "usage: %s executable\n", argv[0]); exit(-1);}
  if (sizeof(int) != 4) {fprintf(stderr, "error: need 4-byte integers\n"); exit(-1);}
  if (sizeof(long long) != 8) {fprintf(stderr, "error: need 8-byte long longs\n"); exit(-1);}

  c = 1;
  little_endian = *((char *)&c);
  f = fopen(argv[1], "rb");
  if (f == NULL) {fprintf(stderr, "error: could not open file %s\n", argv[1]); exit(-1);}
  c = fread(&icount, 4, 1, f);
  if (c != 1) {fprintf(stderr, "error: could not read count from file %s\n", argv[1]); exit(-1);}
  if (little_endian) {
    icount = Convert(icount);
  }
  c = fread(&start, 4, 1, f);
  if (c != 1) {fprintf(stderr, "error: could not read start from file %s\n", argv[1]); exit(-1);}
  if (little_endian) {
    start = Convert(start);
  }

  instruction = (int *)(malloc(icount * 4));
  if (instruction == NULL) {fprintf(stderr, "error: out of memory\n"); exit(-1);}
  c = fread(instruction, 4, icount, f);
  if (c != icount) {fprintf(stderr, "error: could not read (all) instructions from file %s\n", argv[1]); exit(-1);}
  fclose(f);
  if (little_endian) {
    for (c = 0; c < icount; c++) {
      instruction[c] = Convert(instruction[c]);
    }
  }

  printf("running %s\n\n", argv[1]);
  Interpret(start);
}
