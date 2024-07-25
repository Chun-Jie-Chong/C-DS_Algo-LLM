#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/avl_tree.c"

// Test case for inserting nodes into the AVL tree
void testInsert() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Check if nodes are inserted correctly
    //           30
    //        /      \
    //     20          40
    //   /   \           \
    // 10      25          50
    // CU_ASSERT_EQUAL(root->key, 20);
    CU_ASSERT_EQUAL(root->key, 30);
    CU_ASSERT_EQUAL(root->left->key, 20);
    CU_ASSERT_EQUAL(root->right->key, 40);
    CU_ASSERT_EQUAL(root->right->right->key, 50);
    CU_ASSERT_EQUAL(root->left->left->key, 10);
    CU_ASSERT_EQUAL(root->left->right->key, 25);
}

// Test case for deleting a node from the AVL tree
void testDelete() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Delete a node
    root = deleteNode(root, 10);

    // Check if node is deleted correctly
    CU_ASSERT_EQUAL(root->key, 30);
    CU_ASSERT_EQUAL(root->left->key, 20);
    CU_ASSERT_EQUAL(root->right->key, 40);
    CU_ASSERT_EQUAL(root->left->left, NULL);
    CU_ASSERT_EQUAL(root->left->right->key, 25);
    CU_ASSERT_EQUAL(root->right->right->key, 50);
}

// Test case for finding a node in the AVL tree
void testFindNode() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Find a node
    Node* foundNode = findNode(root, 40);

    // Check if node is found correctly
    CU_ASSERT_EQUAL(foundNode->key, 40);
    CU_ASSERT_EQUAL(foundNode->left, NULL);
    CU_ASSERT_EQUAL(foundNode->right->key, 50);
}

// Test case for printing the AVL tree in preorder
void testPrintPreOrder() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print tree in preorder
    printf("Preorder traversal of the constructed AVL tree is:\n");
    printPreOrder(root);
    printf("\n");
}

// Test case for printing the AVL tree in inorder
void testPrintInOrder() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print tree in inorder
    printf("Inorder traversal of the constructed AVL tree is:\n");
    printInOrder(root);
    printf("\n");
}

// Test case for printing the AVL tree in postorder
void testPrintPostOrder() {
    Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print tree in postorder
    printf("Postorder traversal of the constructed AVL tree is:\n");
    printPostOrder(root);
    printf("\n");
}

// Main function to run the test cases
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("AVLTree_Test_Suite", 0, 0);
    CU_add_test(suite, "Test Insert", testInsert);
    CU_add_test(suite, "Test Delete", testDelete);
    CU_add_test(suite, "Test Find Node", testFindNode);
    // CU_add_test(suite, "Test Print Preorder", testPrintPreOrder);
    // CU_add_test(suite, "Test Print Inorder", testPrintInOrder);
    // CU_add_test(suite, "Test Print Postorder", testPrintPostOrder);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}