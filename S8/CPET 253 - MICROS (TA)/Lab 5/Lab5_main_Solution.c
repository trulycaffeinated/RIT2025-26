/****************************************************************************************
         CPET253 Lab5 - Servos and Ultrasonic Sensing

 Jeanne Christman
 original version 1/19/2025

 This program uses an ultrasonic sensor to determine when there is an object in front of a
 forward moving robot. Once it is determined that the robot is approaching an object, it backs up,
 stops and then controls a servo motor to sweep the sensor 90 degrees right then 90 degrees left.
 A distance measurement is taken on each sweep. The robot then turns in the direction that is "more
 clear" and continues forward again.

 The servo motor is controlled by a PWM signal from TimerA3. The period of the PWM signal is 20ms
 and the pulse width ranges from 1 ms to 2 ms to control the sweep. The PWM signal is output on
 pin P9.2

 The ultrasonic sensor trigger is connected to pin P6.2 and the echo is connected to pin P6.3. The
 distance measurement is calculated using the width of the pulse returned from the sensor. TimerA2
 is used to determine the duration of the pulse from the sensor.

 Functions in this code:
     -Clock_Init48MHz() - function provided by TI to set system clock
     -Clock_Delay1ms(time) - built in function that delays time ms
     -Clock_Delay1us(time) - built in function that delays time us
     -Port2_Init();
     -Port3_Init();
     -Port5_Init();
     -Port6_Init();
     -Port9_Init();
     -TimerA0_Init();
     -TimerA2_Init();
     -TimerA3_Init();
     -Motor_Forward(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Backward(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Right(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Left(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Stop();

The state machine has 6 states; forward, turn right, turn left, backward, sweep right, sweep left
*******************************************************************************************/

#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/motor.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

#define TRIGGER 0x04
#define ECHO 0x08

#define microsecondsToClockCycles(a) ( (a) * 1.5 )       //assume 12Mhz clock divided by 8
#define clockCyclesToMicroseconds(a) ( (a) / 1.5 )       // 1.5 clock cycles = 1us

void Servo(uint16_t angle);
uint32_t pulseIn (void);


void ServoInit(void)  //This function initializes the servo to be centered (0 degrees)
{
    Servo(4499);     //call Servo() function to center servo
    Clock_Delay1ms(1000);     //delay here to give servo time to move - can use built in timer function
    TA3CTL &= ~0x0030;     //stop the timer
    return;
}
void Servo(uint16_t angle_count)
{
    TA3CCR0 = 59999; //set period for 20ms
    TA3CCR3 = angle_count;      //set high time for the input angle using angle_count
    TA3CTL |= 0x0010;       //set timer for up mode
    return;
}
uint16_t distanceInCm(void) {
    uint16_t distance;

    P6OUT |= TRIGGER;      //drive trigger pin high
    Clock_Delay1us(10);      //wait 10 us - can use built-in timer function
    P6OUT &= ~TRIGGER;      //drive trigger pin low
    distance = (int)(pulseIn()*0.017);      //calculate distance using s=t * 0.034/2. t comes from pulseIn() function
    if (distance == 0) distance = 38000 * 0.017;      // if no echo (distance = 0), assume object is at farthest distance
    return distance;      //return the distance
}
uint32_t pulseIn (void)
{
    uint16_t width = 0;
    uint16_t time = 0;
    uint16_t maxcount = 56999;  //max count for 38 ms (timeout)
    TA2CTL |= 0x0020;           //set timer for continuous mode

    TA2R = 0;                   //reset the count register
    while (!(P6IN & ECHO))                   //wait for the pulse to start (while Echo is low)
        if (TA2R > maxcount)                //if count is greater than maxcount return 0
                return 0;

    TA2R = 0;                   //reset the count register
    while ((P6IN & ECHO))                    //wait for the pulse to finish (while Echo is high)
        if (TA2R > maxcount)                //if count is greater than maxcount return 0
            return 0;;
    
    width = TA2R;               //read the count (width of the return pulse)
    TA2CTL &= ~0x0030;               //stop the timer
    time = clockCyclesToMicroseconds(width);               // convert the reading to microseconds.
    return time;               //return the microsecond reading
}

void main(void)
{

    uint16_t distance, right_wall, left_wall;

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	Clock_Init48MHz();  // makes bus clock 48 MHz
	//call all the port initialization functions
	Port2_Init();
	Port3_Init();
	Port5_Init();
	Port6_Init();
	Port9_Init();
	 //call all the timer initialization functions
	TimerA0_Init();
	TimerA2_Init();
	TimerA3_Init();
	//center the servo using the ServoInit() function
    ServoInit();
	//These are the states of the state machine
	enum motor_states {FORWARD, BACKWARD, RIGHT, LEFT, SERVO_RIGHT, SERVO_LEFT} state, prevState;

	state = FORWARD;          //start in FORWARD state
	prevState = !FORWARD;   //used to know when the state has changed
	uint16_t stateTimer = 0;           //used to stay in a state
	bool isNewState;              //true when the state has switched


	while(1) {

	    isNewState = (state != prevState);
        prevState = state;
	    //distance = distanceInCm();  //this needs to be moved to the states in which it is used
	    switch (state) {
	               case FORWARD:
	                   //entry housekeeping
	                   if (isNewState) {
	                       Motor_Forward(14999,14999) ;
	                   }
	                   //state business
	                   distance = distanceInCm();
	                   //exit condition 1
	                   if (distance < 12) {
	                       state = BACKWARD;
	                   }
	                   break;

	               case BACKWARD:
	                    //entry housekeeping
	                    if (isNewState) {
	                        stateTimer = 0;
	                        Motor_Backward(14999,14999);
	                    }
	                    //state business
	                    stateTimer++;  //increment timer, stay in state for
	                    //exit condition 1
	                    if (stateTimer >= 20) {
	                        state = SERVO_RIGHT;
	                        Motor_Stop();
	                    }
	                    break;
	                case SERVO_RIGHT:
	                    if (isNewState) {
	                        stateTimer = 4500;   //start in center
	                    }
	                    stateTimer -= 25;
	                    Servo(stateTimer);   //do this so servo turns smoothly
	                    if (stateTimer < 1500) {
	                       right_wall = distanceInCm();
	                       ServoInit();       //recenter servo
	                       state = SERVO_LEFT;
	                    }
	                    break;
	               case SERVO_LEFT:
	                    if (isNewState) {
	                        stateTimer = 4500;
	                    }
	                    stateTimer += 25;
	                    Servo(stateTimer);  //smooth transistion
	                    if (stateTimer > 7700) {
	                       left_wall = distanceInCm();
	                       if (left_wall > right_wall) {
	                           state = LEFT;
	                       }
	                       else {
	                           state = RIGHT;
	                       }
	                       ServoInit();  //recenter servo
	                    }
	                    break;
	               case RIGHT:
	                    //entry housekeeping
	                    if (isNewState) {
	                        stateTimer = 0;
	                        Motor_Right(14999,14999);
	                    }
	                    //state business

	                    stateTimer++;  //increment timer, stay in state for
	                    //exit condition 1
	                    if (stateTimer >= 50) {
	                        state = FORWARD;
	                    }
	                    break;
	               case LEFT:
	                   //entry housekeeping
	                   if (isNewState) {
	                      stateTimer = 0;
	                      Motor_Left(14999,14999);
	                   }
	                   //state business

	                   stateTimer++;  //increment timer, stay in state for
	                   //exit condition 1
	                   if (stateTimer >= 50) {
	                      state = FORWARD;
	                   }
	                   break;
	            } //switch */

        Clock_Delay1ms(20);
	} //while
}
