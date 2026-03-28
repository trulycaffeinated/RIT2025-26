// INTERRUPT OCCURS ON P1.1 - LED2 GOES GREEN 1
// INTERRUPT OCCURS ON P1.4 - LED2 GOES BLUE 2

#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include "..\inc\Clock.h"
#include "..\inc\CortexM.h"

#define GREEN BIT1
#define BLUE BIT2

volatile bool isPin1 = false; // was pin1 the interrupt source
volatile bool isPin4 = false; // was pin4 the interrupt source

void Port_Init(void){
    P1DIR &= ~BIT4 & ~BIT1; // initializes p1.4 and p1.1 as inputs
    P1REN |= BIT4 | BIT1; // enable resistors
    P1OUT |= BIT4 | BIT1; // pull-UP resistors
    P1SEL0 &= ~BIT4 & ~BIT1; //general purpose input/output
    P1SEL1 &= ~BIT4 & ~BIT1; //general purpose input/output part 2

    P2DIR |= BIT1 | BIT2; // init p2.1 and p2.2 as outputs
    P2OUT &= ~BIT1 & ~BIT2; //init as zero to show off

    return;
}

void Interrupt_Init(void){
    P1IE |= BIT1 | BIT4; // enables interrupts (set to 1)
    P1IES |= BIT1 | BIT4; // making them falling edge interrupts
    NVIC -> ISER[1] |= 0x08; // 0x08 = 0b1000

    P1IFG &= ~BIT1; //clear flag p1.1
    P1IFG &= ~BIT4; //clear flag p1.4
    EnableInterrupts();
    return;
}

void PORT1_IRQHandler(void){
    //determine which interrupt was thrown - either p1.1 or p1.4
    uint16_t status = P1IV; // P1IV = 2 * ( n + 1 ) where n is the bit number
    // when p1.1 where n is bit 1 ... 2 * ( 1 + 1 ) = 4
    // when p1.4 where n is bit 4 ... 2 * ( 4 + 1 ) = 10
    if(status == 0x04){
        isPin1 = true;
        P1IFG &= ~BIT1;
        return;
    }
    if(status == 0x0A){
        isPin4 = true;
        P1IFG &= ~BIT4;
        return;
    }
}

void main(void){
    // default
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    Clock_Init48MHz();
    // default

    Port_Init();
    Interrupt_Init();

    //do stuff

}