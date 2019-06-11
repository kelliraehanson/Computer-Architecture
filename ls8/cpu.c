#include "cpu.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#define DATA_LEN 6

// ## Step 2: Add RAM functions
// In `cpu.c`, add functions `cpu_ram_read()` and `cpu_ram_write()` that access the
// RAM inside the `struct cpu`.
// We'll make use of these helper function later.

// ### Day 1: Get `print8.ls8` running
// - [ ] Inventory what is here
// - [ ] Implement `struct cpu` in `cpu.h`
// - [ ] Add RAM functions `cpu_ram_read()` and `cpu_ram_write()`
// - [ ] Implement `cpu_init()`
// - [ ] Implement the core of `cpu_run()`
// - [ ] Implement the `HLT` instruction handler
// - [ ] Add the `LDI` instruction
// - [ ] Add the `PRN` instruction

// Add RAM functions `cpu_ram_read()` and `cpu_ram_write()`
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

void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) // Implement the core of `cpu_run()`
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    printf("\n");
    printf("** The value of the current instruction: %u **\n", IR);

    // 2. Figure out how many operands this next instruction requires

    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);

    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

//   This code above requires the implementation of three instructions:
// * `LDI`: load "immediate", store a value in a register, or "set this register to
//   this value".
// * `PRN`: a pseudo-instruction that prints the numeric value stored in a
//   register.
// * `HLT`: halt the CPU and exit the emulator.
switch (IR)
    {
      case LDI:
        cpu->reg[operandA] = operandB;
        cpu->PC += 3;
        break;
      
      case PRN:
        // Prints the numeric value stored in the register operandA
        printf("** The numeric value stored in the register operandA: %d **\n", cpu->reg[operandA]);
        cpu->PC += 2;
        break;

      case HLT:
        running = 0; // False. Was true above. Halt the CPU.
        cpu->PC++;
        break;

      default:
        exit(1); // Exit the emulator.
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
  cpu->PC = 0;
  memset(cpu->reg, 0, 8);
  memset(cpu->ram, 0, 256);
}
