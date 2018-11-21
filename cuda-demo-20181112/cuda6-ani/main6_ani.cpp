// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage without unified memory.
//
// Simple animation.
// Image manipulation is performed by OpenCV library. 
//
// ***********************************************************************

#include <stdio.h>
#include <sys/time.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "opencv2/opencv.hpp"
#include "pic_type.h"
#include "uni_mem_allocator.h"
#include "animation.h"

using namespace cv;

// Function prototype from .cu file

int main( int numarg, char **arg )
{
	// Uniform Memory allocator for Mat
	//UniformAllocator allocator;
	//cv::Mat::setDefaultAllocator( &allocator );

	Animation animation;

	// Output image
	Mat cv_animation( 777, 888, CV_8UC3 );
	// Ball image
	Mat cv_ball = imread( "ball.png", CV_LOAD_IMAGE_UNCHANGED );

	printf( "ball channels %d\n", cv_ball.channels() );

	// Data for CUDA
	CUDA_Pic pic_animation, pic_ball;

	pic_animation.Size.x = cv_animation.cols;
	pic_animation.Size.y = cv_animation.rows;
	pic_animation.P_uchar3 = ( uchar3 * ) cv_animation.data;

	pic_ball.Size.x = cv_ball.cols;
	pic_ball.Size.y = cv_ball.rows;
	pic_ball.P_uchar4 = ( uchar4 * ) cv_ball.data;

	// Prepare data for animation
	animation.start( pic_animation, pic_ball );

	// simulation of a bouncing ball
	// 1 pixel ~ 1 mm
	float bump_up = 0.8;
	float g = 9.81;
	float v_z = 0;	// vertical speed m/s
	float h_z = 0.001 * ( cv_animation.rows + cv_ball.rows ); // height
	float direction = -1.0;
	int iterations = 0;
	int run_simulation = 1;

	timeval cur_time, old_time, delta_time;
	gettimeofday( &old_time, NULL );

	while ( run_simulation )
	{
		waitKey( 1 );

		// time measuring
		gettimeofday( &cur_time, NULL );
		timersub( &cur_time, &old_time, &delta_time );
		if ( delta_time.tv_usec < 1000 ) continue; // too short time
		old_time = cur_time;
		float delta_sec = ( float ) delta_time.tv_usec / 1E6; // time in seconds

		iterations++;
		// height and speed computation
		h_z = h_z + v_z * delta_sec;
		v_z = v_z - g * delta_sec;

		// direction changed?
		if ( direction < 0 && h_z <= 0 )
		{
			// decrease speed of a bounced ball
			v_z = -v_z * bump_up;
			h_z = 0;
			direction = 1.0;
		}
		else if ( direction > 0 && v_z <= 0 )
		{
			direction = -1.0;
			// simulation limit is jump 2 mm (2 pixels)
			if ( h_z < 0.002 ) run_simulation = h_z = 0;
		}

		// bottom position of ball
		int z = cv_animation.rows - h_z * 1000;
		// position of the ball image
		z -= cv_ball.rows;

		animation.next( pic_animation, { cv_animation.cols - 3 * cv_ball.rows / 2, z } );

		imshow( "Bouncing Ball", cv_animation );
	}

	animation.stop();

	printf( "Ball stopped after %d iterations\n", iterations );

	waitKey( 0 );
}

