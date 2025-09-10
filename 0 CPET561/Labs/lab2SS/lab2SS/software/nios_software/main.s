# --------------------
# Lab 2
# --------------------

.text

# move 32-bit address into a register
.macro MOVIA reg, addr
  movhi \reg, %hi(\addr)
  ori   \reg, \reg, %lo(\addr)
.endm

# device addresses (from system.h)
.equ HEX0,        0x11000
.equ PUSHBUTTONS, 0x11010
.equ SWITCHES,    0x11020

.global main
main:
  MOVIA r2, HEX0           # HEX0
  MOVIA r3, PUSHBUTTONS   
  MOVIA r4, SWITCHES      

  movi  r5, 0             

  # show initial 0
  MOVIA r6, seg_tab
  add   r6, r6, r5
  ldbu  r7, 0(r6)
  stbio r7, 0(r2)

loop_wait_press:
  ldbuio r8, 0(r3)         # read keys
  andi   r8, r8, 0x02   
  bne    r8, r0, loop_wait_press

  ldbuio r9, 0(r4)         # read switches
  andi   r9, r9, 0x01    
  beq    r9, r0, go_down  

go_up:
  movi   r10, 9
  beq    r5, r10, wrap_up
  addi   r5, r5, 1
  br     do_update
wrap_up:
  movi   r5, 0
  br     do_update

go_down:
  beq    r5, r0, wrap_down
  addi   r5, r5, -1
  br     do_update
wrap_down:
  movi   r5, 9

do_update:
  MOVIA  r6, seg_tab
  add    r6, r6, r5
  ldbu   r7, 0(r6)
  stbio  r7, 0(r2)

wait_release:
  ldbuio r8, 0(r3)
  andi   r8, r8, 0x02
  beq    r8, r0, wait_release
  br     loop_wait_press

.data
seg_tab:
  .byte 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10
