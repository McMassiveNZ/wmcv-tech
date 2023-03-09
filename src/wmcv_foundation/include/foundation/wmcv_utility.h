#pragma once

#include "wmcv_types.h"

namespace wmcv
{
[[nodiscard]] constexpr bool is_power_of_2(wmcv_size_t n) noexcept
{
	const bool result = (n & (n - 1)) == 0;
	return result;
}

[[nodiscard]] constexpr wmcv_size_t align( wmcv_size_t size, wmcv_size_t alignment ) noexcept
{
	assert(is_power_of_2(alignment) && "Error: alignment isn't a power of 2");
	const wmcv_size_t mask = alignment - 1;
	const wmcv_size_t result = (size + mask) & ~mask;
	return result;
}

[[nodiscard]] inline void* align_ptr(void* ptr, wmcv_size_t alignment) noexcept
{
	static_assert(std::is_same_v<std::underlying_type<uintptr_t>, std::underlying_type<wmcv_size_t>>);
	const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
	const uintptr_t aligned_address = align(address, alignment);
	return reinterpret_cast<void*>(aligned_address);
}

template<typename T>
[[nodiscard]] T* align_ptr(T* ptr, wmcv_size_t alignment) noexcept
{
	return static_cast<T*>(align_ptr(static_cast<void*>(ptr), alignment));
}

[[nodiscard]] constexpr bool is_aligned( wmcv_size_t size, wmcv_size_t alignment ) noexcept
{
	assert(is_power_of_2(alignment) && "Error: alignment isn't a power of 2");
	const bool result = ( size & (alignment - 1) ) == 0;
	return result;
}

[[nodiscard]] inline bool is_ptr_aligned( void* ptr, wmcv_size_t alignment ) noexcept
{
	assert(is_power_of_2(alignment) && "Error: alignment isn't a power of 2");
	const uintptr_t uintptr = reinterpret_cast<uintptr_t>(ptr);
	const bool result = is_aligned(uintptr, alignment);
	return result;
}

}

[[nodiscard]] constexpr wmcv_size_t operator""_kB(wmcv_size_t size)
{
	return size * 1024;
}

[[nodiscard]] constexpr wmcv_size_t operator""_MB(wmcv_size_t size)
{
	return size * 1024 * 1024;
}

[[nodiscard]] constexpr wmcv_size_t operator""_GB(wmcv_size_t size)
{
	return size * 1024 * 1024 * 1024;
}
