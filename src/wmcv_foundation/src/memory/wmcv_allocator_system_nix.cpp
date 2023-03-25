
#include "wmcv_foundation_pch.h"

#include "foundation/memory/wmcv_allocator.h"
#include "foundation/wmcv_utility.h"

#include <cstdlib>

#if defined( WMCV_PLATFORM_APPLE ) || defined( WMCV_PLATFORM_LINUX )

namespace wmcv
{

class SystemAllocatorNix final : public Allocator
{
public:
	SystemAllocatorNix() = default;
	~SystemAllocatorNix() noexcept override = default;
	[[nodiscard]] void* allocate(wmcv_size_t size) noexcept override;
	void free(void* memory) noexcept override;
};

void* SystemAllocatorNix::allocate(wmcv_size_t size) noexcept
{
	void* result = malloc(size);
	return result;
}

void SystemAllocatorNix::free(void* memory) noexcept
{
	free(memory);
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
	static SystemAllocatorNix s_system_allocator;
	set_system_allocator(&s_system_allocator);
}

}

#endif
