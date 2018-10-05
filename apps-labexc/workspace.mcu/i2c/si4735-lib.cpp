// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         FM/AM Radiomodule SI4735 with I2C interface
//
// **************************************************************************

//#include "../avrkit/avrkit.h"
#include "i2c-lib.h"
#include "si4735-lib.h"

//#include <stdio.h>
//#include <avr/io.h>

char fm_debug = 0;

static void fm_print( const char *msg )
{
	if ( fm_debug ) printf( msg );
}

static char fm_check( char ack )
{
	if ( ack != 1 ) 
		fm_print( "- OK\n" );
	else
		fm_print( "- Error\n" );
	return ack;
}

char SI4735_Init( void )
{
	char ack = 0;
	fm_print( "----- Si4735 Init Started ------\n" );

	fm_print( " Power Down                " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x11 );			// power down
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 1;

	fm_print( " Init FM                   " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x01 );			// power up
	ack |= I2C_Output( 0x10 );			// set crystal 32KHz
	ack |= I2C_Output( 0x05 );			// set analog output
	I2C_Stop();
	
	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 2;

	fm_print( " FM antenna input          " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 );			// set property
	ack |= I2C_Output( 0x00 );			// set property

	ack |= I2C_Output( 0x11 );
	ack |= I2C_Output( 0x07 );

	ack |= I2C_Output( 0x00 );
	ack |= I2C_Output( 0x00 );
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 3;

	fm_print( " FM Deemphasis             " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 );			// set property
	ack |= I2C_Output( 0x00 );			// set property

	ack |= I2C_Output( 0x11 );
	ack |= I2C_Output( 0x00 );

	ack |= I2C_Output( 0x00 );
	ack |= I2C_Output( 0x01 );
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 4;

	fm_print( " Freq. Spacing 5kHz        ");
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 );			// set property
	ack |= I2C_Output( 0x00 );			// set property

	ack |= I2C_Output( 0x14 );
	ack |= I2C_Output( 0x02 );

	ack |= I2C_Output( 0x00 );
	ack |= I2C_Output( 0x05 );
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 5;

	fm_print( " Init RDS(1)               " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 ); //set property
	ack |= I2C_Output( 0x00 ); //set property

	ack |= I2C_Output( 0x15 ); //RDS_CONFIG
	ack |= I2C_Output( 0x02 ); //RDS_CONFIG

	ack |= I2C_Output( 0xAA ); //err.corectable
	ack |= I2C_Output( 0x01 ); //err.corectable
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 6;

	fm_print( " Init RDS(2)               " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 ); //set property
	ack |= I2C_Output( 0x00 ); //set property

	ack |= I2C_Output( 0x15 ); //RDS_CONFIG
	ack |= I2C_Output( 0x00 ); //RDS_CONFIG

	ack |= I2C_Output( 0x00 ); //err.corectable
	ack |= I2C_Output( 0x00 ); //err.corectable
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 7;

	fm_print( " Init RDS(3)               " );
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x12 ); //set property
	ack |= I2C_Output( 0x00 ); //set property

	ack |= I2C_Output( 0x15 ); //RDS_CONFIG
	ack |= I2C_Output( 0x01 ); //RDS_CONFIG

	ack |= I2C_Output( 0x00 ); //err.corectable
	ack |= I2C_Output( 0x00 ); //err.corectable
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 8;

	fm_print( " Set property              ");
	I2C_Start();
	ack |= I2C_Output( SI4735_address );
	ack |= I2C_Output( 0x20 );
	ack |= I2C_Output( 0x00 );

	ack |= I2C_Output( 0x27 );
	ack |= I2C_Output( 0x10 );

	ack |= I2C_Output( 0x00 );
	ack |= I2C_Output( 0x00 );
	I2C_Stop();

	wait_ms( INIT_DELAY );
	if ( fm_check( ack ) ) return 9;

	I2C_Start();
	I2C_Output( SI4735_address );
	I2C_Output( 0x12 );
	I2C_Output( 0x00 );
	I2C_Output( 0x40 );
	I2C_Output( 0x00 );
	I2C_Output( 0x00 );
	I2C_Output( 0x20 );					// hlasitost 32
	I2C_Stop();

	fm_print( "----- Si4735 Init Done ---------\n" );

	return 0;
}
