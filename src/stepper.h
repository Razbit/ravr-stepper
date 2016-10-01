/* stepper.h -- a class describing a stepper motor
 *
 * Copyright Eetu "Razbit" Pesonen 2016
 */

#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

#define DIR_ACW 0
#define DIR_CW  1
#define WINDING_1 0
#define WINDING_2 2
#define STATE_W1 WINDING_1 // last time we controlled winding 1
#define STATE_W2 WINDING_2 // last time we controlled winding 2


class Stepper
{
public:
	Stepper(int pins[4], int _delay);
	~Stepper(){};

	void step(int steps);

private:
	int energize(int winding, int dir);
	void de_energize(int winding);
	int m_pins[4];
	int m_state;
	int m_delay;
};

Stepper::Stepper(int pins[4], int _delay)
{
	m_state = STATE_W1;
	m_delay = _delay;
	
	for (int i = 0; i < 4; i++)
		m_pins[i] = pins[i];
}

void Stepper::step(int steps)
{
	if (steps == 0)
		return;
	
	/* if <steps> is negative, turn anti-clockwise */
	int dir = DIR_CW;
	
	if (steps < 0)
	{
		steps = -steps;
		dir = DIR_ACW;
	}

	while (steps > 0)
	{
		m_state = energize((m_state+2)%4, dir);
		steps--;
		delay(m_delay);
	}
}

int Stepper::energize(int winding, int dir)
{
	digitalWrite(m_pins[winding], dir);
	digitalWrite(m_pins[winding+1], ((dir + 1) % 2));
	de_energize((winding+2)%4);

	return winding;
}

void Stepper::de_energize(int winding)
{
	digitalWrite(m_pins[winding], 0);
	digitalWrite(m_pins[winding+1], 0);
}

#endif /* STEPPER_H */
