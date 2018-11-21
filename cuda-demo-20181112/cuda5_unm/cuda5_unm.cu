// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage wit unified memory.
// Image transformation from RGB to BW schema. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "pic_type.h"

// Demo kernel to create chess board
__global__ void kernel_chessboard( CUDA_Pic colorPic )
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= colorPic.Size.y ) return;
	if ( x >= colorPic.Size.x ) return;

	unsigned char borw = 255 * ( ( blockIdx.x + blockIdx.y ) & 1 );

	// Store point into image
	colorPic.P_uchar3[ y * colorPic.Size.x + x ] = { borw, borw, borw };
}

void cu_create_chessboard( CUDA_Pic colorPic, int square_size )
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	dim3 blocks( ( colorPic.Size.x + square_size - 1 ) / square_size, ( colorPic.Size.y + square_size - 1 ) / square_size );
	dim3 threads( square_size, square_size );
	kernel_chessboard<<< blocks, threads >>>( colorPic );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------

// Demo kernel to create picture with alpha channel gradient
__global__ void kernel_alphaimg( CUDA_Pic colorPic, uchar3 color )
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= colorPic.Size.y ) return;
	if ( x >= colorPic.Size.x ) return;

	int diagonal = sqrtf( colorPic.Size.x * colorPic.Size.x + colorPic.Size.y * colorPic.Size.y );
	int dx = x - colorPic.Size.x / 2;
	int dy = y - colorPic.Size.y / 2;
	int dxy = sqrtf( dx * dx + dy * dy ) - diagonal / 2;

	// Store point into image
	colorPic.P_uchar4[ y * colorPic.Size.x + x ] =
		{ color.x, color.y, color.z, ( unsigned char ) ( 255 - 255 * dxy / ( diagonal / 2 ) ) };
}

void cu_create_alphaimg( CUDA_Pic colorPic, uchar3 color )
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 32;
	dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_alphaimg<<< blocks, threads >>>( colorPic, color );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------

// Demo kernel to create picture with alpha channel gradient
__global__ void kernel_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position )
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= smallPic.Size.y ) return;
	if ( x >= smallPic.Size.x ) return;
	int by = y + position.y;
	int bx = x + position.x;
	if ( by >= bigPic.Size.y || by < 0 ) return;
	if ( bx >= bigPic.Size.x || bx < 0 ) return;

	// Get point from small image
	uchar4 fg_bgra = smallPic.P_uchar4[ y * smallPic.Size.x + x ];
	uchar3 bg_bgr = bigPic.P_uchar3[ by * bigPic.Size.x + bx ];
	uchar3 bgr = { 0, 0, 0 };

	// compose point from small and big image according alpha channel
	bgr.x = fg_bgra.x * fg_bgra.w / 255 + bg_bgr.x * ( 255 - fg_bgra.w ) / 255;
	bgr.y = fg_bgra.y * fg_bgra.w / 255 + bg_bgr.y * ( 255 - fg_bgra.w ) / 255;
	bgr.z = fg_bgra.z * fg_bgra.w / 255 + bg_bgr.z * ( 255 - fg_bgra.w ) / 255;

	// Store point into image
	bigPic.P_uchar3[ by * bigPic.Size.x + bx ] = bgr;
}

void cu_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position )
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 32;
	dim3 blocks( ( smallPic.Size.x + block_size - 1 ) / block_size, ( smallPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_insertimage<<< blocks, threads >>>( bigPic, smallPic, position );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}
