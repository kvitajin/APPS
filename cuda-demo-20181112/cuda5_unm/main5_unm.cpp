// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Image transformation from RGB to BW schema. 
// Image manipulation is performed by OpenCV library. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "opencv2/opencv.hpp"
#include "pic_type.h"
#include "uni_mem_allocator.h"

using namespace cv;

// Function prototype from .cu file
void cu_create_chessboard( CUDA_Pic pic, int square_size );
void cu_create_alphaimg( CUDA_Pic pic, uchar3 color );
void cu_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position );

int main( int numarg, char **arg )
{
	// Uniform Memory allocator for Mat
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator( &allocator );

	Mat cv_chessboard( 511, 515, CV_8UC3 );

	CUDA_Pic pic_chessboard;
	pic_chessboard.Size.x = cv_chessboard.cols;
	pic_chessboard.Size.y = cv_chessboard.rows;
	pic_chessboard.P_uchar3 = ( uchar3 * ) cv_chessboard.data;

	cu_create_chessboard( pic_chessboard, 21 );

	imshow( "Chess Board", cv_chessboard );

	Mat cv_alphaimg( 211, 191, CV_8UC4 );

	CUDA_Pic pic_alphaimg;
	pic_alphaimg.Size.x = cv_alphaimg.cols;
	pic_alphaimg.Size.y = cv_alphaimg.rows;
	pic_alphaimg.P_uchar4 = ( uchar4 * ) cv_alphaimg.data;

	cu_create_alphaimg( pic_alphaimg, { 0, 0, 255 } );

	imshow( "Alpha channel", cv_alphaimg );

	cu_insertimage( pic_chessboard, pic_alphaimg, { 11, 23 } );

	imshow( "Result I", cv_chessboard );

	// some argument?
	if ( numarg > 1 )
	{
		// Load image
		Mat cv_ball = imread( arg[ 1 ], CV_LOAD_IMAGE_UNCHANGED );

		if ( !cv_ball.data )
			printf( "Unable to read file '%s'\n", arg[ 1 ] );

		else if ( cv_ball.channels() != 4 )
			printf( "Image does not contain alpha channel!\n" );

		else
		{
			// insert loaded image
			CUDA_Pic pic_ball;
			pic_ball.Size.x = cv_ball.cols;
			pic_ball.Size.y = cv_ball.rows;
			pic_ball.P_uchar4 = ( uchar4 * ) cv_ball.data;

			cu_insertimage( pic_chessboard, pic_ball, { ( int ) pic_chessboard.Size.x / 2, ( int ) pic_chessboard.Size.y / 2 } );

			imshow( "Result II", cv_chessboard );
		}
	}

	waitKey( 0 );
}

