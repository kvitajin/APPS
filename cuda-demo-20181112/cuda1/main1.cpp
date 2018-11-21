// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
// Global variables usage in threads, use of printf.
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

// Prototype of function from .cu file
void cu_run_cuda( dim3 grid_size, dim3 block_size );

int main()
{
	// Function calling
	dim3 grid_size( 3, 2 ), block_size( 2, 3 );

	cu_run_cuda( grid_size, block_size );

	return 0;
}

