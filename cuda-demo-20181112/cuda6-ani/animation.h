// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
//
// Simple animation.
//
// ***********************************************************************

class Animation
{
public:
	CUDA_Pic cuda_bgPic, cuda_insPic, cuda_resPic;
	int initialized;

	Animation() : initialized( 0 ) {}

	void start( CUDA_Pic bgPic, CUDA_Pic insPic );

	void next( CUDA_Pic resPic, int2 position );

	void stop();

};
