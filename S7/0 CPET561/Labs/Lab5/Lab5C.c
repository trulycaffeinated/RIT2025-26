//-------------------------------------------------------------------------
//-- Ian Woloshyn
//-- CPET 561 Embedded System Design 1
//-- Lab 5 C
//-- March 18th, 2025
//-------------------------------------------------------------------------

#include "io.h"
#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "sys/alt_irq.h"

// Constants and Pointers

typedef unsigned char   uint8;              // unsigned 8 bit values
typedef unsigned short  uint16;             // unsigned 16 bit values
typedef unsigned long   uint32;             // unsigned 32 bit values

volatile uint32 min_angle = 46;
volatile uint32 max_angle = 134;
volatile uint8 update_display = 0;

uint32 *hex5 = (uint32 *) HEX5_BASE;
uint32 *hex4 = (uint32 *) HEX4_BASE;
uint32 *hex2 = (uint32 *) HEX2_BASE;
uint32 *hex1 = (uint32 *) HEX1_BASE;
uint32 *hex0 = (uint32 *) HEX0_BASE;
volatile uint32 *buttons = (uint32 *) PUSHBUTTONS_BASE;
volatile uint32 *switches = (uint32 *) SWITCHES_BASE;
uint32 *servo = (uint32 *) SERVO_CONTROLLER_0_BASE;

// 7-Segment Display

const uint8 SEGMENT_MAP[10] = {
    0x40, 0x79, 0x24, 0x30, 0x19,    // 0-4
    0x12, 0x02, 0x78, 0x00, 0x10     // 5-9
};

// Interrupt Service Routines

void pushbutton_ISR(void* context) {
	
	uint32 button_edge = (*buttons + 3);

    if (button_edge & 0x8) {    // KEY3: Set min angle
        min_angle = *switches;
//        if (min_angle >= 100) min_angle = 99;
    }

    if (button_edge & 0x4) {    // KEY2: Set max angle
        max_angle = *switches;
    }

    update_display = 1;
	
    *(buttons + 3) = 0x00;  // Clears Interrupts

	button_edge = (*buttons + 3);

}

void servo_ISR(void* context) {
	
    *(servo + 0) = angleToDooty(min_angle);   // Write min angle
    *(servo + 1) = angleToDooty(max_angle);   // Write max angle
}

// Display Handling

void display_angle(uint32 value, uint32 *hundreds, uint32 *tens, uint32 *ones) {
    uint8 h = (value >= 100);           // Hundreds digit
    uint8 t = ((value / 10) % 10);     // Tens digit
    uint8 o = value % 10;              // Ones digit

    *ones = SEGMENT_MAP[o];
    *tens = SEGMENT_MAP[t];
    *hundreds = SEGMENT_MAP[h];
}

int angleToDooty (int dooty) {
	
	int count = dooty*(50000/90) + 50000/2;
	return count;
}
	

int main(void) {
    // Register ISRs
    alt_ic_isr_register(PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTONS_IRQ, pushbutton_ISR, 0, 0);
    alt_ic_isr_register(SERVO_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID, SERVO_CONTROLLER_0_IRQ, servo_ISR, 0, 0);

    // Initialize servo angles
    *(servo + 0) = angleToDooty(min_angle);
    *(servo + 1) = angleToDooty(max_angle);

    // Initialize display for angles
		display_angle(min_angle, NULL, hex5, hex4);
		display_angle(max_angle, hex2, hex1, hex0);
	
	*(buttons + 2) = 0x0;
	*(buttons + 2) |= 0x0C;  // Enables interrupts for KEY3 & KEY2 Pushbutton
    *(buttons + 3) = 0x00;  // Clears Interrupts
    


    while (1) {		
        if (update_display) {
			display_angle(min_angle, NULL, hex5, hex4);
			display_angle(max_angle, hex2, hex1, hex0);
            update_display = 0;
        }
    }

    return 0;
}
