# Add tests
# test_lib
add_executable(test_lib test_lib.c)
add_test(NAME test_lib COMMAND test_lib)
target_link_libraries(test_lib ${PROJECT_NAME} cmocka)