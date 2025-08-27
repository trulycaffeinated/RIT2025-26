
**Reduced Instruction Set Computer Architecture (RISC)** - its arithmetic and logic operations are performed on operands in the general purpose registers. The data is moved between the memory and these registers by means of Load and Store instructions.

32 Bit wordlength - all registers are 32 bits
It has 32 registers

- Register r0 is referred to as the zero register. It always contains the constant 0. Thus, reading this register returns the value 0, while writing to it has no effect.  
- Register r1 is used by the Assembler as a temporary register; it should not be referenced in user programs  
- Registers r24 and r29 are used for processing of exceptions; they are not available in User mode  
- Registers r25 and r30 are used exclusively by the JTAG Debug module  
- Registers r27 and r28 are used to control the stack used by the Nios II processor  
- Register r31 is used to hold the return address when a subroutine is called