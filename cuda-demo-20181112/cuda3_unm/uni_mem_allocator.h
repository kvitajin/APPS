
#pragma once

#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>


using namespace cv;

class UniformAllocator : public cv::MatAllocator {
public:
	UMatData* allocate(int dims, const int* sizes, int type,
                       void* data0, size_t* step,
                       int /*flags*/, UMatUsageFlags /*usageFlags*/) const override;

    bool allocate(UMatData* u, int /*accessFlags*/, UMatUsageFlags /*usageFlags*/) const override;

    void deallocate(UMatData* u) const override;

};
