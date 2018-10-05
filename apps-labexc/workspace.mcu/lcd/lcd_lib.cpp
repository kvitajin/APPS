
// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Programming interface for LCD module
//
// **************************************************************************

#include "mbed.h"

DigitalOut cs( PTC0, 0 );		// chip select
DigitalOut reset( PTC1, 0 );	// reset
DigitalOut rs( PTC2, 0 );		// command/data
DigitalOut bl( PTC3, 0 );		// backlight

// **************************************************************************
// internal functions

#define Nop() { asm( "nop" ); }

// SPI interface
static SPI lcd_spi( PTD2, PTD3, PTD1 );

// write one byte to SPI
void  SPI_write_data( uint8_t Data )
{
	lcd_spi.write( Data );
}

// send command to LCD controller
void  LCD_write_command( uint8_t Data)
{
	cs = 0;
	Nop();
	rs = 0;
	SPI_write_data( Data );
	cs = 1;
}

// send one byte to LCD controller
void  LCD_write_data( uint8_t Data )
{	
	cs = 0;
	Nop();
	rs = 1;
	SPI_write_data( Data );
	cs = 1;
	}

// send two bytes to LCD controller
void  LCD_write_data_16( uint32_t Data )
{
	cs = 0;
	Nop();
	rs = 1;
	SPI_write_data( Data >> 8 );
	SPI_write_data( Data );
	cs = 1;
}

// **************************************************************************
// LCD programming interface

// HW reset of LCD controller
void LCD_reset()
{
    reset = 0;
    wait_ms( 100 );
    reset = 1;
    wait_ms( 100 );
}

// clear screen
void LCD_clear()
{
	LCD_write_command( 0x2c );
	for ( int i = 0; i < 320 * 240; i++ )
       LCD_write_data_16( 0 );
}

// LCD controller initialization
void LCD_init()
{
	// init SPI interface
	lcd_spi.format( 8, 0 );
	lcd_spi.frequency( 20000000 );

	// HW reset of LCD controller
	LCD_reset();

	// backlight ON
	bl = 0;
 
	// initialization sequence... see documentation
    LCD_write_command( 0xCB );
    LCD_write_data( 0x39 );
    LCD_write_data( 0x2C );
    LCD_write_data( 0x00 );
    LCD_write_data( 0x34 );
    LCD_write_data( 0x02 );

    LCD_write_command( 0xCF );
    LCD_write_data( 0x00 );
    LCD_write_data( 0XC1 );
    LCD_write_data( 0X30 );

    LCD_write_command( 0xE8 );
    LCD_write_data( 0x85 );
    LCD_write_data( 0x00 );
    LCD_write_data( 0x78 );

    LCD_write_command( 0xEA );
    LCD_write_data( 0x00 );
    LCD_write_data( 0x00 );
 
    LCD_write_command( 0xED );
    LCD_write_data( 0x64 );
    LCD_write_data( 0x03 );
    LCD_write_data( 0X12 );
    LCD_write_data( 0X81 );

    LCD_write_command( 0xF7 );
    LCD_write_data( 0x20 );
  
    LCD_write_command( 0xC0 );    	//Power control
    LCD_write_data( 0x23 );   		//VRH[5:0]
 
    LCD_write_command( 0xC1 );    	//Power control
    LCD_write_data( 0x10 );   		//SAP[2:0];BT[3:0]

    LCD_write_command( 0xC5 );    	//VCM control
    LCD_write_data( 0x3e );   		//Contrast
    LCD_write_data( 0x28 );
 
    LCD_write_command( 0xC7 );    	//VCM control2
    LCD_write_data( 0x86 );   		//--
 
    LCD_write_command( 0x36 );    	// Memory Access Control
    //LCD_write_data( 0x48 );
    LCD_write_data( 0xE8 );

    LCD_write_command( 0x2A );
    LCD_write_data_16( 0 );
    LCD_write_data_16( 320 - 1 );

    LCD_write_command( 0x2B );
    LCD_write_data_16( 0 );
    LCD_write_data_16( 240 - 1 );

    LCD_write_command( 0x3A );
    LCD_write_data( 0x55 );

    LCD_write_command( 0xB1 );
    LCD_write_data( 0x00 );
    LCD_write_data( 0x18 );
 
    LCD_write_command( 0xB6 );    	// Display Function Control
    LCD_write_data( 0x08 );
    LCD_write_data( 0x82 );
    LCD_write_data( 0x27 );
/* 
    LCD_write_command( 0xF2 );    	// 3Gamma Function Disable
    LCD_write_data( 0x00 );
 
    LCD_write_command( 0x26 );    	//Gamma curve selected
    LCD_write_data( 0x01 );

    LCD_write_command( 0xE0 );    	//Set Gamma
    LCD_write_data( 0x0F );
    LCD_write_data( 0x31 );
    LCD_write_data( 0x2B );
    LCD_write_data( 0x0C );
    LCD_write_data( 0x0E );
    LCD_write_data( 0x08 );
    LCD_write_data( 0x4E );
    LCD_write_data( 0xF1 );
    LCD_write_data( 0x37 );
    LCD_write_data( 0x07 );
    LCD_write_data( 0x10 );
    LCD_write_data( 0x03 );
    LCD_write_data( 0x0E );
    LCD_write_data( 0x09 );
    LCD_write_data( 0x00 );

    LCD_write_command( 0XE1 );    	//Set Gamma
    LCD_write_data( 0x00 );
    LCD_write_data( 0x0E );
    LCD_write_data( 0x14 );
    LCD_write_data( 0x03 );
    LCD_write_data( 0x11 );
    LCD_write_data( 0x07 );
    LCD_write_data( 0x31 );
    LCD_write_data( 0xC1 );
    LCD_write_data( 0x48 );
    LCD_write_data( 0x08 );
    LCD_write_data( 0x0F );
    LCD_write_data( 0x0C );
    LCD_write_data( 0x31 );
    LCD_write_data( 0x36 );
    LCD_write_data( 0x0F );
*/
    LCD_write_command( 0x11 );    	//Exit Sleep
    wait_ms( 120 );
				
    LCD_write_command( 0x29 );    	//Display on
    LCD_write_command( 0x2c );
}

// draw one pixel to LCD screen
void LCD_put_pixel( int x, int y, int color )
{
    LCD_write_command( 0x2A );
    LCD_write_data_16( x );
    LCD_write_data_16( x );

    LCD_write_command( 0x2B );
    LCD_write_data_16( y );
    LCD_write_data_16( y );

    LCD_write_command( 0x2C );

    LCD_write_data_16( color );
}

