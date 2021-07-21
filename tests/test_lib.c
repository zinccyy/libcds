#include <libcds.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

void test_stack(void **state);
void test_linked_list(void **state);
void test_hash_table(void **state);
void test_vector_correct(void **state);
void test_vector_incorrect(void **state);

int main()
{
    const struct CMUnitTest test_groups[] = {
        cmocka_unit_test(test_stack),
        cmocka_unit_test(test_linked_list),
        cmocka_unit_test(test_hash_table),
        cmocka_unit_test(test_vector_correct),
        cmocka_unit_test(test_vector_incorrect),
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

    if (cds_stack_valid(s1))
    {
        int a = cds_stack_top(s1);
        assert_int_equal(a, 30);
    }

    cds_stack_free(s1);
}

void test_linked_list(void **state)
{
    typedef cds_linked_list(int) dll_int_t;

    dll_int_t il;
    cds_linked_list_init(il);

    cds_linked_list_add_last(il, 10);
    cds_linked_list_add_last(il, 20);
    cds_linked_list_add_first(il, 30);

    cds_linked_list_free(il);
}

void test_hash_table(void **state)
{
    typedef cds_hash_table_entry(int) hte_int_t;
    typedef cds_hash_table(hte_int_t) ht_int_t;

    ht_int_t ht;

    cds_hash_table_init(ht);

    cds_hash_table_add(ht, "key1", 10);
    cds_hash_table_add(ht, "key2", 20);
    cds_hash_table_add(ht, "key3", 30);

    hte_int_t *e = NULL;

    cds_hash_table_get(ht, "key2", e);

    assert_non_null(e);

    // printf("[e]: %s = %d\n", e->k, e->v);

    cds_hash_table_free(ht);
}

void test_vector_correct(void **state)
{
    typedef cds_vector(int) vecint_t;
    vecint_t v1;
    vecint_t v2;
    int *tmp_ptr = NULL;

    cds_vector_init(v1);
    cds_vector_push_back(v1, 10);
    cds_vector_push_back(v1, 20);
    cds_vector_push_back(v1, 30);

    // assert correct position handling
    cds_vector_get(v1, 2, tmp_ptr);
    assert_non_null(tmp_ptr);
    assert_int_equal(*tmp_ptr, 30);

    cds_vector_get(v1, 0, tmp_ptr);
    assert_non_null(tmp_ptr);
    assert_int_equal(*tmp_ptr, 10);

    // push to front and assert again
    cds_vector_push_front(v1, 40);

    cds_vector_get(v1, 0, tmp_ptr);
    assert_non_null(tmp_ptr);
    assert_int_equal(*tmp_ptr, 40);

    cds_vector_get(v1, 1, tmp_ptr);
    assert_non_null(tmp_ptr);
    assert_int_equal(*tmp_ptr, 10);

    cds_vector_free(v1);
}

void test_vector_incorrect(void **state)
{
    typedef cds_vector(int) vecint_t;
    vecint_t v1;
    vecint_t v2;
    int *tmp_ptr = NULL;

    cds_vector_init(v1);
    cds_vector_push_back(v1, 10);
    cds_vector_push_back(v1, 20);
    cds_vector_push_back(v1, 30);

    // assert incorrect getting of a variable
    cds_vector_get(v1, 3, tmp_ptr);
    assert_null(tmp_ptr);

    cds_vector_get(v1, -1, tmp_ptr);
    assert_null(tmp_ptr);

    cds_vector_free(v1);
}