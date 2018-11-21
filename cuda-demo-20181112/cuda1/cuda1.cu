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
// Every thread displays information of its position in block,
// position of block in grid and global position.
//
// ***********************************************************************


#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

// Demo kernel will display all global variables of grid organization.
// Warning! Function printf is available from compute capability 2.x
__global__ void thread_hierarchy()
{
    // Global variables
    // Grid dimension -				gridDim
	// Block position in grid -		blockIdx
	// Block dimension -			blockDim
	// Thread position in block -	threadIdx
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;
    printf( "Block{%d,%d}[%d,%d] Thread{%d,%d}[%d,%d] [%d,%d]\n",
	    gridDim.x, gridDim.y, blockIdx.x, blockIdx.y,
		blockDim.x, blockDim.y, threadIdx.x, threadIdx.y, x, y );
}

void cu_run_cuda( dim3 grid_size, dim3 block_size )
{
	cudaError_t cerr;
	// Following command can increase internal buffer for printf function
    /*cerr = cudaDeviceSetLimit( cudaLimitPrintfFifoSize, required_size );
	if ( err != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );
    */

	// Thread creation from selected kernel:
	// first parameter dim3 is grid dimension
	// second parameter dim3 is block dimension
    thread_hierarchy<<< grid_size, block_size >>>();

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	// Output from printf is in GPU memory. 
	// To get its contens it is necessary to synchronize device.

	cudaDeviceSynchronize();
}
