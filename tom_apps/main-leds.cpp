// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LEDs
//
// **************************************************************************

#include "mbed.h"
#include "ledPanel.h"
//using namespace std;



int main()
{
	// LEDs on K64F-KIT - instances of class DigitalOut
	DigitalOut KIT_LED1( PTA1 );
	DigitalOut KIT_LED2( PTA2 );

	// Upper LEDs


	// Button on K64F-KIT - instance of class DigitalIn
	DigitalIn KIT_Button( PTC9 );

	LedPanel leds;
	leds.shiftLeds();

}
