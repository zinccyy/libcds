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
	typedef cds_stack(int) stackint_t;
	stackint_t s1;

	cds_stack_init(s1);

	cds_stack_push(s1, 10);
	cds_stack_push(s1, 20);
	cds_stack_push(s1, 30);

	if (cds_stack_valid(s1)) {
		int a = cds_stack_top(s1);
		assert_int_equal(a, 30);
	}

	cds_stack_free(s1);
}