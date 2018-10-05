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
#ifndef __I2C_LIB_H
#define __I2C_LIB_H

#include <mbed.h>
#include <stdio.h>
//#include <avr/io.h>

// ***********************************************************************

// Pins of SCL and SDA lines
#define SCL_PIN PTC7
#define SDA_PIN PTC5

// Prototypes of all I2C functions


// set signal SDA
void _I2C_SDA( uint8_t value );

// read signal SDA
uint8_t _I2C_getSDA( void );

// set signal SCL
void _I2C_SCL( uint8_t value );

// I2C initialization
void I2C_Init( void );

// Start communication on I2C
void I2C_Start( void );

// Stop communication on I2C
void I2C_Stop( void );

// Send ACK bit
void I2C_Ack( void );

// Send NACK bit
void I2C_NAck( void );

// get ACK
uint8_t I2C_getACK( void );

// Send one byte to I2C bus
uint8_t I2C_Output( uint8_t value );

// Receive one byte from I2C bus
uint8_t I2C_Input( void );

#endif //  __I2C_LIB_H
