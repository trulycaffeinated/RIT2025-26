/*
 * Jeff Taylor
 * CPET 561
 * Lab 5 Servo Motor
 */

#include "io.h"
#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "sys/alt_irq.h"

typedef unsigned char   uint8;              // unsigned 8 bit values
typedef unsigned short  uint16;             // unsigned 16 bit values
typedef unsigned long   uint32;             // unsigned 32 bit values

uint32 *hex5 = (uint32 *) HEX5_BASE;
uint32 *hex4 = (uint32 *) HEX4_BASE;
uint32 *hex2 = (uint32 *) HEX2_BASE;
uint32 *hex1 = (uint32 *) HEX1_BASE;
uint32 *hex0 = (uint32 *) HEX0_BASE;
volatile uint32 *buttons = (uint32 *) PUSHBUTTONS_BASE;
volatile uint32 *switches = (uint32 *) SWITCHES_BASE;
uint32 *servo = (uint32 *) SERVO_CONTROLLER_0_BASE;

uint32 conv_min;
uint32 conv_max;
volatile uint32 min_angle = 46;
volatile uint32 max_angle = 134;
volatile uint8 update_display = 0;

// hex display
const uint8 SEVEN_SEG[10] = {0x40, 0x79, 0x24, 0x30, 0x19,0x12, 0x02, 0x78, 0x00, 0x10}; // 0-9

int angleConv (int convNum) {

	int count = convNum*(50000/80) + 25000;
	return count;
}


// ISR (KEY)
void pushbutton_ISR(void* context) {

	uint32 button_edge = *(buttons + 3);

    if (button_edge & 0x8) {    // Set min angle
        min_angle = *switches;
    }
    if (button_edge & 0x4) {    // Set max angle
        max_angle = *switches;
    }

    update_display = 1;

    *(buttons + 3) &= 0xFF;  // Clears Interrupt
	button_edge = *(buttons + 3);

}

// ISR (Servo)
void servo_ISR(void* context) {

    conv_min = angleConv(min_angle);
    conv_max = angleConv(max_angle);

    *(servo + 0) = conv_min;   // Write min angle
    *(servo + 1) = conv_max;   // Write max angle
}

// Display Handling

void display_angle() {

	// Min angle hex's
    *hex4 = SEVEN_SEG[min_angle % 10];
    *hex5 = SEVEN_SEG[(min_angle / 10) % 10];

    // Max angle hex's
    *hex0 = SEVEN_SEG[max_angle % 10];
    *hex1 = SEVEN_SEG[(max_angle / 10) % 10];
    *hex2 = SEVEN_SEG[max_angle / 100];
}

int main(void) {

	*(buttons + 2) &= 0x00;
	*(buttons + 2) |= 0x0C;
    *(buttons + 3) &= 0xFF;

    // Register ISRs
    alt_ic_isr_register(PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTONS_IRQ, pushbutton_ISR, 0, 0);
    alt_ic_isr_register(SERVO_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID, SERVO_CONTROLLER_0_IRQ, servo_ISR, 0, 0);

    // Initialize servo angles
    conv_min = angleConv(min_angle);
    conv_max = angleConv(max_angle);

    *(servo + 0) = conv_min;
    *(servo + 1) = conv_max;

	display_angle(); // Init hex's
    while (1) {
        if (update_display) {
			display_angle();
            update_display = 0;
        }
    }

    return 0;
}
