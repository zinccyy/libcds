#ifndef LIBCDS_LINKED_LIST_H_ONCE
#define LIBCDS_LINKED_LIST_H_ONCE

/**
 * Helper #define for defining an entry for a list
 *
 * @param[in]   type            Type of a list
 *
 */
#define cds_linked_list_entry(type)  \
        struct entry {           \
                type d;          \
                struct entry *n; \
                struct entry *p; \
        }

#define cds_linked_list_cmp(type) int (*linked_list_cmp_func)(type v1, type v2)

/**
 * Use as 'linked_list(int) il;' to create a list
 *
 * @param[in]   type            Linked list type
 *
 */
#define cds_linked_list(type)                         \
        struct {                                  \
                linked_list_entry(type) * root;   \
                linked_list_entry(type) * first;  \
                linked_list_entry(type) * *curr;  \
                linked_list_entry(type) * last;   \
                linked_list_entry(type) * prev;   \
                linked_list_entry(type) * iter;   \
                linked_list_cmp(type) * cmp_func; \
        }

/**
 * Initializes given list fields to 0
 *
 * @param[in]   ls              List to init
 *
 */
#define cds_linked_list_init(ls)           \
        do {                           \
                ls->root = NULL;       \
                ls->first = NULL;      \
                ls->curr = &ls->first; \
                ls->last = NULL;       \
                ls->prev = NULL;       \
                ls->iter = NULL;       \
        } while (0)

/**
 * Adds a given item to the list
 *
 * @param[in]   ls              List to use
 * @param[in]   it              Item to add
 *
 */
#define cds_linked_list_add(ls, it)                             \
        do {                                                \
                *(ls->curr) = malloc(sizeof(**(ls->curr))); \
                if (ls->first == NULL) {                    \
                        ls->first = *(ls->curr);            \
                        ls->last = *(ls->curr);             \
                        ls->first->n = NULL;                \
                }                                           \
                (*(ls->curr))->n = NULL;                    \
                (*(ls->curr))->p = ls->prev;                \
                (*(ls->curr))->d = it;                      \
                ls->prev = *(ls->curr);                     \
                curr = &(*(ls->curr))->n;                   \
        } while (0)

#define cds_linked_list_del(ls, it)                                                         \
        do {                                                                            \
                for (ls->iter = ls->first; ls->iter != NULL; ls->iter = ls->iter->n;) { \
                        if (ls->cmp_func(ls->iter->d, it)) {                            \
                                ls->iter->p = ls->iter->n;                              \
                                if (ls->iter->n != NULL) {                              \
                                        ls->iter->n->p = ls->iter->p;                   \
                                }                                                       \
                                break;                                                  \
                        }                                                               \
                }                                                                       \
        } while (0)
#endif // LIBCDS_LINKED_LIST_H_ONCE