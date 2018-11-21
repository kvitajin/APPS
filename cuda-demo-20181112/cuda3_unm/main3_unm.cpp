// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Image creation and its modification using CUDA.
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

// Prototype of function in .cu file
void cu_run_animation( CUDA_Pic pic, uint2 block_size );

// Image size
#define SIZEX 432 // Width of image
#define	SIZEY 321 // Height of image
// Block size for threads
#define BLOCKX 40 // block width
#define BLOCKY 25 // block height


int main()
{
	// Uniform Memory allocator for Mat
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator( &allocator );

	// Creation of empty image.
	// Image is stored line by line.
	Mat cv_img( SIZEY, SIZEX, CV_8UC3 );

	// Image filling by color gradient blue-green-red
	for ( int y = 0; y < cv_img.rows; y++ )
		for ( int x  = 0; x < cv_img.cols; x++ )
		{
			int dx = x - cv_img.cols / 2;

			unsigned char grad = 255 * abs( dx ) / ( cv_img.cols / 2 );
			unsigned char inv_grad = 255 - grad;

			// left or right half of gradient
			uchar3 bgr = ( dx < 0 ) ? ( uchar3 ) { grad, inv_grad, 0 } : ( uchar3 ) { 0, inv_grad, grad };

			// put pixel into image
			Vec3b v3bgr( bgr.x, bgr.y, bgr.z );
			cv_img.at<Vec3b>( y, x ) = v3bgr;
			// also possible: cv_img.at<uchar3>( y, x ) = bgr;
		}


	CUDA_Pic pic_img;
	pic_img.Size.x = cv_img.cols;
	pic_img.Size.y = cv_img.rows;
	pic_img.P_uchar3 = ( uchar3 * ) cv_img.data;

	// Show image before modification
	imshow( "B-G-R Gradient", cv_img );

	// Function calling from .cu file
	uint2 block_size = { BLOCKX, BLOCKY };
	cu_run_animation( pic_img, block_size );

	// Show modified image
	imshow( "B-G-R Gradient & Color Rotation", cv_img );
	waitKey( 0 );
}

