#include "mbed.h"

Serial pc( USBTX, USBRX );

void demo_leds();
void demo_lcd();
void demo_i2c();

DigitalOut led1( PTA1 );
DigitalOut led2( PTA2 );

DigitalIn but9( PTC9 );
DigitalIn but10( PTC10 );
DigitalIn but11( PTC11 );
DigitalIn but12( PTC12 );

int main()
{
	pc.baud( 115200 );

	// uncomment selected demo
	demo_leds();
	//demo_lcd();
	//demo_i2c();

	// ******************************************************************

	// default demo for 2 LEDs and 4 buttons
	while ( 1 )
	{
		led1 = !led1;		// invert current state
		led2 = !led1;		// blink asynchronously

		wait_ms( 250 );		// delay

		while ( !but9 || !but10 || !but11 || !but12  ); // stop blinking
	}

}
