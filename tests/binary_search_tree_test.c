#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/binary_search_tree.c"

// Test case for inserting elements into the BST
void testInsert() {
    struct Node* root = NULL;
    root = insert(root, 50);
    CU_ASSERT_PTR_NOT_NULL(root);
    CU_ASSERT_EQUAL(root->data, 50);

    root = insert(root, 30);
    CU_ASSERT_PTR_NOT_NULL(root->left);
    CU_ASSERT_EQUAL(root->left->data, 30);

    root = insert(root, 20);
    CU_ASSERT_PTR_NOT_NULL(root->left->left);
    CU_ASSERT_EQUAL(root->left->left->data, 20);

    root = insert(root, 40);
    CU_ASSERT_PTR_NOT_NULL(root->left->right);
    CU_ASSERT_EQUAL(root->left->right->data, 40);

    root = insert(root, 70);
    CU_ASSERT_PTR_NOT_NULL(root->right);
    CU_ASSERT_EQUAL(root->right->data, 70);

    root = insert(root, 60);
    CU_ASSERT_PTR_NOT_NULL(root->right->left);
    CU_ASSERT_EQUAL(root->right->left->data, 60);

    root = insert(root, 80);
    CU_ASSERT_PTR_NOT_NULL(root->right->right);
    CU_ASSERT_EQUAL(root->right->right->data, 80);
}

// Test case for deleting elements from the BST
void testDelete() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    root = deleteNode(root, 20);
    CU_ASSERT_PTR_NULL(find(root, 20));

    root = deleteNode(root, 30);
    CU_ASSERT_PTR_NULL(find(root, 30));

    root = deleteNode(root, 50);
    CU_ASSERT_PTR_NULL(find(root, 50));
}

// Test case for finding elements in the BST
void testFind() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    struct Node* foundNode = find(root, 40);
    CU_ASSERT_PTR_NOT_NULL(foundNode);
    CU_ASSERT_EQUAL(foundNode->data, 40);

    foundNode = find(root, 90);
    CU_ASSERT_PTR_NULL(foundNode);
}

// Test case for in-order traversal of the BST
void testInOrderTraversal() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Redirect stdout to a file for capturing the output
    freopen("output.txt", "w", stdout);

    inOrder(root);

    // Close the file
    fclose(stdout);

    // Read the output from the file
    FILE* file = fopen("output.txt", "r");
    char output[100];
    fgets(output, sizeof(output), file);
    fclose(file);

    // Compare the output with the expected result
    CU_ASSERT_STRING_EQUAL(output, "20 30 40 50 60 70 80 ");
}

// Main function to run the test suite
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("BinarySearchTree_Test_Suite", 0, 0);
    CU_add_test(suite, "Test Insert", testInsert);
    CU_add_test(suite, "Test Delete", testDelete);
    CU_add_test(suite, "Test Find", testFind);
    // CU_add_test(suite, "Test In-Order Traversal", testInOrderTraversal);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}