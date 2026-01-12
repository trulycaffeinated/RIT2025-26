
**Reduced Instruction Set Computer Architecture (RISC)** - its arithmetic and logic operations are performed on operands in the general purpose registers. The data is moved between the memory and these registers by means of Load and Store instructions.

32 Bit wordlength - all registers are 32 bits
It has 32 registers

- Register r0 is referred to as the zero register. It always contains the constant 0. Thus, reading this register returns the value 0, while writing to it has no effect.  
- Register r1 is used by the Assembler as a temporary register; it should not be referenced in user programs  
- Registers r24 and r29 are used for processing of exceptions; they are not available in User mode  
- Registers r25 and r30 are used exclusively by the JTAG Debug module  
- Registers r27 and r28 are used to control the stack used by the Nios II processor  
- Register r31 is used to hold the return address when a subroutine is called

Reading or writing to an address that does not correspond to an existing memory or I/O location produces an undefined result

Five addressing modes
- **Immediate mode** – a 16-bit operand is given explicitly in the instruction. This value may be sign extended to produce a 32-bit operand in instructions that perform arithmetic operations.
- **Register mode** – the operand is in a processor register.
- **Displacement mode** – the effective address of the operand is the sum of the contents of a register and a signed 16-bit displacement value given in the instruction.
- **Register indirect mode** – the effective address of the operand is the contents of a register specified in the instruction. This is equivalent to the displacement mode where the displacement value is equal to 0.
- **Absolute mode** – a 16-bit absolute address of an operand can be specified by using the displacement mode with register `r0` which always contains the value 0.

All Nios II instructions are 32 bits long. Nios II also includes a set of *pseudoinstructions* that can be used directly in assembly language programs.

Three instruction formats...

- *I-Type* - Five bit fields A and B are used to specify general-purpose registers. A 16-bit field IMMED16 provides immediate data which can be sign extended to 32-bit operand
- *R-Type* - Five bit fields A,B, and C are used to specify general-purpose registers. An 11-bit field OPX is used to extend the OPX
- *J-Type* - A 26-bit field IMMED26 contains an unsigned immediate value. This format is only in the call instruction.
![[Format of NIOS II Instructions.png]]

#### Instructions
##### Arithmetic
The Nios II instruction set is pretty straightforward, arithmetic is the three letters of the operation, and then i for immediate. Ex...
add is add
add immediate is addi
division is div
division immediate is divi

add registers A and B and store in C

<div align="center">

add rA, rB, rC

</div>

##### Load and Store
Word instructions are abbreviated, see Nios II introduction for full list.
Abbreviations start with either ld for load, or st for store. w for word, b for byte, h for halfword. u is added for unsigned. End with io for i/o

Load halfword unsigned to io --> ldhuio

See Nios II intro for examples on ld and st

##### Logic
Logic instructions come with AND, OR, XOR, and NOR operations. Using them is straightforward. They also come with immediate varients in andi, ori, xori, nori.
AND rA, and rB, store result in rC
<div align="center">
and rC, rA, rB
</div>

These logic operations can also be done with the high modifier. As such...
andh for and high. andhi for and high immediate.

##### Move
The "move" instruction done as mov copys the contents of one register to another.
<div align="center">
mov rC, rA <br>
copies contents of rA to rC
</div>
