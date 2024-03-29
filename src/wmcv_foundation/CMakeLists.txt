set(SOURCE_FILES)

set(FOUNDATION_SOURCE_FILES
	include/foundation/wmcv_utility.h
	include/foundation/wmcv_types.h
	include/wmcv_foundation_pch.h
)

set(MEMORY_SOURCE_FILES
	include/foundation/memory/wmcv_allocator.h
	include/foundation/memory/wmcv_allocator_linear.h
	include/foundation/memory/wmcv_allocator_linear_concurrent.h
	include/foundation/memory/wmcv_allocator_system.h
	src/memory/wmcv_allocator.cpp
	src/memory/wmcv_allocator_linear.cpp
	src/memory/wmcv_allocator_linear_concurrent.cpp
)

if(MSVC)
    set(MEMORY_SOURCE_FILES_WINDOWS
        src/memory/wmcv_allocator_system_win32.cpp
    )
    list(APPEND MEMORY_SOURCE_FILES ${MEMORY_SOURCE_FILES_WINDOWS})
elseif(UNIX)
    set(MEMORY_SOURCE_FILES_NIX
        src/memory/wmcv_allocator_system_nix.cpp
    )
    list(APPEND MEMORY_SOURCE_FILES ${MEMORY_SOURCE_FILES_NIX})
endif()

source_group("" FILES ${FOUNDATION_SOURCE_FILES})
source_group("memory" FILES ${MEMORY_SOURCE_FILES})

list(APPEND SOURCE_FILES ${FOUNDATION_SOURCE_FILES})
list(APPEND SOURCE_FILES ${MEMORY_SOURCE_FILES})

#todo maybe provide the option to build a shared lib
add_library(wmcv_foundation STATIC ${SOURCE_FILES})

target_include_directories(wmcv_foundation PUBLIC include)
target_compile_definitions(wmcv_foundation PUBLIC ${WMCV_PLATFORM})
target_precompile_headers(wmcv_foundation PRIVATE include/wmcv_foundation_pch.h)
