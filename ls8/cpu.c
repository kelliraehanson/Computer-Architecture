#include "cpu.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#define DATA_LEN 6

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

void cpu_load(struct cpu *cpu, char *fileName)
{
    FILE *program_file = fopen(fileName, "r");
    
    if (program_file == NULL)
    {
        printf("** Error! Could not open this program: %s **\n", fileName);
        exit(2);
    }

    int address = 0;
    char line[8000];

    while (fgets(line, sizeof(line), program_file) != NULL)
    {
        char *endptr;
        unsigned char value = strtoul(line, &endptr, 2) & 0xFF;
        if (endptr == line)
        {
            continue;
        }
        cpu_ram_write(cpu, address++, value);
    }

    fclose(program_file);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  unsigned int a = cpu->reg[regA];
  unsigned int b = cpu->reg[regB];

  switch (op) {
    case ALU_MUL:
      // TODO
      cpu->reg[regA] = a * b;
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
    printf("\n");

    // 2. Figure out how many operands this next instruction requires

    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);

    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

switch (IR)
    {
      case LDI: // Load "immediate", store a value in a register, or "set this register to this value
        cpu->reg[operandA] = operandB;
        cpu->PC += 3;
        break;
      
      case PRN:
        // Prints the numeric value stored in the register operandA
        printf("** The numeric value stored in the register operandA: %d **\n", cpu->reg[operandA]);
        cpu->PC += 2;
        break;

      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        cpu->PC += 3;
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
