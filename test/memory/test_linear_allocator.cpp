#include "wmcv_test_pch.h"

#include "foundation/wmcv_utility.h"

#include "foundation/memory/wmcv_allocator.h"
#include "foundation/memory/wmcv_allocator_linear.h"
#include "foundation/memory/wmcv_allocator_linear_concurrent.h"
#include "foundation/memory/wmcv_allocator_system.h"

#include "test_allocator_mock.h"

using ::testing::AtLeast;

TEST(linear_allocator_test, test_linear_allocator_alloc)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::LinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);

	EXPECT_TRUE(alloced_mem != nullptr);
	EXPECT_TRUE(alloced_mem == mem_pool);

	EXPECT_TRUE(allocator.get_marker() == 1_kB);

	alloced_mem = allocator.allocate(1_kB);
	EXPECT_TRUE(alloced_mem != nullptr);
	EXPECT_TRUE(alloced_mem == mem_pool + 1_kB);

	EXPECT_TRUE(allocator.get_marker() == 2_kB);
}

TEST(linear_allocator_test, test_concurrent_linear_allocator_alloc)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::ConcurrentLinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);

	EXPECT_TRUE(alloced_mem != nullptr);
	EXPECT_TRUE(alloced_mem == mem_pool);

	EXPECT_TRUE(allocator.get_marker() == 1_kB);

	alloced_mem = allocator.allocate(1_kB);
	EXPECT_TRUE(alloced_mem != nullptr);
	EXPECT_TRUE(alloced_mem == mem_pool + 1_kB);

	EXPECT_TRUE(allocator.get_marker() == 2_kB);
}

TEST(linear_allocator_test, test_linear_allocator_free)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::LinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);
	const auto marker = allocator.get_marker();

	EXPECT_TRUE(allocator.get_marker() == 1_kB);
	allocator.free(alloced_mem);

	EXPECT_TRUE(allocator.get_marker() == marker);
}

TEST(linear_allocator_test, test_concurrent_linear_allocator_free)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::LinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);
	const auto marker = allocator.get_marker();

	EXPECT_TRUE(allocator.get_marker() == 1_kB);
	allocator.free(alloced_mem);

	EXPECT_TRUE(allocator.get_marker() == marker);
}

TEST(linear_allocator_test, test_linear_allocator_reset)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::LinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);
	const auto marker = allocator.get_marker();

	EXPECT_TRUE(allocator.get_marker() == 1_kB);
	allocator.reset();

	EXPECT_TRUE(allocator.get_marker() == 0ull);
}

TEST(linear_allocator_test, test_concurrent_linear_allocator_reset)
{
	constexpr wmcv_size_t PoolSize = 4_kB;
	wmcv_byte mem_pool[PoolSize] = {};

	wmcv::LinearAllocator allocator{PoolSize, mem_pool};
	void* alloced_mem = allocator.allocate(1_kB);
	const auto marker = allocator.get_marker();

	EXPECT_TRUE(allocator.get_marker() == 1_kB);
	allocator.reset();

	EXPECT_TRUE(allocator.get_marker() == 0ull);
}
