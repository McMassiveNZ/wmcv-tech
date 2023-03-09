#include "wmcv_foundation_pch.h"
#include "foundation/memory/wmcv_allocator.h"
#include "foundation/wmcv_utility.h"

namespace wmcv
{

static constexpr wmcv_size_t default_alignment = 4;

Allocator& get_system_allocator();
void set_system_allocator(Allocator&);
void create_default_system_allocator();

}


void wmcv_allocator_create()
{
	wmcv::create_default_system_allocator();
}

void wmcv_allocator_destroy()
{
}

void* wmcv_allocate(wmcv::Allocator& allocator, wmcv_size_t size)
{
	return allocator.allocate(size);
}

void* wmcv_allocate_aligned(wmcv::Allocator& allocator, wmcv_size_t size, wmcv_size_t alignment)
{
	const wmcv_size_t actual_bytes = size + alignment;

	wmcv_u8* raw_memory = static_cast<wmcv_u8*>(allocator.allocate(actual_bytes));
	wmcv_u8* aligned_memory = wmcv::align_ptr<wmcv_u8>(raw_memory, alignment);

	if (raw_memory == aligned_memory)
		aligned_memory += alignment;

	ptrdiff_t shift = aligned_memory - raw_memory;
	assert(shift > 0 && shift <= 0x100);
	aligned_memory[-1] = static_cast<wmcv_u8>(shift & 0xFF);
	return aligned_memory;
}

void wmcv_free(wmcv::Allocator& allocator, void* memory)
{
	if (memory)
	{
		allocator.free(memory);
	}
}

void wmcv_free_aligned(wmcv::Allocator& allocator, void* memory, wmcv_size_t alignment)
{
	if (memory)
	{
		wmcv_u8* aligned_memory = static_cast<wmcv_u8*>(memory);
		ptrdiff_t shift = aligned_memory[-1];

		if (shift == 0)
			shift = 0x100;

		void* raw_memory = static_cast<void*>(aligned_memory - shift);
		allocator.free(raw_memory);
	}
}