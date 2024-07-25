#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/singly_linkedlist.c"

void testInsertion() {
    struct Node* head = NULL;
    
    // Insert at position 0
    insert(&head, 0, 1);
    CU_ASSERT_EQUAL(head->data, 1);
    CU_ASSERT_PTR_NULL(head->next);
    
    // Insert at position 1
    insert(&head, 1, 2);
    CU_ASSERT_EQUAL(head->next->data, 2);
    CU_ASSERT_PTR_NULL(head->next->next);
    
    // Insert at position 2
    insert(&head, 2, 3);
    CU_ASSERT_EQUAL(head->next->next->data, 3);
    CU_ASSERT_PTR_NULL(head->next->next->next);
    
    // Insert at position 1
    insert(&head, 1, 4);
    CU_ASSERT_EQUAL(head->next->data, 4);
    CU_ASSERT_EQUAL(head->next->next->data, 2);
    CU_ASSERT_EQUAL(head->next->next->next->data, 3);
    CU_ASSERT_PTR_NULL(head->next->next->next->next);
}

void testDeletion() {
    struct Node* head = NULL;
    
    // Insert nodes for deletion
    insert(&head, 0, 1);
    insert(&head, 1, 2);
    insert(&head, 2, 3);
    insert(&head, 1, 4);
    // 1 ->4 ->2 ->3 ->NULL
    // Delete at position 2
    // 1 ->4 ->3 ->NULL
    deletion(&head, 2);
    CU_ASSERT_EQUAL(head->data, 1);
    CU_ASSERT_EQUAL(head->next->data, 4);
    CU_ASSERT_EQUAL(head->next->next->data, 3);
    CU_ASSERT_PTR_NULL(head->next->next->next);
    
    // Delete at position 0
    // 4 ->3 ->NULL
    deletion(&head, 0);
    CU_ASSERT_EQUAL(head->data, 4);
    CU_ASSERT_EQUAL(head->next->data, 3);
    CU_ASSERT_PTR_NULL(head->next->next);
}

void testViewList() {
    struct Node* head = NULL;
    
    // Insert nodes for viewing
    insert(&head, 0, 1);
    insert(&head, 1, 2);
    insert(&head, 2, 3);
    insert(&head, 1, 4);
    
    // Capture the output of viewList
    freopen("output.txt", "w", stdout);
    viewList(head);
    fclose(stdout);
    
    // Read the output from the file
    FILE* file = fopen("output.txt", "r");
    char output[100];
    fgets(output, sizeof(output), file);
    fclose(file);
    
    // Verify the output
    CU_ASSERT_STRING_EQUAL(output, "1 -> 4 -> 2 -> 3 -> NULL\n");
}

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("SinglyLinkedList_Test_Suite", NULL, NULL);
    CU_add_test(suite, "testInsertion", testInsertion);
    CU_add_test(suite, "testDeletion", testDeletion);
    // CU_add_test(suite, "testViewList", testViewList);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    CU_cleanup_registry();
    
    return CU_get_error();
}