/* Certainly! Below is a concise implementation of an AVL tree in C, including the necessary headers and the required functions: `insert`, `delete`, `findNode`, `printPreOrder`, `printInOrder`, and `printPostOrder`. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Function to get the height of a node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Helper function to create a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // New node is initially added at leaf
    return(node);
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a node into the AVL tree
Node* insert(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node
    int balance = getBalance(node);

    // If node becomes unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Find the node with the minimum value in a tree
Node* minValueNode(Node* node) {
    Node* current = node;

    // Find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Delete a node from the AVL tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find a node in the AVL tree
Node* findNode(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return findNode(root->right, key);

    return findNode(root->left, key);
}

// Print tree in Preorder
void printPreOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Print tree in Inorder
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->key);
        printInOrder(root->right);
    }
}

// Print tree in Postorder
void printPostOrder(Node* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->key);
    }
}

// Main function to test the AVL tree
// int main() {
//     Node* root = NULL;

//     root = insert(root, 10);
//     root = insert(root, 20);
//     root = insert(root, 30);
//     root = insert(root, 40);
//     root = insert(root, 50);
//     root = insert(root, 25);

//     printf("Preorder traversal of the constructed AVL tree is:\n");
//     printPreOrder(root);

//     printf("\nInorder traversal of the constructed AVL tree is:\n");
//     printInOrder(root);

//     printf("\nPostorder traversal of the constructed AVL tree is:\n");
//     printPostOrder(root);

//     root = deleteNode(root, 10);

//     printf("\nPreorder traversal after deletion of 10:\n");
//     printPreOrder(root);

//     return 0;
// }
// Main function to test the AVL tree
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Node* root = NULL;
    char command[10];
    int key;

    // Read commands from the file
    while (fscanf(file, "%s %d", command, &key) != EOF) {
        if (strcmp(command, "insert") == 0) {
            root = insert(root, key);
            printf("Inserted %d\n", key);
        } else if (strcmp(command, "delete") == 0) {
            root = deleteNode(root, key);
            printf("Deleted %d\n", key);
        } else if (strcmp(command, "search") == 0) {
            Node* result = findNode(root, key);
            if (result) {
                printf("Found %d\n", key);
            } else {
                printf("%d not found\n", key);
            }
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    fclose(file);

    printf("Preorder traversal of the constructed AVL tree is:\n");
    printPreOrder(root);

    printf("\nInorder traversal of the constructed AVL tree is:\n");
    printInOrder(root);

    printf("\nPostorder traversal of the constructed AVL tree is:\n");
    printPostOrder(root);

    return 0;
}
/* ``` */
/*  */
/* This code provides a basic implementation of an AVL tree with the required operations. The `main` function demonstrates how to use the `insert`, `delete`, and traversal functions. Adjust the `main` function as needed for different test cases or to fit specific requirements. */
