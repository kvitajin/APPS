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
#include <string>
#include <cmath>
#include <time.h>
#include <sys/time.h>


// two dimensional array with fixed size font
extern uint8_t font8x8[ 256 ][ 8 ];

class Usecka{
public:
    Usecka();   //todo dodelat vzkresleni podle smeru a slass promenne
    void plotLineLow(int x0, int y0, int x1, int y1, int color);
    void plotLineHigh(int x0,int y0, int x1, int y1, int color);
    void plotLine(int x0,int y0, int x1, int y1, int color);
};
void Usecka::plotLineLow(int x0,int y0, int x1, int y1, int color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2*dy - dx;
    y = y0;
    for (int x=x0;x< x1;++x){
        LCD_put_pixel(x,y, color);
        if (D > 0) {
            y = y + yi;
            D = D - 2 * dx;
        }
        D = D + 2*dy;
    }
}

void Usecka::plotLineHigh(int x0, int y0, int x1, int y1, int color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    D = 2*dx - dy;
    x = x0;

    for (int y=y0;y<y1;++y){
        LCD_put_pixel(x,y, color)
        if( D > 0) {
            x = x + xi;
            D = D - 2 * dy;
        }
        D = D + 2*dx;
    }
}
void Usecka::plotLine(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) plotLineLow(x1, y1, x0, y0);
        else         plotLineLow(x0, y0, x1, y1);
    }
    else {
        if (y0 > y1) plotLineHigh(x1, y1, x0, y0);
        else         plotLineHigh(x0, y0, x1, y1);
    }
}
Usecka::Usecka() {}
class Analog{
    Analog();
    void cifernik(int xc, int yc, int r, int color);
    void rucicka(int xc, int yc, int r, int v, int color);
                                                                        //todo dodelat
};

Analog::Analog() {}
void Analog::cifernik(int xc, int yc, int r, int color) {
    int i;
    Usecka u;
    for ( i = 0; i < 60; i ++ )
    {
        int x1 = xc + r * cos ( i * M_PI / 30 );
        int y1 = yc + r * sin ( i * M_PI / 30 );
        int rr = i % 5 == 0 ? 0.85 * r : 0.92 * r;
        int x2 = xc + rr * cos ( i * M_PI / 30 );
        int y2 = yc + rr * sin ( i * M_PI / 30 );

        u.plotLine(x1, y1, x2, y2, color);
    }
}
void Analog::rucicka(int xc, int yc, int r, int v, int color ) {
    int x = xc + r * cos ( ( 15 - v ) * M_PI / 30 );
    int y = yc - r * sin ( ( 15 - v ) * M_PI / 30 );
    Usecka r;
    r.plotLine (xc, yc, x, y, color);
}



class Kruh{
public:
    Kruh(int x0, int y0, int radius, int barva);
};

Kruh::Kruh(int x0, int y0, int radius, int barva) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        (x0 + x, y0 + y);
        LCD_put_pixel(x0 + y, y0 + x, barva);
        LCD_put_pixel(x0 - y, y0 + x, barva);
        LCD_put_pixel(x0 - x, y0 + y, barva);
        LCD_put_pixel(x0 - x, y0 - y, barva);
        LCD_put_pixel(x0 - y, y0 - x, barva);
        LCD_put_pixel(x0 + y, y0 - x, barva);
        LCD_put_pixel(x0 + x, y0 - y, barva);
        LCD_put_pixel(x0 + x, y0 + y, barva);


        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }

    }
}

class Obdelnik{
public:
    Obdelnik (int x, int y, int xx, int yy, bool fill, int barva);
    void rotace();
};
Obdelnik::Obdelnik(int x, int y, int xx, int yy, bool fill, int barva) {
    if (fill){
        for(int i=y; i<=yy; ++i){
            for(int j=x; j<=xx;++j){
                LCD_put_pixel(i, j, barva);
            }
        }
    }
    else{
        for(int i=y; i<=yy; ++i){
            for(int j=x; j<=xx;++j){
                if (i==y || i==yy){
                    LCD_put_pixel(i, j, barva);
                }
                if (j==x||j==xx){
                    LCD_put_pixel(i, j, barva);

                }
            }
        }
    }
}

class pismeno{
private:
    int x;
    int y;
    int color;
    int back;
    int velikost;
    uint8_t* letter;

public:
    pismeno(int, int, int, int, int, uint8_t*);
    void draw();
    void drawBigger();
};

pismeno::pismeno(int one, int two, int barva, int pozadi, int vel, uint8_t* znak){
    this->x = one;
    this->y = two;
    this->color = barva;
    this->back = pozadi;
    this->velikost = vel;
    this->letter = znak;

    //draw();
    drawBigger();
}

void pismeno::draw(){
    for (int i = 0; i < 8; i++){
        uint8_t row = letter[i];
        for (int j = 0; j < 8; j++){    // trying if the number at z is 1 or 0
            int check = pow(2, 7-j);
            if (row/check >= 1){
                LCD_put_pixel(x -j, y + i, color);
                row -= check;
            }
        }
    }
}

void pismeno::drawBigger(){
    for (int i = 0; i < 8; i++){
        uint8_t row = letter[i];

        for (int j = 0; j < 8; j++){
            int check = pow(2, 7-j);
            if (row/check >= 1){
                for (int k = 0; k < velikost; k++){
                    for (int l = 0; l < velikost; l++)
                    {
                        LCD_put_pixel(x -(velikost*j)-k, y +(velikost*i)+l, color);
                    }
                }
                row -= check;
            }
        }
    }
}
/*
class Tvary{
public:
    Tvary();
    void Kruh(int x0, int y0, int radius, int barva);
    void obdelnik (int x, int y, int xx, int yy, bool fill, int barva);
    void usecka(int x, int y, int end, int color, int direction);
};
Tvary::Tvary(){}

void Tvary::usecka(int x, int y, int end, int color, int direction){
    for (int i = 0; i < end; i++){
        switch (direction) {
            case 1:
                LCD_put_pixel(x, y - i, color);
                break;
            case 2:
                LCD_put_pixel(x, y + i, color);
                break;
            case 3:
                LCD_put_pixel(x - i, y, color);
                break;
            case 4:
                LCD_put_pixel(x, y + i, color);
                break;
            case 5:
                LCD_put_pixel(x - i, y - i, color);
                break;
            case 6:
                LCD_put_pixel(x + i, y - i, color);
                break;
            case 7:
                LCD_put_pixel(x - i, y + i, color);
                break;
            case 8:
                LCD_put_pixel(x + i, y + i, color);
        }
    }
}

void Tvary::Kruh(int x0, int y0, int radius, int barva){
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        (x0 + x, y0 + y);
        LCD_put_pixel(x0 + y, y0 + x, barva);
        LCD_put_pixel(x0 - y, y0 + x, barva);
        LCD_put_pixel(x0 - x, y0 + y, barva);
        LCD_put_pixel(x0 - x, y0 - y, barva);
        LCD_put_pixel(x0 - y, y0 - x, barva);
        LCD_put_pixel(x0 + y, y0 - x, barva);
        LCD_put_pixel(x0 + x, y0 - y, barva);
        LCD_put_pixel(x0 + x, y0 + y, barva);


        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }

    }
}

void Tvary::obdelnik (int x, int y, int xx, int yy, bool fill, int barva) {
    // x, y - levý horní roh
    // xx, yy - pravý dolní roh

    if (fill){
        for(int i=y; i<=yy; ++i){
            for(int j=x; j<=xx;++j){
                LCD_put_pixel(i, j, barva);
            }
        }
    }
    else{
        for(int i=y; i<=yy; ++i){
            for(int j=x; j<=xx;++j){
                if (i==y || i==yy){
                    LCD_put_pixel(i, j, barva);
                }
                if (j==x||j==xx){
                    LCD_put_pixel(i, j, barva);

                }
            }
        }
    }
}
/*void pismeno(int x, int y, int pozadi, int velikost, int pismeno, int barva){
	for (int i=0; i=velikost; ++i){
		for (int j=0; j=velikost; ++j){
			if (pismeno[i][j]==0)
		}
	}

		/*for(int i = 0; i < 8; i++) {
			int radek = pismeno[i];
			for(int q = 0; q < 8; q++) {
				int odecti = pow(2, 7-q);
				if((radek / odecti) >= 1) {
					LCD_put_pixel(x - q, y + i, barva);
					radek -= odecti;
				}
			}
		}

}*/



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
    /*for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
        for ( int i = 0; i < limit; i++ )
        {
            LCD_put_pixel( ofs + i,     ofs + 0,     color_red );
            LCD_put_pixel( ofs + 0,     ofs + i,     color_green );
            LCD_put_pixel( ofs + i,     ofs + limit, color_blue );
            LCD_put_pixel( ofs + limit, ofs + i,     color_white );
        }
        */
    /*Tvary t;
    t.usecka(10, 10, 20, color_red, 5);
    t.Kruh(100, 100, 100, color_red);
    t.obdelnik(20, 20, 50, 50, true, color_green);
    t.obdelnik(55, 55, 150, 100, false, color_white);*/
    //pismeno(150, 150, color_white, 'M', color_green)

    struct timeval tv;
    struct tm t;

    gettimeofday ( &tv, NULL );
    t = *localtime ( &tv . tv_sec );
    Analog anal;
    anal.cifernik(xc, yc, r, color_white);           //todo dopsat pocatecni hodnoty ciferniku a polomer
    //drawDial ( dst, xc, yc + r / 2, r / 3 );
    anal.rucicka(xc, yc, 0.8 * r, t . tm_min, color_white );                                 //minuta?
    anal.rucicka(xc, yc, 0.6 * r, ( t . tm_hour % 12 ) * 5 + t . tm_min / 12, color_white);  //hodina?
    //drawHand ( dst, xc, yc, 0.8 * r, t . tm_min );
    //drawHand ( dst, xc, yc, 0.6 * r, ( t . tm_hour % 12 ) * 5 + t . tm_min / 12 );

    //SDL_SetRenderDrawColor ( dst, 255, 0, 0, 255 );
    anal.rucicka(xc, yc, 0.9 * r, t . tm_sec, color_red);                               //sekunda
    //drawHand ( dst, xc, yc, 0.9 * r, t . tm_sec );

    //SDL_SetRenderDrawColor ( dst, 0, 0, 0, 255 );
    //drawHand ( dst, xc, yc + r / 2, 0.9 * r / 3, 60.0 * tv . tv_usec / 1000000 );




    return 0;
}