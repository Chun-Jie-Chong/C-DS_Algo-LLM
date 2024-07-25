#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/doubly_linkedlist.c"

void testInsert() {
    List *list = NULL;

    // Test inserting at the beginning
    list = insert(list, 10.5, 0);
    CU_ASSERT_EQUAL(list->value, 10.5);
    CU_ASSERT_PTR_NULL(list->prev);
    CU_ASSERT_PTR_NULL(list->next);

    // Test inserting at the end
    list = insert(list, 20.5, 1);
    CU_ASSERT_EQUAL(list->next->value, 20.5);
    CU_ASSERT_EQUAL(list->next->prev->value, 10.5);
    CU_ASSERT_PTR_NULL(list->next->next);

    // Test inserting at a specific position
    list = insert(list, 15.5, 1);
    CU_ASSERT_EQUAL(list->next->value, 15.5);
    CU_ASSERT_EQUAL(list->next->prev->value, 10.5);
    CU_ASSERT_EQUAL(list->next->next->value, 20.5);

    // Test inserting at an invalid position
    // list = insert(list, 25.5, 5);
    // CU_ASSERT_EQUAL(list->next->next->next->value, 25.5);
    // CU_ASSERT_EQUAL(list->next->next->next->prev->value, 20.5);
    // CU_ASSERT_PTR_NULL(list->next->next->next->next);
}

void testDelete() {
    List *list = NULL;

    // Test deleting from an empty list
    list = delete(list, 0);
    CU_ASSERT_PTR_NULL(list);

    // Test deleting the only node
    list = insert(list, 10.5, 0);
    list = delete(list, 0);
    CU_ASSERT_PTR_NULL(list);

    // Test deleting from the beginning
    list = insert(list, 10.5, 0);
    list = insert(list, 20.5, 1);
    list = delete(list, 0);
    CU_ASSERT_EQUAL(list->value, 20.5);
    CU_ASSERT_PTR_NULL(list->prev);
    CU_ASSERT_PTR_NULL(list->next);
    // 20.5 -> NULL

    // Test deleting from the end
    list = insert(list, 10.5, 0);
    list = insert(list, 20.5, 1);
    list = delete(list, 1);
    // 10.5 <-> 20.5
    CU_ASSERT_EQUAL(list->value, 10.5);
    CU_ASSERT_PTR_NULL(list->prev);
    CU_ASSERT_EQUAL(list->next->value, 20.5);

    // Test deleting from a specific position
    list = insert(list, 10.5, 0);
    // 10.5 <-> 10.5 <-> 20.5
    list = insert(list, 20.5, 1);
    // 10.5 <-> 20.5 <-> 10.5 <-> 20.5
    list = insert(list, 15.5, 1);
    // 10.5 <-> 15.5 <-> 20.5 <-> 10.5 <-> 20.5
    list = delete(list, 1);
    // 10.5 <-> 20.5 <-> 10.5 <-> 20.5
    CU_ASSERT_EQUAL(list->next->value, 20.5);
    CU_ASSERT_EQUAL(list->next->prev->value, 10.5);
    CU_ASSERT_PTR_NULL(list->next->next->next->next);

    // Test deleting from an invalid position
    // list = delete(list, 5);
    // CU_ASSERT_EQUAL(list->next->value, 20.5);
    // CU_ASSERT_EQUAL(list->next->prev->value, 10.5);
    // CU_ASSERT_PTR_NULL(list->next->next);
}

void testSearch() {
    List *list = NULL;

    // Test searching in an empty list
    int pos = search(list, 10.5);
    CU_ASSERT_EQUAL(pos, -1);

    // Test searching for a value that exists
    list = insert(list, 10.5, 0);
    list = insert(list, 20.5, 1);
    list = insert(list, 15.5, 1);
    // 10.5 <-> 15.5 <-> 20.5
    pos = search(list, 20.5);
    CU_ASSERT_EQUAL(pos, 2);

    // Test searching for a value that doesn't exist
    pos = search(list, 25.5);
    CU_ASSERT_EQUAL(pos, -1);
}

void testPrint() {
    List *list = NULL;

    // Test printing an empty list
    CU_ASSERT_EQUAL(list, NULL);

    // Test printing a list with nodes
    list = insert(list, 10.5, 0);
    list = insert(list, 20.5, 1);
    list = insert(list, 15.5, 1);
    CU_ASSERT_EQUAL(list->value, 10.5);
    CU_ASSERT_EQUAL(list->next->value, 15.5);
    CU_ASSERT_EQUAL(list->next->next->value, 20.5);
    CU_ASSERT_PTR_NULL(list->next->next->next);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Doubly_LinkedList_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Insert Test", testInsert);
    CU_add_test(suite, "Delete Test", testDelete);
    CU_add_test(suite, "Search Test", testSearch);
    // CU_add_test(suite, "Print Test", testPrint);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}