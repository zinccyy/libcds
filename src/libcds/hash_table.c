#include <libcds/hash_table.h>
#include <string.h>

/**
 * Calculates the position in a hash entry for a given key 'k'
 *
 * @param[in]   	k		Key type
 *
 */
int cds_hash_table_calc_pos(char *k)
{
    int pos = 0;
    char *k_ptr = 0;
    for (k_ptr = k; *k != 0; k++)
    {
        pos += (int)(*k);
    }
    pos %= CDS_HASH_TABLE_SIZE;
    return pos;
}