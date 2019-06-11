#ifndef _CPU_H_
#define _CPU_H_

// This code above requires the implementation of three instructions:

// * `LDI`: load "immediate", store a value in a register, or "set this register to
//   this value".
// * `PRN`: a pseudo-instruction that prints the numeric value stored in a
//   register.
// * `HLT`: halt the CPU and exit the emulator.

// See [the LS-8 spec](../LS8-spec.md) for more details.

// The above program is already hardcoded into the source file `cpu.c`. To run it,
// you will eventually:

// ```
// make
// ./ls8
// ```

// but you'll have to implement those three above instructions first!

// Holds all information about the CPU
struct cpu { // Implement `struct cpu` in `cpu.h`
  // TODO
  // PC
  unsigned int PC;
  // registers (array)
  unsigned char reg[8];
  // ram (array)
  unsigned char ram[256];
  // With 8 bits, our CPU has a total of 256 bytes of memory and can only compute values up to 255.
  // The CPU could support 256 instructions, as well, but we won't need them.
};

// ALU operations
enum alu_op {
	ALU_MUL
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define HLT  0b00000001
#define LDI  0b10000010
#define PRN  0b01000111
#define MUL  0b10100010
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu, char *fileName);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
