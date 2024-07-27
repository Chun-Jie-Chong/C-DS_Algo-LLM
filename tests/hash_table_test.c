#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_table.c"

void test_insert_and_search() {
    HashTable *hashTable = create_table();

    insert(hashTable, "name", "John Doe");
    insert(hashTable, "occupation", "Software Developer");
    insert(hashTable, "language", "C");

    CU_ASSERT_STRING_EQUAL(search(hashTable, "name"), "John Doe");
    CU_ASSERT_STRING_EQUAL(search(hashTable, "occupation"), "Software Developer");
    CU_ASSERT_STRING_EQUAL(search(hashTable, "language"), "C");

    free_table(hashTable);
}

void test_delete() {
    HashTable *hashTable = create_table();

    insert(hashTable, "name", "John Doe");
    insert(hashTable, "occupation", "Software Developer");
    insert(hashTable, "language", "C");

    delete(hashTable, "name");
    CU_ASSERT_PTR_NULL(search(hashTable, "name"));

    free_table(hashTable);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashTable_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Test Insert and Search", test_insert_and_search);
    CU_add_test(suite, "Test Delete", test_delete);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}