// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LCD module
//
// **************************************************************************

#include "mbed.h"

Serial pc( USBTX, USBRX );

#include "lcd_lib.h"

// two dimensional array with fixed size font
extern uint8_t font8x8[ 256 ][ 8 ];

int main()
{ 
	LCD_init();				// LCD initialization

	LCD_clear();			// LCD clear screen

	int color_red = 0xF800;
	int color_green = 0x07E0;
	int color_blue = 0x001F;
	int color_white = 0xFFFF;

	// simple animation display four color square using LCD_put_pixel function
	int limit = 200;
	for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
		for ( int i = 0; i < limit; i++ )
		{
			LCD_put_pixel( ofs + i,     ofs + 0,     color_red );
			LCD_put_pixel( ofs + 0,     ofs + i,     color_green );
			LCD_put_pixel( ofs + i,     ofs + limit, color_blue );
			LCD_put_pixel( ofs + limit, ofs + i,     color_white );
		}

	return 0;
}
