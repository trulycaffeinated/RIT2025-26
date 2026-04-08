/****************************************************************************************
         CPET253 Lab8 - IR Reflectance Sensors

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
#include <stdio.h>
#include "..\inc\Clock.h"
#include "..\inc\CortexM.h"
#include "..\inc\Init_Ports.h"
#include "..\inc\Init_Timers.h"
#include "..\inc\motor.h"
#include "..\inc\Reflectance.h"

//Lab8 Optional: Use P2.2-0 as LED outputs
//Declare constants for colored LED
//The LED is controlled by P2.0(red), P2.1(green) and P2.2(blue)
//Make a constant for each RED, GREEN, BLUE and PURPLE
const uint8_t RED = BIT0;
const uint8_t GREEN = BIT1;
const uint8_t BLUE = BIT2;
const uint8_t PURPLE = (BIT2 | BIT0);
const uint8_t TEAL = (BIT2 | BIT1);

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

       //Call the appropriate functions from Init_Ports.c
       Port2_Init();
       Port3_Init();
       Port5_Init();
       Port7_Init();
       Port8_Init();
       Port9_Init();
       Port10_Init();

       //Call the appropriate functions from Init_Timers.c



       TimerA0_Init();

       //These are the three states of the state machine
       enum motor_states {FORWARD, VEER_LEFT, VEER_RIGHT} state, prevState;

       state = FORWARD;         //start state
       prevState = VEER_LEFT;   //used to know when the state has changed
       uint16_t stateTimer;     //used to stay in a state
       bool isNewState;         //true when the state has switched
       uint32_t time_us;        //time delay before reading IR sensors in us
       uint8_t ir_out;          //output for all 8 IR sensors
       int32_t position_10thmm; //position relative to line in 0.1mm units
       
       while(1)
       {
           isNewState = (state != prevState);
           prevState = state;  //save state for next time

           time_us = 1200; // 500us to 2000us
           ir_out = Reflectance_Read(time_us);
           position_10thmm = Reflectance_Position(ir_out);
           //printf("ir_out = %x \n",  ir_out);
           P8OUT = ir_out;  // ir_out[7:4] Had to split due to board connect issues
           P10OUT = ir_out; // ir_out[3:0]

           switch (state) {
                   //each case below should have entry housekeeping, state business and exit housekeeping
                       case FORWARD:
                           // Entry Housekeeping
                           if (isNewState) {
                               Motor_Forward(8000, 8000);
                               LED_Color(GREEN);
                           }
                           // State Business
                           // Exit Housekeeping
                           if (position_10thmm > 48) { // Line on the left
                               state = VEER_LEFT;
                           }
                           if (position_10thmm < -48) { // Line on the right
                               state = VEER_RIGHT;
                           }
                       break;
                       case VEER_RIGHT:
                              // Entry Housekeeping
                              if (isNewState) {
                                  Motor_Forward(4000, 8000); // Slow right motor (rightduty, leftduty)
                                  LED_Color(TEAL);
                              }
                              // State Business
                              // Exit Housekeeping
                              if (position_10thmm >= -48 && position_10thmm <= 48) {
                                  state = FORWARD;
                              }
                              else if (position_10thmm > 48) {
                                  state = VEER_LEFT;
                              }
                        break;
                        case VEER_LEFT:
                              // Entry Housekeeping
                              if (isNewState) {
                                  Motor_Forward(8000, 4000); // Slow left motor (rightduty, leftduty)
                                  LED_Color(PURPLE);
                              }
                              // State Business
                              // Exit Housekeeping
                              if (position_10thmm >= -48 && position_10thmm <= 48) {
                                  state = FORWARD;
                              }
                              else if (position_10thmm < -48) {
                                  state = VEER_RIGHT;
                              }
                          break;
                   } //switch
          Clock_Delay1ms(70);
       } //while(1)
   } //main()
