// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Paralel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage without unified memory.
//
// Manipulation with prepared image.
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
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

	CUDA_Pic cudaPic;
	cudaPic.Size = pic.Size;

	// Memory allocation in GPU device
	cerr = cudaMalloc( &cudaPic.P_void, cudaPic.Size.x * cudaPic.Size.y * sizeof( uchar3 ) );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );	

	// Copy data to GPU device
	cerr = cudaMemcpy( cudaPic.P_void, pic.P_void, cudaPic.Size.x * cudaPic.Size.y * sizeof( uchar3 ), cudaMemcpyHostToDevice );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );	

	// Grid creation with computed organization
	dim3 mrizka( ( cudaPic.Size.x + block_size.x - 1 ) / block_size.x, ( cudaPic.Size.y + block_size.y - 1 ) / block_size.y );
	kernel_animation<<< mrizka, dim3( block_size.x, block_size.y ) >>>( cudaPic );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Copy data from GPU device to PC
	cerr = cudaMemcpy( pic.P_void, cudaPic.P_void, pic.Size.x * pic.Size.y * sizeof( uchar3 ), cudaMemcpyDeviceToHost );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );	

	// Free memory
	cudaFree( cudaPic.P_void );

	cudaDeviceSynchronize();
}
