include(${CMAKE_SCRIPTS_DIR}/googletest.cmake)

add_executable(
  wmcv-test
  wmcv_test_pch.h
  memory/test_utility.cpp
  memory/test_allocator.cpp
  memory/test_system_allocator.cpp
  memory/test_linear_allocator.cpp
  memory/test_allocator_mock.h
)

target_link_libraries(
  wmcv-test PRIVATE 
  gtest_main
  gmock_main
  wmcv_foundation
)

target_include_directories(wmcv-test PUBLIC .)
target_precompile_headers(wmcv-test PRIVATE wmcv_test_pch.h)

include(GoogleTest)
gtest_discover_tests(wmcv-test)
