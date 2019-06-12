#include "cpu.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) 
{
  return cpu->ram[address];
}
void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) 
{
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

void cpu_load(struct cpu *cpu, char *fileName)
{
  // file pointer
  FILE *fp;
  int address = 0;
  char line[1000];

  fp = fopen(fileName, "r");
  if(fp == NULL) 
    {
        printf("** Error! Could not open this program: %s **\n", fileName);
        exit(1);
    }

  while (fgets(line, sizeof(line), fp) != NULL) { // loop until fgets is at the end of the file
    char *endptr;
    unsigned char value = strtoul(line, &endptr, 2); // cast line to binary until value is captured
    
    if (endptr == line) {
      continue;
    }

    cpu_ram_write(cpu, address++, value); // write value to RAM @address
  }

      fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] *= cpu->reg[regB];
      break;

    case ALU_ADD:
      cpu->reg[regA] += cpu->reg[regB];
      break;

    default:
      printf("** Error! Looks like there was no instruciton for ALU provided. **\n");
      break;
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) // Implement the core of `cpu_run()`
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC); // Read instructions from RAM
    // printf("** The value of the current instruction: %u **\n", IR);

    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1); // Read additional operands 
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2); // Read additional operands 

    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

int number_of_operands = (IR >> 4) & 1;
switch (IR)
    {
      case LDI: // Load "immediate", store a value in a register, or "set this register to this value
        cpu->reg[operandA] = operandB;
        break;
      
      case PRN:
        // Prints the numeric value stored in the register operandA (prints register)
        printf("** The numeric value stored in the register operandA: %d **\n", cpu->reg[operandA]);
        break;

      case MUL:
        // Call the ALU to execute MUL instruction
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        break;

      case PUSH:
        cpu->sp--;
        cpu_ram_write(cpu, cpu->sp, cpu->reg[operandA]);
        break;

      case POP:
        if(cpu->sp == 244)
        fprintf(stderr, "** Error! You ca not pop off an empty stack! **\n");
        cpu->reg[operandA] = cpu_ram_read(cpu, cpu->sp++);
        break;

      case HLT:
        running = 0; // Halt. (False. Was true above.) Halt the CPU.
        break;

      default:
        printf("** Error! Unknown instruction at %02x: %02x **\n", cpu->PC, IR);
        exit(1); // Exit the emulator.
    }

    if (!number_of_operands) {
      cpu->PC += ((IR >> 6) & 0x3) + 1;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu) // Implement `cpu_init()`
{
  // TODO: Initialize the PC and other special registers
  cpu = malloc(sizeof(struct cpu));
  cpu->sp = 244;
  cpu->PC = 0;
  memset(cpu->reg, 0, 8);
  memset(cpu->ram, 0, 256);
}

// ## Step 11: Implement System Stack

// All CPUs manage a _stack_ that can be used to store information temporarily.
// This stack resides in main memory and typically starts at the top of memory (at
// a high address) and grows _downward_ as things are pushed on. The LS-8 is no
// exception to this.

// Implement a system stack per the spec. Add `PUSH` and `POP` instructions. Read
//   the beginning of the spec to see which register is the stack pointer. 
  
// * Values themselves should be saved in the ***portion of RAM*** _that is allocated for the stack_. 
//   -  Use the stack pointer to modify the correct block of memory. 
//   - Make sure you update the stack pointer appropriately as you `PUSH` and `POP` items to and from the stack.

// If you run `./ls8 examples/stack.ls8` you should see the output:

// ```
// 2
// 4
// 1
// ```