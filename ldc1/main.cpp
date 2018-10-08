LCD_init();
LCD_clear();
function obdelnik (x, y, xx, yy, barva) {
    // x, y - levý horní roh
    // xx, yy - pravý dolní roh
    for(i = y; i <= yy; i++) {
        if(i == y || i == yy) {
            for(q = x; q <= xx; q++) {
                LCD_put_pixel(i, q, barva);
            }
        }
        else {
            LCD_put_pixel(i, x, barva);
            LCD_put_pixel(i, xx, barva);
        }
    }
}
function drawcircle(int x0, int y0, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        putpixel(x0 + x, y0 + y);
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

obdelnik(60, 40, 180, 280, "0000000000011111");
drawcircle(40, 40, 20);
Console_write('drawcircle(40, 40, 20)');
			