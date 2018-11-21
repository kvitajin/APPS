// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology usage without unified memory.
//
// Multiplication of elements in float array.
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

// Demo kernel for array elements multiplication.
// Every thread selects one element and multiply it. 
__global__ void kernel_mult( float *pole, int L, float Mult )
{
	int l = blockDim.x * blockIdx.x + threadIdx.x;
	// if grid is greater then length of array...
	if ( l >= L ) return;

	pole[ l ] *= Mult;
}

void cu_run_mult( float *Array, int Length, float Mult )
{
	cudaError_t cerr;
	int threads = 128;
	int blocks = ( Length + threads - 1 ) / threads;

	// Memory allocation in GPU device
	float *cudaArray;
	cerr = cudaMalloc( &cudaArray, Length * sizeof( float ) );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );	

	// Copy data from PC to GPU device
	cerr = cudaMemcpy( cudaArray, Array, Length * sizeof( float ), cudaMemcpyHostToDevice );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );	

	// Grid creation
	kernel_mult<<< blocks, threads >>>( cudaArray, Length, Mult );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Copy data from GPU device to PC
	cerr = cudaMemcpy( Array, cudaArray, Length * sizeof( float ), cudaMemcpyDeviceToHost );
	if ( cerr != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Free memory
	cudaFree( cudaArray );
}
