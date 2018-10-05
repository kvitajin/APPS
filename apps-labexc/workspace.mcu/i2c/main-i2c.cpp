// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main programm for I2C bus
//
// **************************************************************************

#include <mbed.h>

#include "i2c-lib.h"
#include "si4735-lib.h"

//************************************************************************

// Direction of I2C communication
#define R	0b00000001
#define W	0b00000000

Serial pc( USBTX, USBRX );

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main( void )
{
	uint8_t S1, S2, RSSI, SNR, MULT, CAP;
	uint8_t ack = 0;

	I2C_Init();

	pc.baud( 115200 );
	pc.printf( "K64F-KIT ready...\r\n" );

	// communication with 8 bit expander PCF8574

	// start communication
	I2C_Start();

	// PCF8574 addressing
	// The address is composed from 3 parts!
	//ack = I2C_Output( HWADR_PCF8574 | A012 | W );

	// Check ack! Return value must be 0!
	// ....

	//ack = I2C_Output( Any_8_bit_value );
	// selected LEDs should light

	// stop communication
	I2C_Stop();

	if ( ( ack = SI4735_Init() ) != 0 )
	{
		pc.printf( "Initialization of SI4735 finish with error (%d)\r\n", ack );
		return 0;
	}
	else
		pc.printf( "SI4735 initialized.\r\n" );
		
	pc.printf( "\nTunig of radio station...\r\n" );
	
	// Required frequency in MHz * 100
	int freq = 10140; // Radiozurnal

	// Tuning of radio station
	I2C_Start();
	ack |= I2C_Output( SI4735_address | W );
	ack |= I2C_Output( 0x20 );			// FM_TUNE_FREQ
	ack |= I2C_Output( 0x00 );			// ARG1
	ack |= I2C_Output( freq >> 8 );		// ARG2 - FreqHi
	ack |= I2C_Output( freq & 0xff );	// ARG3 - FreqLo
	ack |= I2C_Output( 0x00 );			// ARG4
	I2C_Stop();
	// Check ack!
	// if...
	
	// Tuning process inside SI4735
	wait_ms( 100 );
	printf( "... station tuned.\r\n\n" );
	
	// Example of reading of tuned frequency
	I2C_Start();
	ack |= I2C_Output( SI4735_address | W );
	ack |= I2C_Output( 0x22 );			// FM_TUNE_STATUS
	ack |= I2C_Output( 0x00 );			// ARG1
	// repeated start
	I2C_Start();
	// change direction of communication
	ack |= I2C_Output( SI4735_address | R );
	// read data
	S1 = I2C_Input();
	I2C_Ack();
	S2 = I2C_Input();
	I2C_Ack();
	freq = (int) I2C_Input() << 8;
	I2C_Ack();
	freq |= I2C_Input();
	I2C_Ack();
	RSSI = I2C_Input();
	I2C_Ack();
	SNR = I2C_Input();
	I2C_Ack();
	MULT = I2C_Input();
	I2C_Ack();
	CAP = I2C_Input();
	I2C_NAck();
	I2C_Stop();

	if ( ack != 0 ) 
		printf( "Communication error!\r\n" );
	else
		printf( "Current tuned frequency: %d.%dMHz\r\n", freq / 100, freq % 100 );

	return 0;
}



