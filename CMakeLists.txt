cmake_minimum_required(VERSION 3.0.0)
project(cds)

include_directories(
    "src"
)

add_library(
    ${PROJECT_NAME}
    SHARED
    "src/libcds/hash_table.c"
)

add_executable(
    example_stack
    "examples/example_stack.c"
)

target_link_libraries(
    example_stack
    ${PROJECT_NAME}
)

if(ENABLE_TESTS)
    find_package(CMOCKA REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()