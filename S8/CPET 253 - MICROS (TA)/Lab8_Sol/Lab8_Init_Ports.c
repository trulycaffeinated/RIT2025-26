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
}

// ------------Port2_Init------------
void Port2_Init(void){

   // Lab3: Enable TimerA0 CCR3 (P2.6 - PWMR) and CCR4 (P2.7 - PWML) Output Channels
   P2SEL1 &= ~(BIT6 | BIT7);// 0b00111111 0x3F
   P2SEL0 |= (BIT6 | BIT7); // 0b11000000 0xC0
   P2DIR |= (BIT6 | BIT7);  // 0b11000000 0xC0
   // Lab8 Optional: Use P2.2-0 as LED outputs. All off to start.
   P2DIR |= (BIT2 | BIT1 | BIT0);
   P2OUT &= ~(BIT2 | BIT1 | BIT0);
}

// ------------Port3_Init------------
void Port3_Init(void){
   // Lab3: Make motor sleep controls outputs P3.6 (nSLPR) P3.7 (nSLPL)
   P3DIR |= (BIT6 | BIT7); // 0b11000000 0xC0
   // Initialize the outputs to 0
   P3OUT &= ~(BIT6 | BIT7); //0b00111111 0x3F
}

// ------------Port4_Init------------

void Port4_Init(void){
}

// ------------Port5_Init------------
void Port5_Init(void){
   // Lab3: Make motor direction controls outputs P5.6 (DIRR) P5.7 (DIRL)
   // Lab8: Make IR reflectance sensor control even pin an output (P5.3)
   P5DIR |= (BIT5 | BIT4 | BIT3);  //0b00111000  0x38
   // Initialize the outputs to 0
   P5OUT &= ~(BIT5 | BIT4 | BIT3); //0b11000111 0xC7
}

// ------------Port6_Init------------
void Port6_Init(void){

}

// ------------Port7_Init------------
void Port7_Init(void){
    // Lab8: Make IR reflectance sensor cap pins inputs (P7.7 - P7.0)
    P7DIR &= 0x00;
}

// ------------Port8_Init------------
void Port8_Init(void){
    // Lab8: Extra - Output IR Sensor results 7-4
    P8DIR |= 0xF0;
    P8OUT &= 0x0F;
}

// ------------Port9_Init------------
void Port9_Init(void){
    // Lab8: Make IR reflectance sensor control odd an output (P9.2)
    P9DIR |= (BIT2);
    //        0b00000100   0x04

}

// ------------Port10_Init------------
// First set the pin directions

void Port10_Init(void){
    // Lab8: Extra - Output IR Sensor results 3-0
    P10DIR |= 0x0F;
    P10OUT &= 0xF0;
}

// ------------PortJ_Init------------
void PortJ_Init(void){

}
