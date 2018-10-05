

#include "mbed.h"
#define JUMP 10
// LEDs on K64F-KIT - instances of class DigitalOut
	DigitalOut KIT_LED1( PTA1 );
	DigitalOut KIT_LED2( PTA2 );

	// Button on K64F-KIT - instance of class DigitalIn
	DigitalIn butt[4]={PTC9, PTC10, PTC11, PTC12};
	Serial pc( USBTX, USBRX );
	DigitalOut rgbL[3]={PTB2, PTB3, PTB9};
	DigitalOut rgbH[3]={PTB11, PTB18, PTB19};
	DigitalOut leds[8]={PTC0,PTC1, PTC2, PTC3, PTC4, PTC5, PTC7, PTC8};

/*void sleep(int timeOn, int timeOff){
	KIT_LED1=1;
	wait_ms(timeOn);
	KIT_LED1=0;
	wait_ms(timeOff);
}*/
bool flag=0;
int stav=0;
int rh=0, gh=10, bh=0, rl=0, gl=100, bl=0;


bool stisk(DigitalIn *butt){
    if (!*butt){
		while(true){pc.baud( 115200 );

			if(!*butt){
			flag=!flag;
			return true;
			pc.printf("RH: %d \nGH: %d \nBH: %d\n\nRL: %d \nGL: %d \nBL:%d", rh, gh, bh, rl, gl, bl);
			}
		}
    }
	pc.printf("o kurwa");

    return false;
}
class ledKit{


public:
	ledKit();
	void ledShift();
	void ledBrightH();
	void ledBrightL();
	void Signal();
};


ledKit::ledKit(){

}
	int click=0;
	int i=0;

void ledKit::ledShift(){
	/*int t, m, p;
	t=m=p=0;
	while(1){
		for (int i; i<8; ++i){
			if 		(KIT_Button9==0)	click=1;
			else if (KIT_Button10==0)	click=2;
			else if (KIT_Button11==0)	click=3;
			else{};
			t=i;
			m=(i+1);
			p=(i+2);
			leds[t]= 1;
			leds[m]= 1;
			leds[p]= 1;
			if 		(click==1)	wait_ms(200);
			else if (click==2) 	wait_ms(800);
			else if (click==3) 	wait_ms(1000);
			else 				wait_ms(500);

			leds[t]= !leds[t];
			leds[m]= !leds[m];
			leds[p]= !leds[p];

		}

	}*/

}
void ledKit::ledBrightH(){
			if (i > rh) 	rgbH[2] = 0;
			else 		rgbH[2] = 1;

			if (i > gh) 	rgbH[1] = 0;
			else 		rgbH[1] = 1;

			if (i > bh) 	rgbH[0] = 0;
			else 		rgbH[0] = 1;


	}
void ledKit::ledBrightL(){
			if (i > rl) 	rgbL[2] = 0;
			else 		rgbL[2] = 1;

			if (i > gl) 	rgbL[1] = 0;
			else 		rgbL[1] = 1;

			if (i > bl) 	rgbL[0] = 0;
			else 		rgbL[0] = 1;



	}
void ledKit::Signal(){
/*	if (stisk(butt[0])){
		if (rgbL[0]==1){
			rgbL[0]=0;
			rgbL[1]=1;
			rgbL[2]=0;
			stav=0;
		}
		else if(&rgbL[1]==1){
			rgbL[0]=0;
			rgbL[1]=0;
			rgbL[2]=1;
			stav=1;
		}
		else {
			rgbL[0]=1;
			rgbL[1]=0;
			rgbL[2]=0;
			stav=2;
		}
	}*/
}
int main()
{
	pc.baud( 115200 );

	while(true){
		if 		(stisk(&butt[0])){

		}
		else if (stisk(&butt[1])){
			rl-=JUMP;
			gl-=JUMP;
			bl-=JUMP;
		}
		else if (stisk(&butt[2])){
			rl+=JUMP;
			gl+=JUMP;
			bl+=JUMP;
			rh+=JUMP;
			gh+=JUMP;
			bh+=JUMP;
		}
		else if (stisk(&butt[3])){
			rh-=JUMP;
			gh-=JUMP;
			bh-=JUMP;
		}
		else{}
		++i;
		if (i > 100) i = 1;
		ledKit tmp;
		tmp.ledBrightL();
		tmp.ledBrightH();

	}
	pc.printf("hovno");
	ledKit tmp;
	tmp.ledShift();

	/*		int ON= 1;
	    	int Off5=5;
	    	int Off3=3;
	    	int Off8=20;

    while( 1 )
    {

    	if (KIT_Button9==0){
    		sleep(ON, Off3);
    	}
    	else if(KIT_Button10==0){
    		sleep(ON, Off5);
    	}
    	else if(KIT_Button11==0){
    		sleep(ON, Off8);
    	}
    	else{
    		KIT_LED1=1;
    	}



    }
    */
    	/*int delay = 400;

    	KIT_LED1 = !KIT_LED1; 	// invert LED1 state

    	if ( KIT_Button == 0 ) 	// button pressed?
    	{
    		delay /= 20;		// speed up blinking
    		KIT_LED2 = !KIT_LED2;
    	}
    	else
    		KIT_LED2 = 0; 		// LED2 off

    	wait_ms( delay );
    }*/
}
