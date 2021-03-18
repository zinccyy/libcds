# Add tests
# test_stack
add_executable(test_stack test_stack.c)
add_test(NAME test_stack COMMAND test_stack)
target_link_libraries(test_stack cmocka)