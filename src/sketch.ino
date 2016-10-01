/* sketch.ino -- main file of ravr-stepper
 *
 * A stepper motor controller
 *
 * Copyright Eetu "Razbit" Pesonen 2016
 */

int stepper_max_pos = 500;

/* Winding pins */
#define C1_1 2
#define C1_2 3
#define C2_1 4
#define C2_2 5

/* limit switch pins */
#define SW1 6
#define SW2 7

/* potentiometer pin */
#define POT A0

#include "stepper.h"
#include "analog.h"

Stepper* stepper;
int stepper_pins[] = {C1_1, C1_2, C2_1, C2_2};
int stepper_pos = 0;
int pot_val;

void setup()
{
	pinMode(SW1, INPUT_PULLUP);
	pinMode(SW2, INPUT_PULLUP);
	stepper = new Stepper(stepper_pins, 20);

	/* Turn the stepper as far ACW as possible, and set it's
	 * relative position to 0 */
	stepper->calibrate(DIR_ACW, SW1, LOW);
	stepper->set_pos(0);
}

void loop()
{
	pot_val = analog_read_tolerance(POT, 10);
	int stepper_target = map(pot_val, 0, 1023, 0, stepper_max_pos);

	if (stepper_target < stepper_pos)
		stepper->step(-1);
	else if (stepper_target > stepper_pos)
	{
		if (digitalRead(SW2) == HIGH)
			stepper->step(1);
		else
			stepper_max_pos = stepper_pos;
	}
	
	stepper_pos = stepper->get_pos();
}
