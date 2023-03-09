#include "wmcv_test_pch.h"

#include "foundation/wmcv_utility.h"

#include "foundation/memory/wmcv_allocator.h"
#include "foundation/memory/wmcv_allocator_linear.h"
#include "foundation/memory/wmcv_allocator_system.h"

#include "test_allocator_mock.h"

struct MockSystemAllocatorTestFixture : public ::testing::Test
{
	virtual void SetUp() override final
	{
		wmcv::set_system_allocator(&mock);
	}

	virtual void TearDown() override final
	{
		wmcv::set_system_allocator(nullptr);
	}

	MockAllocator mock;
};

TEST_F(MockSystemAllocatorTestFixture, test_use_system_allocator_correctly)
{
	constexpr wmcv_size_t PoolSize = 4_MB;

	EXPECT_CALL(mock, allocate(PoolSize))
		.Times(::testing::AtLeast(1));

	wmcv::LinearAllocator linear_alloc(PoolSize);
}
