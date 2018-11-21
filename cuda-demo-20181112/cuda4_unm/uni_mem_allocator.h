// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// OpenCV allocator of unified memory for Mat.
//
// ***********************************************************************

#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

class UniformAllocator : public MatAllocator
{
public:
	UMatData* allocate(int dims, const int* sizes, int type,
                       void* data0, size_t* step,
                       int /*flags*/, UMatUsageFlags /*usageFlags*/) const override;

    bool allocate(UMatData* u, int /*accessFlags*/, UMatUsageFlags /*usageFlags*/) const override;

    void deallocate(UMatData* u) const override;

};
