#include "foundation/wmcv_types.h"
#include "foundation/memory/wmcv_allocator.h"

class MockAllocator : public wmcv::Allocator
{
public:
	MOCK_METHOD(void*, allocate, (wmcv_size_t size), (noexcept, override, final));
	MOCK_METHOD(void, free, (void* memory), (noexcept, override, final));
};
