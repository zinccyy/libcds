#ifndef LIBCDS_HASH_TABLE_H_ONCE
#define LIBCDS_HASH_TABLE_H_ONCE

#include <stdint.h>
#include <stdlib.h>
#include <libcds/linked_list.h>
#include <string.h>

// number of entries in a hash table -> each entry should be a linked list of values at certain position
#define CDS_HASH_TABLE_SIZE 256

/**
 * Helper struct for an entry of a hash table
 *
 * @param[in]           val_tp          Value type
 *
 */
#define cds_hash_table_entry(val_tp)                                                                                   \
	struct hash_table_entry_##val_tp {                                                                             \
		char *k;                                                                                               \
		val_tp v;                                                                                              \
	}

/**
 * Use as 'cds_hash_table(int) ht;' to create a hash table of (char *) -> int
 *
 * @param[in]           ent		Entry type - use previous macro to define one
 *
 */
#define cds_hash_table(ent)                                                                                            \
	struct hash_table_##ent {                                                                                      \
		ent ef;                                                                                                \
		cds_linked_list(ent) ell[CDS_HASH_TABLE_SIZE];                                                         \
	}

/**
 * Initializes the given hash table
 *
 * @param[in]		ht		Hash table	
 *
 */
#define cds_hash_table_init(ht)                                                                                        \
	do {                                                                                                           \
		for (int i = 0; i < CDS_HASH_TABLE_SIZE; i++) {                                                        \
			cds_linked_list_init((ht).ell[i]);                                                             \
		}                                                                                                      \
	} while (0)

/**
 * Calculates the position in a hash entry for a given key 'k'
 *
 * @param[in]   	k		Key type
 *
 */
int cds_hash_table_calc_pos(char *k);

/**
 * Adds an entry to a given hash table using key and val values
 *
 * @param[in]		ht		Hash table to use
 * @param[in]   	key_tp          Key type
 * @param[in]           val_tp          Value type
 *
 */
#define cds_hash_table_add(ht, key, val)                                                                               \
	do {                                                                                                           \
		int p = cds_hash_table_calc_pos((key));                                                                \
		typeof((ht).ef) e;                                                                                     \
		e.k = strdup(key);                                                                                     \
		e.v = val;                                                                                             \
		cds_linked_list_add_last((ht).ell[p], e);                                                              \
	} while (0)

/**
 * Gets an entry by a given key
 *
 * @param[in]		ht		Hash table to use
 * @param[in]   	key		Key value
 * @param[in]		en_ptr		Entry pointer -> used to store found entry if one found, or NULL otherwise
 *
 */
#define cds_hash_table_get(ht, key, en_ptr)                                                                            \
	do {                                                                                                           \
		typeof((ht).ef) *entr = NULL;                                                                          \
		int p = cds_hash_table_calc_pos(key);                                                                  \
		cds_linked_list_iter((ht).ell[p], itr)                                                                 \
		{                                                                                                      \
			if (strcmp(itr->d.k, key) == 0) {                                                              \
				entr = &itr->d;                                                                        \
				break;                                                                                 \
			}                                                                                              \
		}                                                                                                      \
		en_ptr = entr;                                                                                         \
	} while (0)

/**
 * Frees the given hash table
 *
 * @param[in]		ht		Hash table	
 *
 */
#define cds_hash_table_free(ht)                                                                                        \
	do {                                                                                                           \
		for (int i = 0; i < CDS_HASH_TABLE_SIZE; i++) {                                                        \
			cds_linked_list_iter((ht).ell[i], it)                                                          \
			{                                                                                              \
				free(it->d.k);                                                                         \
			}                                                                                              \
			cds_linked_list_free((ht).ell[i]);                                                             \
		}                                                                                                      \
	} while (0)

#endif // LIBCDS_HASH_TABLE_H_ONCE