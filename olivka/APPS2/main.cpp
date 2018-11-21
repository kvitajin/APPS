#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "font8x8.cpp"
#include "font36.cpp"

struct RGB { unsigned char r, g, b; };

cv::Mat platno( cv::Size( 320, 240 ), CV_8UC3 );

void lcd_putpixel( int x, int y, RGB rgb )
{
    cv::Vec3b barva( rgb.b, rgb.g, rgb.r );
    platno.at<cv::Vec3b>( x, y ) = barva;
}

void lcd_clear()
{
    cv::Vec3b cerna( 0, 0, 0 );
    platno.setTo( cerna );
}

class Bod 
{
public:
    Bod( int x, int y, RGB barva ): x0( x ), y0( y ), rgb( barva ) {};
    void kresli( int x = 0, int y = 0 ) { lcd_putpixel( x0 + x, y0 + y, rgb ); }

    int x0, y0;
    RGB rgb;
};

class Kruh : public Bod
{
public:
  Kruh( int x, int y, int radius, RGB barva ) : Bod( x, y, barva ), R( radius ) {};
  void kresli()
  {
    int x = R-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (R << 1);

    while (x >= y)
    {
        Bod::kresli( + x,  + y);
        Bod::kresli( + y,  + x);
        Bod::kresli( - y,  + x);
        Bod::kresli( - x,  + y);
        Bod::kresli( - x,  - y);
        Bod::kresli( - y,  - x);
        Bod::kresli( + y,  - x);
        Bod::kresli( + x,  - y);

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
            err += dx - (R << 1);
        }
    }
  }

  int R;
};

int fun_a(void)
{
    RGB cervena = { 255, 0, 0 };
    Bod b( 100, 100, cervena );
    Kruh k( 100, 100, 50, cervena );
    b.kresli();
    k.kresli();
    cv::namedWindow( "platno", 0 );
    cv::imshow( "platno", platno );
    cv::waitKey( 0 );
}

int fun_b(void)
{
  char znak = '8';
  for ( int x = 0; x < 8; x++ )
  {
    for ( int y = 0; y < 8; y++ )
    {
      if ( font8x8[ znak ][ x ] & ( 1 << y ) )
        printf( "#" );
      else
        printf( "." );
    }
    printf( "\n" );
  }  
}


int fun_c(void)
{
  char znak = 'F';

  int start = (48*5)*(znak - ' ');

  for ( int x = 0; x < 48; x++ )
  {
    for ( int s = 0; s < 5; s++ )
      for ( int y = 0; y < 8; y++ )
      {
        if ( Font36_Table[ start + (x*5) + s  ] & ( 1 << (7-y) ) )
          printf( "#" );
        else
          printf( "." );
      }
    printf( "\n" );
  }
}

int main(void)
{
  fun_a();
  fun_b();
  fun_c();

  return 0;
}
