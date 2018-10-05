/*
 * ledPanel.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: mic0357
 */

#include <ledPanel.h>
#include "mbed.h"

LedPanel::LedPanel() {
	// TODO Auto-generated constructor stub

}

LedPanel::~LedPanel() {
	// TODO Auto-generated destructor stub
}

void LedPanel::shiftLeds() {
	DigitalOut LEDS[8] = {PTC0, PTC1, PTC2, PTC3, PTC4, PTC5, PTC7, PTC8};
	int delay = 500;
	int f, s, t;
	DigitalIn btn1( PTC10 );
	DigitalIn btn2( PTC11 );
	DigitalIn btn3( PTC12 );

	while(1) {

		for (int i = 0; i < 8; i++) {
			f = i;
			s = i + 1;
			t = i + 2;
			if (s > 7) s -= 8;
			if (t > 7) t -= 8;

			LEDS[f] = !LEDS[f];
			LEDS[s] = !LEDS[s];
			LEDS[t] = !LEDS[t];

			if (!btn1) {
				delay = 200;
			}
			if (!btn2) {
				delay = 500;
			}
			if (!btn3) {
				delay = 1000;
			}

			wait_ms(delay);

			if (!btn1) {
				delay = 200;
			}
			if (!btn2) {
				delay = 500;
			}
			if (!btn3) {
				delay = 1000;
			}

			LEDS[f] = !LEDS[f];
			LEDS[s] = !LEDS[s];
			LEDS[t] = !LEDS[t];

		}
	}
}
