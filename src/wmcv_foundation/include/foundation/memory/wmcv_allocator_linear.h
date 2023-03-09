#pragma once

#include "wmcv_allocator.h"

namespace wmcv
{
class LinearAllocator final : public Allocator
{
public:
	LinearAllocator(wmcv_size_t size);
	LinearAllocator(wmcv_size_t size, wmcv_byte* memory);
	~LinearAllocator() noexcept override = default;

	void* allocate(wmcv_size_t size) noexcept override;
	void free(void*) noexcept override;

	wmcv_size_t get_marker() const noexcept;
	void reset() noexcept;

private:
	wmcv_byte* m_memory = nullptr;
	wmcv_size_t m_marker{};
	wmcv_size_t m_capacity{};
};
} // namespace wmcv