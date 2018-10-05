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

#ifndef __SI4735_LIB_H
#define __SI4735_LIB_H

#define SI4735_address	0x22
#define INIT_DELAY		100

extern char fm_debug;

char SI4735_Init( void );

#endif // __SI4735_LIB_H

