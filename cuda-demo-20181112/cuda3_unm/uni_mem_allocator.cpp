

#include "uni_mem_allocator.h"

using namespace cv;

UMatData* UniformAllocator::allocate(int dims, const int* sizes, int type,
				   void* data0, size_t* step,
				   int /*flags*/, UMatUsageFlags /*usageFlags*/) const
{
	size_t total = CV_ELEM_SIZE(type);
	for (int i = dims-1; i >= 0; i--)
	{
		if (step)
		{
			if (data0 && step[i] != CV_AUTOSTEP)
			{
				CV_Assert(total <= step[i]);
				total = step[i];
			}
			else
			{
				step[i] = total;
			}
		}

		total *= sizes[i];
	}

	UMatData* u = new UMatData(this);
	u->size = total;

	if (data0)
	{
		u->data = u->origdata = static_cast<uchar*>(data0);
		u->flags |= UMatData::USER_ALLOCATED;
	}
	else
	{
		void* ptr = 0;
		if(cudaMallocManaged(&ptr, total) != cudaSuccess)
		{
			abort();
		}


		u->data = u->origdata = static_cast<uchar*>(ptr);
	}

	return u;
}

bool UniformAllocator::allocate(UMatData* u, int /*accessFlags*/, UMatUsageFlags /*usageFlags*/) const
{
	return (u != NULL);
}

void UniformAllocator::deallocate(UMatData* u) const
{
	if (!u)
		return;

	CV_Assert(u->urefcount >= 0);
	CV_Assert(u->refcount >= 0);

	if (u->refcount == 0)
	{
		if ( !(u->flags & UMatData::USER_ALLOCATED) )
		{
			cudaFreeHost(u->origdata);
			u->origdata = 0;
		}

		delete u;
	}
}

