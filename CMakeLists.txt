cmake_minimum_required(VERSION 3.23)

project(wmcv-tech VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
OPTION(ENABLE_TESTS "Enable Unit Tests" ON)
OPTION(ENABLE_ALL_REASONABLE_WARNINGS "Enable all possible reasonable warnings" ON )
OPTION(ENABLE_WARNINGS_AS_ERRORS "Warnings are treated as Errors" ON)
OPTION(ENABLE_STATIC_ANALYSIS "Enable Static Analysis Tools" ON)
OPTION(ENABLE_SANITIZERS "Enable Sanitizer Tools" ON)
OPTION(ENABLE_TRACY_PROFILER "Enable Tracy Profiler" OFF)

set(CMAKE_SCRIPTS_DIR ${CMAKE_CURRENT_LIST_DIR}/scripts/cmake)

if(MSVC)
    set(WMCV_PLATFORM WMCV_PLATFORM_WINDOWS)
elseif(APPLE)
    set(WMCV_PLATFORM WMCV_PLATFORM_APPLE)
elseif(ANDROID)
    set(WMCV_PLATFORM WMCV_PLATFORM_ANDROID)
elseif(UNIX AND NOT APPLE)
    set(WMCV_PLATFORM WMCV_PLATFORM_LINUX)
else()
    set(WMCV_PLATFORM WMCV_PLATFORM_UNKNOWN)
endif()

include(${CMAKE_SCRIPTS_DIR}/compilerwarnings.cmake)
include(${CMAKE_SCRIPTS_DIR}/sanitizers.cmake)
include(${CMAKE_SCRIPTS_DIR}/staticanalysis.cmake)

if (ENABLE_TESTS)
    message("-- Unit Testing Enabled")
    enable_testing()
    add_subdirectory(test)
endif()

add_subdirectory(src)
