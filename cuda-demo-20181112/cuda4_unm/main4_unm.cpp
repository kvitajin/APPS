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
void cu_run_grayscale( CUDA_Pic bgr_pic, CUDA_Pic bw_pic );

int main( int numarg, char **arg )
{
	// Uniform Memory allocator for Mat
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator( &allocator );

	if ( numarg < 2 ) 
	{
		printf( "Enter picture filename!\n" );
		return 1;
	}

	// Load image
	Mat cv_bgr = imread( arg[ 1 ], CV_LOAD_IMAGE_COLOR );

	if ( !cv_bgr.data )
	{
		printf( "Unable to read file '%s'\n", arg[ 1 ] );
		return 1;
	}

	// create empty BW image
	Mat cv_bw( cv_bgr.size(), CV_8U );

	// data for CUDA
	CUDA_Pic pic_bgr, pic_bw;
	pic_bgr.Size.x = pic_bw.Size.x = cv_bgr.size().width;
	pic_bgr.Size.y = pic_bw.Size.y = cv_bgr.size().height;
	pic_bgr.P_uchar3 = ( uchar3 * ) cv_bgr.data;
	pic_bw.P_uchar1 = ( uchar1 * ) cv_bw.data;

	// Function calling from .cu file
	cu_run_grayscale( pic_bgr, pic_bw );

	// Show the Color and BW image
	imshow( "Color", cv_bgr );
	imshow( "GrayScale", cv_bw );
	waitKey( 0 );
}

