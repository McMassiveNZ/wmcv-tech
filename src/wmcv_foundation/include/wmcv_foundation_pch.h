#pragma once

#ifdef WMCV_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xmmintrin.h>
#endif

#include <cinttypes>
#include <cmath>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <atomic>
#include <utility>

#include "foundation/wmcv_types.h"
