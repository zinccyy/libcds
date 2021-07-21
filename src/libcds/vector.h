#ifndef LIBCDS_VECTOR_H_ONCE
#define LIBCDS_VECTOR_H_ONCE

#include <stdint.h>
#include <stdlib.h>

/**
 * Use as 'cds_vector(int) iv;' to create a vector
 *
 * @param[in]   	type		vector type
 *
 */
#define cds_vector(type)                                                                                               \
    struct cds_vec_##type                                                                                              \
    {                                                                                                                  \
        type tf;                                                                                                       \
        type *mem;                                                                                                     \
        uint64_t s;                                                                                                    \
    }

/**
 * initializes given vector fields to 0
 *
 * @param[in]		vec		vector to init
 *
 */
#define cds_vector_init(vec)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        (vec).mem = NULL;                                                                                              \
        (vec).s = 0;                                                                                                   \
    } while (0)

/**
 * returns the variable at a given position if one exists
 *
 * @param[in]		vec     vector to use
 * @param[in]       pos     position to get
 * @param[in]       ptr     pointer to store the variable to, if no value exists - NULL is set to that pointer
 *
 */
#define cds_vector_get(vec, pos, ptr)                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        ptr = NULL;                                                                                                    \
        if ((pos) < (vec).s && (pos) >= 0)                                                                             \
        {                                                                                                              \
            ptr = &(vec).mem[(pos)];                                                                                   \
        }                                                                                                              \
    } while (0)

/**
 * pushes the value to the back of the vector
 *
 * @param[in]		st		vector to use
 * @param[in]       val     value to push
 *
 */
#define cds_vector_push_back(vec, val)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        (vec).mem = realloc((vec).mem, sizeof((vec).tf) * ((vec).s + 1));                                              \
        (vec).mem[(vec).s] = val;                                                                                      \
        (vec).s += 1;                                                                                                  \
    } while (0)

/**
 * pushes the value to the front of the vector
 *
 * @param[in]		vec		vector to use
 * @param[in]       val     value to push
 *
 */
#define cds_vector_push_front(vec, val)                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        (vec).mem = realloc((vec).mem, sizeof((vec).tf) * ((vec).s + 1));                                              \
        (vec).s += 1;                                                                                                  \
        for (uint64_t i = (vec).s - 1; i > 0; i--)                                                                     \
            (vec).mem[i] = (vec).mem[i - 1];                                                                           \
        (vec).mem[0] = val;                                                                                            \
    } while (0)

/**
 * frees the given vector memory
 *
 * @param[in]		vec     vector to free
 *
 */
#define cds_vector_free(vec)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        free((vec).mem);                                                                                               \
        cds_vector_init(vec);                                                                                          \
    } while (0)

#endif // LIBCDS_VECTOR_H_ONCE