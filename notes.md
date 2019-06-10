Computer Architecture: CPU and Components

The Beginning:
    - Transistors, the most basic
    - Gates, mad of transistors
    - Digital Logic common operations preformed by gates
        - AND, OR, NOT, like you've seen in conditionals in code
        - XOR, NOR, NAND
    - Gates can be put together into far more complex structures
        - ALU
        - CPUs

RAM:
    - RAM stands for Random Access Memory.
    - Fast compared to hard drives (and even compared to SSDs)
    - Think of it like abig array of bytes that you can access by index, just like an array in your favorite programming language.
    - Each element in RAM can store on byte, an 8-bit number
    - Larget, mulit-byte values are stored in sequential addresses in RAM
    - The CPU communicates with RAM via the memory bus

CPU words:
    - Bytes of data are stored in RAM(memory)
    - Larger 64-bit (8-byte) numbers, stored sequentially in RAM, that the CPU can operate on at once are called words.
    - The exact number of bytes per wod depends on the architecture
        - 8 bytes for a 64-bit CPU
        - 4 bytes for a 32-bit CPU
        - 1 bytes for an 8-bit CPU

CPU Registers:
Refisters store words that can be accessed at ultra-high-speed
    - Think of them like variables that the CPU has at its disposal.
    - Similar to RAM, except stored directly on the CPU so they are much faster.
    - There are a limited number of them at your disposal, usually 8, 16, or 32, depending on the CPU.
    - They have fixed names, e.g. R0, R1 or EAX, EBX, etc. depending on the CPU.
    - Many CPUs can only perform math operations on registers which must be loaded from RAM first. (The x86 family can often perform math on registers quickly, or RAM  slowly.)

CPU Instructions:
    - Are also stored in RAM with other data.
    - Are actually just numbers.
    - Humans often use mnemonics to refer to the instruction in a human-readable way.
    - The CPU keeps track of the address of the currently-executing instruction in RAM and preforms different actions based on the instructoin found there.
    - The address of the currently-executing instrucion is held in a special register called the program counter (PC)
    - CPUs usually have a significant number of instructions, around 50-200

CPU Clock:
    - The clock in a modern CPU triggers a few billion times per second.
    - Clock cycle rate is measured in Hz, KHz, MHz, or GHz (billions of cycles per second)
    - Each instruction takes one or more clock cycles to execute.
    - The faster the clock, the more instructions can execute per second. 

Concurrency:
How the CPU does more than one thing at once.
    - Each hardware component can only do one thing at once.
    - Duplicate the hardware components!
    - Multi-core CPUs
    - Pipelining
    - Timesharing 

System Bus:
How data is passed from the CPU to RAM, and from the CPU to peripherals.
    - Address Bus: carries the address in RAM we're interested in, or the peripheral ID we're interested in. 
    - Data Bus: carries data to be transmitted to or from RAM or peripherals.
    - Control Bus: controls whether or not the CPU is talking to RAM or peripheral.
    - The size or width of the bus is typically the number of "bits" a computer is advertised having. A 63-bit CPU has a 64-bit wide data bus, and usually a 64-bit wide address bus. 

Caching:
    - Access to RAM is relative slow.
    - Access to Registers is fast
    - Middle ground? Cache.
    - Closer to the CPU
    - Usually arranged in a level hierarchy
    - Cache Miss means you're trying to access memory that is not ye tin the cache.
    - Cache Hit means the memory you want is in the cache already. 
