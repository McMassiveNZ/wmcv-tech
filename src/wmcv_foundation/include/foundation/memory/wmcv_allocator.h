#pragma once

namespace wmcv
{

class Allocator
{
public:
	[[nodiscard]] virtual void* allocate(wmcv_size_t size) noexcept = 0;
	virtual void free(void* p) noexcept = 0;

	Allocator(const Allocator&) = delete;
	Allocator(Allocator&&) = delete;
	Allocator& operator=(const Allocator&) = delete;
	Allocator& operator=(Allocator&&) = delete;

protected:
	Allocator() = default;
	virtual ~Allocator() = default;
};

} // namespace wmcv

void wmcv_allocator_create();
void wmcv_allocator_destroy();

void* wmcv_allocate(wmcv::Allocator& allocator, wmcv_size_t size);
void* wmcv_allocate_aligned(wmcv::Allocator& allocator, wmcv_size_t size, wmcv_size_t alignment);
void wmcv_free(wmcv::Allocator& allocator, void* memory);
void wmcv_free_aligned(wmcv::Allocator& allocator, void* memory, wmcv_size_t alignment);

