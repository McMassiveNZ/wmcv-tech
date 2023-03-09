#pragma once

#include "foundation/memory/wmcv_allocator.h"

namespace wmcv
{
Allocator& get_system_allocator();
void set_system_allocator(Allocator* allocator);
void create_default_system_allocator();
} // namespace wmcv