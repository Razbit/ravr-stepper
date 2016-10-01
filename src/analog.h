/* Analog.h -- helpers for analog input
 *
 * Copyright Eetu "Razbit" Pesonen 2016
 */

#ifndef ANALOG_H
#define ANALOG_H

#include <Arduino.h>

int analog_read_tolerance(int pin, int tolerance)
{
	int val = analogRead(pin);
	val -= (val % tolerance);

	return val;
}

#endif /* ANALOG_H */
