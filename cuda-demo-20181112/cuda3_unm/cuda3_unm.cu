// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Paralel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Manipulation with prepared image.
//
// ***********************************************************************

#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include "pic_type.h"

// Every threads identifies its position in grid and in block and modify image
__global__ void kernel_animation( CUDA_Pic cuda_pic )
{
	// X,Y coordinates 
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( x >= cuda_pic.Size.x ) return;
	if ( y >= cuda_pic.Size.y ) return;

	// Point [x,y] selection from image
	uchar3 bgr, tmp = cuda_pic.P_uchar3[ y * cuda_pic.Size.x + x ];

	// color rotation
    bgr.x = tmp.y;
    bgr.y = tmp.z;
    bgr.z = tmp.x;

	// Store point [x,y] back to image
	cuda_pic.P_uchar3[ y * cuda_pic.Size.x + x ] = bgr;
}

void cu_run_animation( CUDA_Pic pic, uint2 block_size )
{
	cudaError_t cerr;

	// Grid creation with computed organization
	dim3 grid( ( pic.Size.x + block_size.x - 1 ) / block_size.x, ( pic.Size.y + block_size.y - 1 ) / block_size.y );
	kernel_animation<<< grid, dim3( block_size.x, block_size.y ) >>>( pic );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();

}
