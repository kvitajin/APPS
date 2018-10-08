#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
//#include "font8x8.cpp"

cv::Mat platno( cv::Size( 200, 200 ), CV_8UC3 );

void lcd_putpixel( int x, int y )
{
	cv::Vec3b barva( 255, 255, 255 );
	platno.at<cv::Vec3b>( x, y ) = barva;
}

void lcd_clear()
{
	cv::Vec3b cerna( 0, 0, 0 );
	platno.setTo( cerna );
}

int main()
{
	lcd_putpixel( 100, 100 );
	cv::namedWindow( "platno", 0 );
	cv::imshow( "platno", platno );
	cv::waitKey( 0 );
}


