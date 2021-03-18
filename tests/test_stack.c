#include <libcds.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_stack(void **state);

int main()
{
	const struct CMUnitTest test_groups[] = {
		cmocka_unit_test(test_stack),
	};

	// results of group testing
	return cmocka_run_group_tests(test_groups, 0, 0);
	return 0;
}

void test_stack(void **state)
{
	cds_stack(int) is;
	cds_stack_push(is, 10);
	cds_stack_push(is, 20);
	cds_stack_push(is, 30);

	if (cds_stack_valid(is)) {
		int a = cds_stack_top(is);
		assert_int_equal(a, 30);
	}
}