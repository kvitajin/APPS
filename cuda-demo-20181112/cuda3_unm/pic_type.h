// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
//
// Image interface for CUDA
//
// ***********************************************************************

#pragma once

// Structure definition for exchanging data between Host and Device
struct CUDA_Pic
{
  uint3 Size;			// size of picture
  union {
	  void   *P_void;		// data of picture
	  uchar1 *P_uchar1;		// data of picture
	  uchar3 *P_uchar3;		// data of picture
	  uchar4 *P_uchar4;		// data of picture
  };
};
