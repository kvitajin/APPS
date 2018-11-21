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
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "pic_type.h"
#include "animation.h"

// Demo kernel to create chess board
__global__ void kernel_creategradient( CUDA_Pic colorPic )
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= colorPic.Size.y ) return;
	if ( x >= colorPic.Size.x ) return;

	int dy = x * colorPic.Size.y / colorPic.Size.x + y - colorPic.Size.y;
	unsigned char color = 255 * abs( dy ) / colorPic.Size.y;

	uchar3 bgr = ( dy < 0 ) ? ( uchar3 ) { color, 255 - color, 0 } : ( uchar3 ) { 0, 255 - color, color };

	// Store point into image
	colorPic.P_uchar3[ y * colorPic.Size.x + x ] = bgr;
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

// -----------------------------------------------------------------------------------------------

void Animation::start( CUDA_Pic bgPic, CUDA_Pic insPic )
{
	if ( initialized ) return;
	cudaError_t cerr;

	cuda_bgPic = bgPic;
	cuda_resPic = bgPic;
	cuda_insPic = insPic;

	// Memory allocation in GPU device
	// Memory for background
	cerr = cudaMalloc( &cuda_bgPic.P_void, cuda_bgPic.Size.x * cuda_bgPic.Size.y * sizeof( uchar3 ) );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Memory for inserted image
	cerr = cudaMalloc( &cuda_insPic.P_void, cuda_insPic.Size.x * cuda_insPic.Size.y * sizeof( uchar4 ) );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Memory for result
	cerr = cudaMalloc( &cuda_resPic.P_void, cuda_resPic.Size.x * cuda_resPic.Size.y * sizeof( uchar3 ) );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Creation of background gradient
	int block_size = 32;
	dim3 blocks( ( cuda_bgPic.Size.x + block_size - 1 ) / block_size, ( cuda_bgPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_creategradient<<< blocks, threads >>>( cuda_bgPic );

	// Copy data to GPU device
	cerr = cudaMemcpy( cuda_insPic.P_void, insPic.P_void, cuda_insPic.Size.x * cuda_insPic.Size.y * sizeof( uchar4 ), cudaMemcpyHostToDevice );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	initialized = 1;
}

void Animation::next( CUDA_Pic resPic, int2 position )
{
	if ( !initialized ) return;

	cudaError_t cerr;

	// Copy data internally GPU from background into result
	cerr = cudaMemcpy( cuda_resPic.P_void, cuda_bgPic.P_void, cuda_bgPic.Size.x * cuda_bgPic.Size.y * sizeof( uchar3 ), cudaMemcpyDeviceToDevice );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// insert picture
	int block_size = 32;
	dim3 blocks( ( cuda_insPic.Size.x + block_size - 1 ) / block_size, ( cuda_insPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_insertimage<<< blocks, threads >>>( cuda_resPic, cuda_insPic, position );

	// Copy data to GPU device
	cerr = cudaMemcpy( resPic.P_void, cuda_resPic.P_void, cuda_resPic.Size.x * cuda_resPic.Size.y * sizeof( uchar3 ), cudaMemcpyDeviceToHost );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

}

void Animation::stop()
{
	if ( !initialized ) return;

	cudaFree( cuda_bgPic.P_void );
	cudaFree( cuda_resPic.P_void );
	cudaFree( cuda_insPic.P_void );

	initialized = 0;
}


