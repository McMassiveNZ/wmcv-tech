#include "wmcv_foundation_pch.h"

#include "foundation/wmcv_utility.h"
#include "foundation/memory/wmcv_allocator_linear.h"
#include "foundation/memory/wmcv_allocator_system.h"

namespace wmcv
{
LinearAllocator::LinearAllocator(wmcv_size_t size)
	: m_memory{static_cast<wmcv_byte*>(get_system_allocator().allocate(size))}
	, m_marker{0}
	, m_capacity{size}
{
}

LinearAllocator::LinearAllocator(wmcv_size_t size, wmcv_byte* memory)
	: m_memory{memory}
	, m_marker{0}
	, m_capacity{size}
{
}

void* LinearAllocator::allocate(wmcv_size_t size) noexcept
{
	const wmcv_size_t offset = std::exchange(m_marker, m_marker + size);
	if (offset >= m_capacity)
		return nullptr;

	wmcv_byte* result = m_memory + offset;
	return static_cast<void*>(result);
}

void LinearAllocator::free(void*) noexcept
{
}

wmcv_size_t LinearAllocator::get_marker() const noexcept
{
	return m_marker;
}

void LinearAllocator::reset() noexcept
{
	m_marker = 0ull;
}

} // namespace wmcv