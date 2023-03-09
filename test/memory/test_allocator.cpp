#include "wmcv_test_pch.h"

#include "foundation/wmcv_utility.h"
#include "foundation/memory/wmcv_allocator.h"
#include "foundation/memory/wmcv_allocator_linear.h"
#include "foundation/memory/wmcv_allocator_system.h"

#include "test_allocator_mock.h"

using ::testing::AtLeast;

class Mallocator : public wmcv::Allocator
{
public:
	[[no_discard]] void* allocate(wmcv_size_t size) noexcept override
	{
		return ::malloc(size);
	}

	void free(void* memory) noexcept override
	{
		::free(memory);
	}
};


TEST(allocator_test, test_allocator_alloc)
{
	constexpr wmcv_size_t alloc_size = 1_kB;
	MockAllocator alloc;

	EXPECT_CALL(alloc, allocate(alloc_size))
		.Times(::testing::AtLeast(1));

	wmcv_allocate(alloc, alloc_size);
}

TEST(allocator_test, test_allocator_alloc_aligned)
{
	constexpr wmcv_size_t alloc_size = 1_kB;
	constexpr wmcv_size_t alloc_alignment = 16;

	Mallocator alloc;

	auto* memory = wmcv_allocate_aligned(alloc, alloc_size, alloc_alignment);
	EXPECT_NE(memory, nullptr);
	EXPECT_TRUE(wmcv::is_ptr_aligned(memory, alloc_alignment));

	wmcv_free_aligned(alloc, memory, alloc_alignment);
}

TEST(allocator_test, test_allocator_free)
{
	constexpr wmcv_size_t alloc_size = 1_kB + 4;

	MockAllocator mock;
	wmcv_byte memory[alloc_size];

	void* ptr = static_cast<void*>(memory);

	EXPECT_CALL(mock, free(ptr))
		.Times(::testing::AtLeast(1));

	wmcv_free(mock, ptr);
}