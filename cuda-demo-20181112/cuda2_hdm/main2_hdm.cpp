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
#include <math.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

// Function prototype from .cu file
void cu_run_mult( float *pole, int L, float mult );

#define N 200

int main()
{
	// Array initialization 
	float array[ N ];
	for ( int i = 0; i < N; i++ )
		array[ i ] = ( float ) i;

	// Function calling from .cu file
	cu_run_mult( array, N, M_PI );

	// Print result
	for ( int i = 0; i < N; i++ )
		printf( "%8.2f", array[ i ] );
	printf( "\n" );
	return 0;
}

