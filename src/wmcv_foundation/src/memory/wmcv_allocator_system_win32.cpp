#include "wmcv_foundation_pch.h"

#include "foundation/memory/wmcv_allocator.h"
#include "foundation/wmcv_utility.h"

#ifdef WMCV_PLATFORM_WINDOWS

namespace wmcv
{

class SystemAllocatorWindows final : public Allocator
{
public:
	SystemAllocatorWindows() = default;
	~SystemAllocatorWindows() noexcept override = default;
	[[nodiscard]] void* allocate(wmcv_size_t size) noexcept override;
	void free(void* memory) noexcept override;
};

void* SystemAllocatorWindows::allocate(wmcv_size_t size) noexcept
{
	void* result = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	return result;
}

void SystemAllocatorWindows::free(void* memory) noexcept
{
	VirtualFree(memory, 0, MEM_RELEASE);
}

static Allocator* g_system_allocator = nullptr;
Allocator& get_system_allocator()
{
	assert(g_system_allocator && "System Allocator not yet created");
	return *g_system_allocator;
}

void set_system_allocator(Allocator* allocator)
{
	g_system_allocator = allocator;
}

void create_default_system_allocator()
{
	static SystemAllocatorWindows s_windows_system_allocator;
	set_system_allocator(&s_windows_system_allocator);
}

}

#endif
