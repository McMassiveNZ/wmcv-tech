#include "wmcv_test_pch.h"
#include "foundation/wmcv_utility.h"

TEST(test_utility, is_zero_power_of_2)
{
	constexpr bool result = wmcv::is_power_of_2(0);
	EXPECT_TRUE(result);
}

TEST(test_utility, is_one_power_of_2)
{
	constexpr bool result = wmcv::is_power_of_2(1);
	EXPECT_TRUE(result);
}

TEST(test_utility, is_two_power_of_2)
{
	constexpr bool result = wmcv::is_power_of_2(2);
	EXPECT_TRUE(result);
}

TEST(test_utility, is_arbitrary_power_of_2)
{
	constexpr bool result = wmcv::is_power_of_2(4096);
	EXPECT_TRUE(result);
}

TEST(test_utility, is_arbitrary_not_power_of_2)
{
	constexpr bool result = wmcv::is_power_of_2(4099);
	EXPECT_FALSE(result);
}

TEST(test_utility, test_align_0)
{
	constexpr auto result = wmcv::align(0, 16);
	EXPECT_EQ(result, 0);
}

TEST(test_utility, test_align_1_to_16)
{
	const auto result = wmcv::align(1, 16);
	EXPECT_EQ(result, 16);
}

TEST(test_utility, test_align_5_to_4)
{
	const auto result = wmcv::align(5, 4);
	EXPECT_EQ(result, 8);
}

TEST(test_utility, test_is_aligned)
{
	const auto result = wmcv::is_aligned(16, 16);
	EXPECT_TRUE(result);
}

TEST(test_utility, test_is_not_aligned)
{
	const auto result = wmcv::is_aligned(3, 4);
	EXPECT_FALSE(result);
}

TEST(test_utility, test_ptr_aligned)
{
	uintptr_t uintptr = 0x0000000000543310;
	void* address = reinterpret_cast<void*>(uintptr);
	const auto result = wmcv::is_ptr_aligned(address, 16);
	EXPECT_TRUE(result);
}

TEST(test_utility, test_ptr_not_aligned)
{
	uintptr_t uintptr = 0x0000000000543313;
	void* address = reinterpret_cast<void*>(uintptr);
	const auto result = wmcv::is_ptr_aligned(address, 16);
	EXPECT_FALSE(result);
}