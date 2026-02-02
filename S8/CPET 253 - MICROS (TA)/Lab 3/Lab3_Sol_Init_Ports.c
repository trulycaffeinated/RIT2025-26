// Init_Ports.c
// Runs on MSP432
// Provide functions that initialize ports 
// Prof. Christman
// 1/8/2023

/* These functions will be used in all of the labs for CPET253

There is an initialization function for each of the ports 1-10 and J.

The initializations will be different for each lab.
*/

#include "msp.h"


// ------------Port1_Init------------
void Port1_Init(void){

   // Lab1: Make Port1 pins 1 and 4 inputs.
   P1DIR &= ~(BIT1 | BIT4);
   //         0b11101101    0xED

   // Lab1: Enable resistors on Port1 pins 1 and 4.
   P1REN |= (BIT1 | BIT4);
   //        0b00010010    0x12

   // Lab1: Enable pull-up resistors on Port1 pins 1 and 4.
   P1OUT |= (BIT1 | BIT4);
   //        0b00010010   0x12
}

// ------------Port2_Init------------
void Port2_Init(void){

   // Lab3: Enable TimerA0 CCR3 (P2.6 - PWMR) and CCR4 (P2.7 - PWML) Output Channels
   P2SEL1 &= ~(BIT6 | BIT7);
   //        0b00111111   0x3F
   P2SEL0 |= (BIT6 | BIT7);
   //        0b11000000   0xC0
   P2DIR |= (BIT6 | BIT7);
   //        0b11000000   0xC0
   // Lab3 Optional: Use P2.2-0 as LED outputs. All off to start.
   P2DIR |= (BIT2 | BIT1 | BIT0);
   P2OUT &= ~(BIT2 | BIT1 | BIT0);
}

// ------------Port3_Init------------
void Port3_Init(void){
   // Lab3: Make motor sleep controls outputs P3.6 (nSLPR) P3.7 (nSLPL)
   P3DIR |= (BIT6 | BIT7);
   //        0b11000000   0xC0
}

// ------------Port4_Init------------

void Port4_Init(void){
}

// ------------Port5_Init------------
void Port5_Init(void){
   // Lab3: Make motor direction controls outputs P5.6 (DIRR) P5.7 (DIRL)
   P5DIR |= (BIT5 | BIT4);
   //        0b11000000   0xC0
}

// ------------Port6_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port6_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port7_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port7_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port8_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port8_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port9_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port9_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port10_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port10_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------PortJ_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void PortJ_Init(void){
  // Use the port direction register to configure pins as inputs and output
  // 	-A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  // 	-A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}
