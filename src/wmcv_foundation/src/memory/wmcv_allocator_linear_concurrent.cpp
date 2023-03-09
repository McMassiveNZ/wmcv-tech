#include "wmcv_foundation_pch.h"

#include "foundation/memory/wmcv_allocator_linear_concurrent.h"
#include "foundation/memory/wmcv_allocator_system.h"

namespace wmcv
{
ConcurrentLinearAllocator::ConcurrentLinearAllocator(wmcv_size_t size)
	: m_memory{static_cast<wmcv_byte*>(get_system_allocator().allocate(size))}
	, m_marker{0}
	, m_capacity{size}
{
}

ConcurrentLinearAllocator::ConcurrentLinearAllocator(wmcv_size_t size, wmcv_byte* memory)
	: m_memory{memory}
	, m_marker{0}
	, m_capacity{size}
{
}

void* ConcurrentLinearAllocator::allocate(wmcv_size_t size) noexcept
{
	const wmcv_size_t offset = m_marker.fetch_add(size, std::memory_order_relaxed);
	if (offset >= m_capacity)
		return nullptr;

	wmcv_byte* result = m_memory + offset;

	return static_cast<void*>(result);
}

void ConcurrentLinearAllocator::free(void*) noexcept
{
}

wmcv_size_t ConcurrentLinearAllocator::get_marker() const noexcept
{
	return m_marker.load();
}

void ConcurrentLinearAllocator::reset() noexcept
{
	m_marker.store(0ull);
}

} // namespace wmcv