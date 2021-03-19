cmake_minimum_required(VERSION 3.0.0)
project(zinc)

include_directories(
    "src"
)

add_executable(
    example_stack
    "examples/example_stack.c"
)

if(ENABLE_TESTS)
    find_package(CMOCKA REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()