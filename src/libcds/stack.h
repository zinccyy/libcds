#ifndef LIBCDS_STACK_H_ONCE
#define LIBCDS_STACK_H_ONCE

#include <stdint.h>
#include <stdlib.h>

#define CDS_STACK_INCR 8

/**
 * use as 'cds_stack(int) is;' to create a stack
 *
 * @param[in]   	type		stack type
 *
 */
#define cds_stack(type)                                                                                                \
    struct stack_##type                                                                                                \
    {                                                                                                                  \
        type tf;                                                                                                       \
        type *mem;                                                                                                     \
        uint64_t s;                                                                                                    \
        uint64_t t;                                                                                                    \
    }

/**
 * initializes given stack fields to 0
 *
 * @param[in]		st		stack to init
 *
 */
#define cds_stack_init(st)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        (st).s = 0;                                                                                                    \
        (st).t = 0;                                                                                                    \
        (st).mem = NULL;                                                                                               \
    } while (0)

/**
 * push a given element to the stack
 *
 * @param[in]		st			stack to use
 * @param[in]		elem		element to push on stack
 *
 */
#define cds_stack_push(st, elem)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((st).t == (st).s)                                                                                          \
        {                                                                                                              \
            (st).s += CDS_STACK_INCR;                                                                                  \
            (st).mem = realloc((st).mem, sizeof(typeof(((st).tf))) * ((st).s));                                        \
        }                                                                                                              \
        (st).mem[(st).t] = elem;                                                                                       \
        (st).t += 1;                                                                                                   \
    } while (0)

/**
 * check if a given stack is valid for use
 *
 * @param[in]		st			stack to check
 *
 * @param[out]		valid		1 if stack is valid, 0 otherwise
 *
 */
#define cds_stack_valid(st) ((st).mem != NULL && (st).t > 0)

/**
 * get the top element of the stack - first the user needs to check wether a given stack is valid
 *
 * @param[in]		st		stack to use
 *
 * @param[out]		t		top element
 *
 */
#define cds_stack_top(st) ((st).mem[(st).t - 1])

/**
 * pops the last element from the stack if possible -> if top > 0
 *
 * @param[in]		st		stack to use
 *
 */
#define cds_stack_pop(st)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((st).t > 0)                                                                                                \
        {                                                                                                              \
            (st).t--;                                                                                                  \
        }                                                                                                              \
    } while (0)

/**
 * frees the given stack memory
 *
 * @param[in]		st		stack to free
 *
 */
#define cds_stack_free(st)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        free((st).mem);                                                                                                \
        cds_stack_init(st);                                                                                            \
    } while (0)

#endif // LIBCDS_STACK_H_ONCE