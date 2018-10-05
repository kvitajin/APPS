// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         I2C bus programming interface
//
// **************************************************************************

#include <mbed.h>
//#include <stdio.h>

#include "i2c-lib.h"

//************************************************************************
// I2C bus (low level) - signals SDA & SCL control

DigitalInOut SDA( PTC1, PIN_OUTPUT, PullNone, 1 );
DigitalInOut SCL( PTC0, PIN_OUTPUT, PullNone, 1 );

void _I2C_delay() { wait_us( 100 ); }

// set signal SDA
void _I2C_SDA( uint8_t value )
{
	SDA = value != 0;
	//if ( value ) I2C_PORT |= ( 1 << SDA_PIN );
	//else         I2C_PORT &= ~( 1 << SDA_PIN );
	 _I2C_delay();
}

// read signal SDA
uint8_t _I2C_getSDA( void )
{
	uint8_t r = 0;
	_I2C_delay();
	return r;
}

// set signal SCL
void _I2C_SCL( uint8_t value )
{
	SCL = value != 0;
	_I2C_delay();
}

//************************************************************************
// Principle of I2C communication is described in datasheets of all I2C
// integrated circuits

// I2C initialization
void I2C_Init( void )
{
	SDA.output();
	SDA.mode( PullNone );
	SDA = 1;
	SCL.output();
	SCL.mode( PullNone );
	SCL = 1;

	I2C_Start();
	I2C_Stop();
}

// Start communication on I2C
void I2C_Start( void )
{
	_I2C_SDA( 1 );
	_I2C_SCL( 1 );
	_I2C_SDA( 0 );
	_I2C_SCL( 0 );
}

// Stop communication on I2C
void I2C_Stop( void )
{
	_I2C_SCL( 0 );
	_I2C_SDA( 0 );
	_I2C_SCL( 1 );
	_I2C_SDA( 1 );
}

// Send ACK bit
void I2C_Ack( void )
{
	_I2C_SCL( 0 );
	_I2C_SDA( 0 );
	_I2C_SCL( 1 );
	_I2C_SCL( 0 );
}

// Send NACK bit
void I2C_NAck( void )
{
	_I2C_SCL( 0 );
	_I2C_SDA( 1 );
	_I2C_SCL( 1 );
	_I2C_SCL( 0 );
}

// get ACK
uint8_t I2C_getACK( void )
{
	SDA = 1;
	SDA.input();
	_I2C_SCL( 1 );
	uint8_t ret = SDA;
	_I2C_SCL( 0 );
	SDA.output();
	return ret;
}

// Send one byte to I2C bus
uint8_t I2C_Output( uint8_t value )
{
	uint8_t mask = 0x80;
	// send 8 bits, MSB first
	for ( int i = 0; i < 8; i++ )
	{
		_I2C_SDA( value & mask );
		 mask >>= 1;
		_I2C_SCL( 1 );
		_I2C_SCL( 0 );
	}
	return I2C_getACK();
}

// Receive one byte from I2C bus
uint8_t I2C_Input( void )
{
	uint8_t value = 0;
	// quiet state on SDA line
	SDA = 1;

	// set SDA pin to input
	SDA.input();

	// read 8 bits, MSB first
	for ( int i = 0; i < 8; i++ )
	{
		value <<= 1;
		_I2C_SCL( 1 );
		if ( SDA ) value |= 1;
		_I2C_SCL( 0 );
	}

	// set SDA pin to output
	SDA.output();

	return value;
}

