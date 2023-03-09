#pragma once

#include "wmcv_allocator.h"

namespace wmcv
{
class ConcurrentLinearAllocator final : public Allocator
{
public:
	ConcurrentLinearAllocator(wmcv_size_t size);
	ConcurrentLinearAllocator(wmcv_size_t size, wmcv_byte* memory);
	~ConcurrentLinearAllocator() noexcept override final = default;

	void* allocate(wmcv_size_t size) noexcept override;
	void free(void*) noexcept override;

	wmcv_size_t get_marker() const noexcept;
	void reset() noexcept;

private:
	wmcv_byte* m_memory = nullptr;
	wmcv_atomic_size_t m_marker{};
	wmcv_size_t m_capacity{};
};
} // namespace wmcv