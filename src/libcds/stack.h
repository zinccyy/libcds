#ifndef LIBCDS_STACK_H_ONCE
#define LIBCDS_STACK_H_ONCE

#include <stdint.h>
#include <stdlib.h>

#define CDS_STACK_INCR 8

#define cds_stack(type)                                                                                                \
	struct {                                                                                                       \
		type tf;                                                                                               \
		type *mem;                                                                                             \
		uint64_t s;                                                                                            \
		uint64_t t;                                                                                            \
	}

#define cds_stack_init(st)                                                                                             \
	do {                                                                                                           \
		(st).s = 0;                                                                                            \
		(st).t = 0;                                                                                            \
		(st).mem = NULL;                                                                                       \
	} while (0)

#define cds_stack_push(st, elem)                                                                                       \
	do {                                                                                                           \
		if ((st).t == (st).s) {                                                                                \
			(st).s += CDS_STACK_INCR;                                                                      \
			(st).mem = realloc((st).mem, sizeof(typeof(((st).tf))) * ((st).s));                            \
		}                                                                                                      \
		(st).mem[(st).t] = elem;                                                                               \
		(st).t += 1;                                                                                           \
	} while (0)

#define cds_stack_valid(st) ((st).mem != NULL)

#define cds_stack_top(st) ((st).mem[(st).t])

#endif // LIBCDS_STACK_H_ONCE