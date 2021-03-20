#ifndef LIBCDS_LINKED_LIST_H_ONCE
#define LIBCDS_LINKED_LIST_H_ONCE

/**
 * Helper #define for defining an entry for a list
 *
 * @param[in]		type            Type of a list
 *
 */
#define cds_linked_list_entry(type)                                                                                    \
	struct linked_list_entry_##type {                                                                              \
		type d;                                                                                                \
		struct linked_list_entry_##type *n;                                                                    \
		struct linked_list_entry_##type *p;                                                                    \
	}

/**
 * Use as 'cds_linked_list(int) il;' to create a list
 *
 * @param[in]		type            Linked list type
 *
 */
#define cds_linked_list(type)                                                                                          \
	struct linked_list_##type {                                                                                    \
		type tf;                                                                                               \
		cds_linked_list_entry(type) * head, *end;                                                              \
	}
/**
 * Initialize the given linked list to NULL
 *
 * @param[in]		type            Linked list to init
 *
 */
#define cds_linked_list_init(ll)                                                                                       \
	do {                                                                                                           \
		(ll).head = NULL;                                                                                      \
		(ll).end = NULL;                                                                                       \
	} while (0)

/**
 * Adds a given value to the front of the list
 *
 * @param[in]		ll		Linked list
 * @param[in]		val		Value to add
 *
 */
#define cds_linked_list_add_first(ll, val)                                                                             \
	do {                                                                                                           \
		typeof((ll).head) nn = malloc(sizeof((ll).tf) + sizeof((ll).head) * 2);                                \
		nn->d = val;                                                                                           \
		nn->p = NULL;                                                                                          \
		nn->n = (ll).head;                                                                                     \
		if ((ll).head == NULL) {                                                                               \
			(ll).end = nn;                                                                                 \
		}                                                                                                      \
		(ll).head = nn;                                                                                        \
	} while (0)

/**
 * Adds a given value to the end of the list
 *
 * @param[in]		ll		Linked list
 * @param[in]		val		Value to add
 *
 */
#define cds_linked_list_add_last(ll, val)                                                                              \
	do {                                                                                                           \
		typeof((ll).head) nn = malloc(sizeof((ll).tf) + sizeof((ll).head) * 2);                                \
		nn->d = val;                                                                                           \
		if ((ll).end == NULL) {                                                                                \
			cds_linked_list_add_first(ll, val);                                                            \
		} else {                                                                                               \
			(ll).end->n = nn;                                                                              \
			nn->p = (ll).end;                                                                              \
			(ll).end = nn;                                                                                 \
		}                                                                                                      \
	} while (0)

#define cds_linked_list_iter(ll, vn) for (typeof((ll).head) vn = (ll).head; vn != NULL; vn = (vn)->n)

/**
 * Free the given list contents
 *
 * @param[in]		ll		List to free
 *
 */
#define cds_linked_list_free(ll)                                                                                       \
	do {                                                                                                           \
		typeof((ll).head) nd = (ll).head;                                                                      \
		typeof((ll).head) nx = NULL;                                                                           \
		while (nd) {                                                                                           \
			nx = nd->n;                                                                                    \
			free(nd);                                                                                      \
			nd = nx;                                                                                       \
		}                                                                                                      \
	} while (0)
#endif // LIBCDS_LINKED_LIST_H_ONCE