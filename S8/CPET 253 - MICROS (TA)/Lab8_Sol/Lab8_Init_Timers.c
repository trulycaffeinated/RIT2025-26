// Init_Timers.c
// Runs on MSP432
// Provide functions that initialize Timers 
// Prof. Christman
// 6/28/2023

/* These functions will be used for labs 3-8 in CPET253

There is an initialization function for each instantiation of TimerA;
TimerA0, TimerA1, TimerA2, TimerA3

*/

#include "msp.h"


// ------------TimerA0_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler
//
// Lab 3: Find smallest N
//        N = (Elapsed Time*Clock Frequency)/clock counts
//        N = (10ms*12MHz)/65,535
//        N = (0.010s*12,000,000Hz)/65,535
//        N = 1.83 -> Round up to 2
//        Find count which produces 10ms elapsed time with N = 2
//        clock counts = (Elapsed Time*Clock Frequency)/N
//        clock counts = (10ms*12MHz)/2
//        clock counts = (0.010s*12,000,000Hz)/2
//        clock counts = 60,000 -> Becomes CCR0 compare value in up mode

// Input: none
// Output: none
void TimerA0_Init(void){
  // Lab 3: In the TA0CTL register:
  // 	Disable timer for initialization - MC(5-4) == 0b00
  TA0CTL &= ~(BIT5 | BIT4);
  //        0b1111111111001111 0xFFCF ~0x0030
  // 	Choose a clock source - SMCLK - TASSEL(9-8) = 0b10
  TA0CTL &= ~(BIT8);
  //        0b1111111011111111 0xFEFF ~0x0100
  TA0CTL |= BIT9;
  //        0b0000001000000000 0x0200
  // 	Select clock scaler /2 - ID (7-6) = 0b01
  TA0CTL &= ~(BIT7);
  //        0b1111111101111111 0xFF7F ~0x0080
  TA0CTL |= BIT6;
  //        0b0000000001000000 0x0040
  // Lab 3: In the TA0EX0 register:
  //    N/A - Select a second clock scaler if needed
  // Lab 3: For EACH CCRn being used, in the TA0CCTLn register
  // 	set the PWM out mode to Reset/set - OUTMOD(7-5) = 0b111
  TA0CCTL3 |= (BIT7 | BIT6 | BIT5);
  TA0CCTL4 |= (BIT7 | BIT6 | BIT5);
  //
  // Lab 3: For PWM, Load TA0CCR0 with clock
  //	counts for desired period 10ms -> 60,000 counts
  TA0CCR0 = 59999;
}

// ------------TimerA1_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA1_Init(void){
  // In the TA1CTL register:
  // 	Disable timer for initialization
  // 	Choose a clock source
  // 	Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA1EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA1CCTLn register
  // 	set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA1CCR0 with clock
  //	counts for desired period
}

// ------------TimerA2_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA2_Init(void){
  // In the TA2CTL register:
  // 	Disable timer for initialization
  // 	Choose a clock source
  // 	Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA2EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA2CCTLn register
  // 	set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA2CCR0 with clock
  //	counts for desired period
}

// ------------TimerA3_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA3_Init(void){
  // In the TA3CTL register:
  // 	Disable timer for initialization
  // 	Choose a clock source
  // 	Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA3EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA3CCTLn register
  // 	set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA3CCR0 with clock
  //	counts for desired period
}
