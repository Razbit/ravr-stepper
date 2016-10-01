/* sketch.ino -- main file of ravr-stepper
 *
 * A stepper motor controller
 *
 * Copyright Eetu "Razbit" Pesonen 2016
 */

/* Pins corresponding to coil wires */
#define C1_1 2
#define C1_2 3
#define C2_1 4
#define C2_2 5

#include "stepper.h"

Stepper* stepper;
int stepper_pins[] = {C1_1, C1_2, C2_1, C2_2};

void setup()
{
	stepper = new Stepper(stepper_pins, 20);
}

void loop()
{
	stepper->step(100);
	delete stepper;
}
