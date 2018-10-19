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
DigitalIn but9( PTC9 );
DigitalIn but10( PTC10 );
DigitalIn but11( PTC11 );
DigitalIn but12( PTC12 );

#include "i2c-lib.h"
#include "si4735-lib.h"

//************************************************************************

// Direction of I2C communication
#define R	0b00000001
#define W	0b00000000

Serial pc( USBTX, USBRX );

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

class PCF{
public:
	PCF(unsigned char ADDRESS){
		this->address=ADDRESS;
	};
	void write(unsigned char VALUE){
		I2C_Start();
		uint8_t ack = 0;
		ack = I2C_Output( address | W );
		if(ack)
			printf("Nepodarilo se navazat spojeni\r\n");
		else
			printf("Spojeni uspesne navazano\r\n");
		ack = I2C_Output( VALUE );
		if(ack)
			printf("Nepodarilo se ulozit hodnotu\r\n");
		else
			printf("Hodnota uspesne ulozena: %d\r\n",VALUE);
		I2C_Stop();
	}

	//Moje hracka
	void bar2(){

		unsigned char bar=1;
		bool up = true;
		while(true)
		{
			this->write(bar);
			if(up)
				bar=bar+bar+1;
			else
				bar=bar/2;
			if(bar==255)
				up=false;
			if(bar==1)
			{
				wait_ms(200);
				this->write(bar);
				break;
			}
			wait_ms(200);
		}
		//1 = 1. ledka, 3 = 3. ledka
	}

	void bar(unsigned char VALUE){
		unsigned char hodnota=1;
		if(VALUE>=0&&VALUE<=8)
		{
			hodnota = hodnota<<(VALUE-1);
			this->write(hodnota);
		}
		else
		{
			this->write(0);
		}
	}

	unsigned char read(){
		I2C_Start();
		uint8_t ack = 0;
		ack = I2C_Output( address | R );
		unsigned char vysledek=0b0;
		if(ack)
			printf("Nepodarilo se navazat spojeni\r\n");
		else
		{
			vysledek = I2C_Input();
			printf("Hodnota uspesne prectena: %d\r\n",vysledek);
		}

		I2C_Stop();
		return vysledek;
	}
	uint8_t address;
};

class RADIO{
public:
	RADIO(){};
	void setFreq(int freq2=0)
	{
		if(freq2)
			this->freq=freq2;
		I2C_Start();
		ack |= I2C_Output( SI4735_address | W );
		ack |= I2C_Output( 0x20 );			// FM_TUNE_FREQ
		ack |= I2C_Output( 0x00 );			// ARG1
		ack |= I2C_Output( freq2 >> 8 );		// ARG2 - FreqHi
		ack |= I2C_Output( freq2 & 0xff );	// ARG3 - FreqLo
		ack |= I2C_Output( 0x00 );			// ARG4
		I2C_Stop();
		printf( "Current set frequency: %d.%dMHz\r\n", freq / 100, freq % 100 );
	};

	void upFreq(int freq2=10)
	{
		this->freq+=freq2;
		this->setFreq();
	};

	void downFreq(int freq2=10)
	{
		this->freq-=freq2;
		this->setFreq();
	};

	int readFreq()
	{
		uint8_t S1, S2, RSSI, SNR, MULT, CAP;
		int freq3;
		I2C_Start();
		ack |= I2C_Output( SI4735_address | W );
		ack |= I2C_Output( 0x22 );			// FM_TUNE_STATUS
		ack |= I2C_Output( 0x00 );
		I2C_Start();
		// change direction of communication
		ack |= I2C_Output( SI4735_address | R );
		// read data
		S1 = I2C_Input();
		I2C_Ack();
		S2 = I2C_Input();
		I2C_Ack();
		freq3 = (int) I2C_Input() << 8;
		I2C_Ack();
		freq3 |= I2C_Input();
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
			printf( "Current tuned frequency: %d.%dMHz\r\n", freq3 / 100, freq3 % 100 );
	};

	void setVolume(uint8_t VOLUME)
	{
		uint8_t S1, S2, RSSI, SNR, MULT, CAP;
		int freq3;
		I2C_Start();
		ack |= I2C_Output( SI4735_address | W );
		ack |= I2C_Output( 0x12 );
		ack |= I2C_Output( 0x00 );
		ack |= I2C_Output( 0x40 );
		ack |= I2C_Output( 0x00 );
		ack |= I2C_Output( 0x00 );
		ack |= I2C_Output( VOLUME );
		I2C_Stop();
	}

	void FM_SEEK_UP(){
		I2C_Start();
		ack |= I2C_Output( SI4735_address | W );
		ack |= I2C_Output( 0x21 );
		ack |= I2C_Output( 0b00000100 |1<<3);
		I2C_Stop();
		if ( ack != 0 )
			printf( "Communication error!\r\n" );
		else
			printf( "Frekvence vyhledana nahoru\r\n");
	}

	void FM_SEEK_DOWN(){
		I2C_Start();
		ack |= I2C_Output( SI4735_address | W );
		ack |= I2C_Output( 0x21 );
		ack |= I2C_Output( 0b00000100);
		I2C_Stop();
		if ( ack != 0 )
			printf( "Communication error!\r\n" );
		else
			printf( "Frekvence vyhledana dolu\r\n");
	}

	int freq = 10140;
	uint8_t ack = 0;

	// up frek
	// down frek
	// volume
	// dej frekvenci
};

int main( void )
{
	uint8_t S1, S2, RSSI, SNR, MULT, CAP;
	uint8_t ack = 0;

	I2C_Init();

	pc.baud( 115200 );
	pc.printf( "K64F-KIT ready...\r\n" );

	// communication with 8 bit expander PCF8574

	// start communication
	//I2C_Start();

	// PCF8574 addressing
	// The address is composed from 3 parts!
	//ack = I2C_Output( PCF8574 );

	// Check ack! Return value must be 0!
	// ....
	PCF PCF1(0b01001010);

	PCF1.bar(1);
	PCF1.bar(3);
	PCF1.bar(-10);
	PCF1.bar(7);
	ack = PCF1.read();



	//ack = I2C_Output( 0b01010110 );
	// selected LEDs should light

	// stop communication
	//I2C_Stop();

//	if ( ( ack = SI4735_Init() ) != 0 )
//	{
//		pc.printf( "Initialization of SI4735 finish with error (%d)\r\n", ack );
//		return 0;
//	}
//	else
//		pc.printf( "SI4735 initialized.\r\n" );
//
//	pc.printf( "\nTunig of radio station...\r\n" );
	
	// Required frequency in MHz * 100
	//int freq = 10140; // Radiozurnal

	// Tuning of radio station
//	I2C_Start();
//	ack |= I2C_Output( SI4735_address | W );
//	ack |= I2C_Output( 0x20 );			// FM_TUNE_FREQ
//	ack |= I2C_Output( 0x00 );			// ARG1
//	ack |= I2C_Output( freq >> 8 );		// ARG2 - FreqHi
//	ack |= I2C_Output( freq & 0xff );	// ARG3 - FreqLo
//	ack |= I2C_Output( 0x00 );			// ARG4
//	I2C_Stop();
	// Check ack!
	// if...
	
	// Tuning process inside SI4735
//	wait_ms( 100 );
//	printf( "... station tuned.\r\n\n" );
	
	// Example of reading of tuned frequency
//	I2C_Start();
//	ack |= I2C_Output( SI4735_address | W );
//	ack |= I2C_Output( 0x22 );			// FM_TUNE_STATUS
//	ack |= I2C_Output( 0x00 );			// ARG1
	// repeated start
//	I2C_Start();
//	// change direction of communication
//	ack |= I2C_Output( SI4735_address | R );
//	// read data
//	S1 = I2C_Input();
//	I2C_Ack();
//	S2 = I2C_Input();
//	I2C_Ack();
//	freq = (int) I2C_Input() << 8;
//	I2C_Ack();
//	freq |= I2C_Input();
//	I2C_Ack();
//	RSSI = I2C_Input();
//	I2C_Ack();
//	SNR = I2C_Input();
//	I2C_Ack();
//	MULT = I2C_Input();
//	I2C_Ack();
//	CAP = I2C_Input();
//	I2C_NAck();
//	I2C_Stop();
//
//	if ( ack != 0 )
//		printf( "Communication error!\r\n" );
//	else
//		printf( "Current tuned frequency: %d.%dMHz\r\n", freq / 100, freq % 100 );

	//PCF1.bar2();
	int Volume=30;
	int RegVolumeBy=10;
	RADIO *RADIO1 = new RADIO();
	RADIO1->setFreq();
	RADIO1->setVolume(Volume);

	bool pressed9 = false,pressed10 = false,pressed11 = false,pressed12 = false;
	while(true)
	{
		wait_ms(5);
		if(!pressed9&&!but9)
		{
			RADIO1->FM_SEEK_DOWN();
			pressed9 = true;
		}
		else if(but9&&pressed9)
		{
			RADIO1->readFreq();
			pressed9 = false;
		}

		if(!pressed10&&!but10)
		{
			RADIO1->FM_SEEK_UP();
			pressed10 = true;
		}
		else if(but10&&pressed10)
		{
			RADIO1->readFreq();
			pressed10 = false;
		}
		if(!pressed11&&!but11)
		{
			if(Volume+RegVolumeBy>63)
				Volume=63;
			else
				Volume+=RegVolumeBy;
			RADIO1->setVolume(Volume);
			pressed11 = true;
		}
		else if(but11&&pressed11)
		{
			pressed11 = false;
		}
		if(!pressed12&&!but12)
		{
			if(Volume-RegVolumeBy<0)
				Volume=0;
			else
				Volume-=RegVolumeBy;
			RADIO1->setVolume(Volume);
			pressed12 = true;
		}
		else if(but12&&pressed12)
		{
			pressed12 = false;
		}
	}

	return 0;
}


