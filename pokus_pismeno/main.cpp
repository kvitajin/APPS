#include <iostream>
#include "font8x8/font8x8.h"

/*LCD_init();
LCD_clear();

function usecka(x, y, end, color, direction) {
    for (i = 0; i < end; i++)
        switch (direction) {
            case "UP":
                LCD_put_pixel(x, y - i, color);
                break;
            case "DOWN":
                LCD_put_pixel(x, y + i, color);
                break;
            case "LEFT":
                LCD_put_pixel(x - i, y, color);
                break;
            case "RIGHT":
                LCD_put_pixel(x, y + i, color);
                break;
            case "UPLEFT":
                LCD_put_pixel(x - i, y - i, color);
                break;
            case "UPRIGHT":
                LCD_put_pixel(x + i, y - i, color);
                break;
            case "DOWNLEFT":
                LCD_put_pixel(x - i, y + i, color);
                break;
            case "DOWNRIGHT":
                LCD_put_pixel(x + i, y + i, color);
        }
}

usecka(50, 150, 50, "0000000000011111", "UP");


function obdelnik (x, y, xx, yy, color) {
    // x, y - levý horní roh
    // xx, yy - pravý dolní roh
    for(i = y; i <= yy; i++) {
        if(i == y || i == yy) {
            for(j = x; j <= xx; j++) {
                LCD_put_pixel(i, j, color);
            }
        }
        else {
            LCD_put_pixel(i, x, barva);
            LCD_put_pixel(i, xx, barva);
        }
    }
}
obdelnik(60, 40, 180, 280, "0000000000011111");


 function kruh (x0, y0, radius, barva){
    x=radius-1;
    y=0;
    dy=1;
    dx=1;
    err=dx-(radius<<1);

while (x >= y)
    {
        LCD_put_pixel(x0 + x, y0 + y, barva);
        LCD_put_pixel(x0 + y, y0 + x, barva);
        LCD_put_pixel(x0 - y, y0 + x, barva);
        LCD_put_pixel(x0 - x, y0 + y, barva);
        LCD_put_pixel(x0 - x, y0 - y, barva);
        LCD_put_pixel(x0 - y, y0 - x, barva);
        LCD_put_pixel(x0 + y, y0 - x, barva);
        LCD_put_pixel(x0 + x, y0 - y, barva);

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
*/

void drawcircle(int x0, int y0, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        (x0 + x, y0 + y);
        putpixel(x0 + y, y0 + x);
        putpixel(x0 - y, y0 + x);
        putpixel(x0 - x, y0 + y);
        putpixel(x0 - x, y0 - y);
        putpixel(x0 - y, y0 - x);
        putpixel(x0 + y, y0 - x);
        putpixel(x0 + x, y0 - y);

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

int main(){
    drawcircle(5,5,10);

    return 0;
}