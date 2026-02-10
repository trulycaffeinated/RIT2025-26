// Init_Timers.c
// Runs on MSP432
// Provide functions that initialize Timers 
// Prof. Christman
// 6/28/2023

/* These functions will be used for labs 3-7 in CPET253

There is an initialization function for each instantiation of TimerA;
TimerA0, TimerA1, TimerA2, TimerA3

*/

#include "msp.h"


// ------------TimerA0_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA0_Init(void){
    // In the TA0CTL register:
    //    Disable timer for initialization
          TA0CTL &= ~0x0030;

    //    Choose a SMCLKclock source
          TA0CTL |= 0x0200; //sets bit 9 as a 1
          TA0CTL &= ~0x0100; //sets bit  8 as a 0
          
    //    Select a clock scaler of 2
          TA0CTL &= ~0x0080; //sets bit 7 as a 0
          TA0CTL |= 0x0040; //sets bit 6 as a 1
    
    //    Enable overflow interrupt if needed
    // In the TA0EX0 register:
    //    Select a second clock scaler if needed
    // For EACH CCRn being used, in the TA0CCTLn register
    //    set the PWM outmode if needed
          TA0CCTL3 |= 0x00E0; //selects compare mode for block 3 - outmode 7
          TA0CCTL4 |= 0x00E0; //selects compare mode for block 4 - outmode 7
    
    //    Enable the CCRn match interrupt if needed
    // For PWM, Load TA0CCR0 with clock counts for desired delay
          TA0CCR0 = 59999; //setting the period to 10 ms
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
  // For PWM, Load TA0CCR0 with clock
  //	counts for desired delay
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
    TA2CTL &= ~0x0030;

  // 	Choose a clock source
    TA2CTL |= 0x0200; //sets bit 9 as a 1
    TA2CTL &= ~0x0100; //sets bit  8 as a 0

  // 	Select a clock scaler if needed
    TA2CTL |= 0x00C0;   //choose clock divider of 8

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
    TA3CTL &= ~0x0030;

  // 	Choose a clock source
    TA3CTL |= 0x0200; //sets bit 9 as a 1
    TA3CTL &= ~0x0100; //sets bit  8 as a 0

  // 	Select a clock scaler if needed
    TA3CTL |= 0x0080;  TA3CTL &= ~0x0040; //choose clock divider of 4

  //    Enable overflow interrupt if needed
  // In the TA3EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA3CCTLn register
  // 	set the PWM outmode if needed
    TA3CCTL3 |= 0x00E0;   //Outmode 7: reset/set
    
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA0CCR0 with clock
  //	counts for desired delay
}
