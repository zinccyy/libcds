#include <libcds.h>
#include <stdio.h>

// typedef your created stacks -> used for portability and to enable creating many stacks of the same type
typedef cds_stack(int) intstack_t;

void print_top(intstack_t *s)
{
	printf("top: %d\n", cds_stack_top(*s));
}

int main(int argc, char **argv)
{
	// if a type contains a pointer -> typedef type to another type (needs to be used that way because of the cds_stack() definition definition)
	// for example: char *
	typedef char *str_t;
	// now use with the stack
	typedef cds_stack(str_t) strstack_t;

	intstack_t is;
	strstack_t ss;
	int top = 0;

	cds_stack_init(is);

	cds_stack_push(is, 1);
	cds_stack_push(is, 2);

	if (cds_stack_valid(is)) {
		print_top(&is);
		cds_stack_pop(is);
		print_top(&is);
		cds_stack_pop(is);
	}

	cds_stack_free(is);
	return 0;
}