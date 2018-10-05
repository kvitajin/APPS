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

int main()
{
	// LEDs on K64F-KIT - instances of class DigitalOut
	DigitalOut KIT_LED1( PTA1 );
	DigitalOut KIT_LED2( PTA2 );

	// Button on K64F-KIT - instance of class DigitalIn
	DigitalIn KIT_Button( PTC9 );

    while( 1 )
    {
    	int delay = 500;

    	KIT_LED1 = !KIT_LED1; 	// invert LED1 state

    	if ( KIT_Button == 0 ) 	// button pressed?
    	{
    		delay /= 10;		// speed up blinking
    		KIT_LED2 = !KIT_LED2;
    	}
    	else
    		KIT_LED2 = 0; 		// LED2 off

    	wait_ms( delay );
    }
}
