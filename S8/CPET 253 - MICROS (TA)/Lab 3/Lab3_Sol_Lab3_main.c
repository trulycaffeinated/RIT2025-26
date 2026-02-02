/****************************************************************************************
         CPET253 Lab3 - PWM and Motor Drivers

 Jeanne Christman
 original version 6/1/2022

 This program uses a state machine to control the TI-RSLK robot to drive
 in a pattern of forward, right turn, backward, left turn, forward, right turn, ….. 

 To control the motors on the TI-RSLK robot, there are three outputs that need
 to be driven.
    :Pin    :Description            :Notes
    :=======:=======================:=========================
    : P5.5  : Right motor direction : 0=forwards, 1=backwards
    : P3.6  : Right motor sleep     : 0=sleep, 1=awake
    : P2.6  : Right motor PWM       : 0=stop, PWM signal = go
    : P5.4  : Left motor direction  : 0=forwards, 1=backwards
    : P3.7  : Left motor sleep      : 0=sleep, 1= awake
    : P2.7  : Left motor PWM        : 0=stop, PWM signal = go

 Functions in this code:
     -Clock_Init48MHz() - function provided by TI to set system clock
     -Clock_Delay1ms(time) - built in function that delays time ms
     -Port2_Init();
     -Port3_Init();
     -Port5_Init();
     -TimerA0_Init();
     -MotorForward(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorBackward(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorTurnRight(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorTurnLeft(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 

The state machine has 4 states; forward, right, left, backward
use FSM to make a pattern: Forward, right turn 90 degrees, backwards, left turn 90, forward...
*******************************************************************************************/

#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include "..\inc\Clock.h"
#include "..\inc\CortexM.h"
#include "..\inc\TExaS.h"
#include "..\inc\Init_Ports.h"
#include "..\inc\Init_Timers.h"
#include "..\inc\motor.h"

//Lab3 Optional: Use P2.2-0 as LED outputs
//Declare constants for colored LED
//The LED is controlled by P2.0(red), P2.1(green) and P2.2(blue)
//Make a constant for each RED, GREEN, BLUE and PURPLE
const uint8_t RED = BIT0;
const uint8_t GREEN = BIT1;
const uint8_t BLUE = BIT2;
const uint8_t PURPLE = (BIT0 | BIT2);

//Lab3 Optional:
void LED_Color (uint8_t color) {
   //This is a simple function to turn on the multi-colored LED on the MSP432 Launchpad
   //board according to the argument passed into the function
   //The LED is controlled by bits 0, 1 and 2 on PORT2
   //first turn off all colors
   P2OUT &= ~(BIT0 | BIT1 | BIT2);
   //second turn on the input color
   P2OUT |= color;
}

void main(void)
{


       WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
       Clock_Init48MHz();  // makes bus clock 48 MHz
       TExaS_Init(SCOPE);
       //Call the appropriate functions from Init_Ports.c
       Port2_Init();
       Port3_Init();
       Port5_Init();

       //Call the appropriate functions from Init_Timers.c
       TimerA0_Init();
       //These are the four states of the state machine
       enum motor_states {FORWARD, BACK, LEFT, RIGHT} state, prevState;

       state = FORWARD;           //start state
       prevState = BACK;          //used to know when the state has changed
       uint16_t stateTimer;       //used to stay in a state
       bool isNewState;           //true when the state has switched

       // Call motor forward function generate PWM signal for scope
       // Start with 25% duty cycle
       // Full period = 60,000 counts. 25% = 15,000
       //Motor_Forward(15000, 15000);
       
       while(1)
       {
           isNewState = (state != prevState);
           prevState = state;  //save state for next time

           switch (state) {
                   //each case below should have entry housekeeping, state business and exit housekeeping
                       case FORWARD:
                           // Entry Housekeeping
                           if (isNewState) {
                               LED_Color(GREEN);
                               stateTimer = 0;
                               Motor_Forward(15000, 15000);
                           }
                           // State Business
                           stateTimer++;
                           // Exit Housekeeping
                           if (stateTimer >= 100) { // 1s = 100*10ms
                               state = RIGHT;
                           }
                       break;
                       case RIGHT:
                           // Entry Housekeeping
                           if (isNewState) {
                               LED_Color(BLUE);
                               stateTimer = 0;
                               Motor_Right(15000, 15000);
                           }
                           // State Business
                           stateTimer++;
                           // Exit Housekeeping
                           if (stateTimer >= 150) { // 1.50s = 150*10ms
                               state = BACK;
                           }
                       break;
                       case BACK:
                           // Entry Housekeeping
                           if (isNewState) {
                               LED_Color(RED);
                               stateTimer = 0;
                               Motor_Backward(15000, 15000);
                           }
                           // State Business
                           stateTimer++;
                           // Exit Housekeeping
                           if (stateTimer >= 100) { // 1s = 100*10ms
                               state = LEFT;
                           }
                       break;
                       case LEFT:
                           // Entry Housekeeping
                           if (isNewState) {
                               LED_Color(PURPLE);
                               stateTimer = 0;
                               Motor_Left(15000, 15000);
                           }
                           // State Business
                           stateTimer++;
                           // Exit Housekeeping
                           if (stateTimer >= 150) { // 1.50s = 150*10ms
                               state = FORWARD;
                           }
                       break;
                   } //switch
          Clock_Delay1ms(10);  //10ms delay so that each increment of stateTimer is 10ms
       } //while(1)
   } //main()
