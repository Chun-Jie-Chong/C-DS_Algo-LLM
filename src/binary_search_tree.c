/* Sure! Here is a complete implementation of a Binary Search Tree (BST) in C, with the functions `insert`, `delete`, `find`, and `inOrder`. I've included the necessary headers and provided comments to help you understand what each part of the code does. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert function for BST
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    // Do nothing if data is already present (no duplicates)
    return node;
}

// Find the minimum value node in a subtree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Delete function for BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Find function for BST
struct Node* find(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return find(root->left, data);
    }
    return find(root->right, data);
}

// InOrder traversal of BST
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Main function to test the BST implementation
// int main() {
//     struct Node* root = NULL;
//     root = insert(root, 50);
//     root = insert(root, 30);
//     root = insert(root, 20);
//     root = insert(root, 40);
//     root = insert(root, 70);
//     root = insert(root, 60);
//     root = insert(root, 80);

//     printf("InOrder traversal of the given tree: ");
//     inOrder(root);
//     printf("\n");

//     printf("Delete 20\n");
//     root = deleteNode(root, 20);
//     printf("InOrder traversal of the modified tree: ");
//     inOrder(root);
//     printf("\n");

//     printf("Delete 30\n");
//     root = deleteNode(root, 30);
//     printf("InOrder traversal of the modified tree: ");
//     inOrder(root);
//     printf("\n");

//     printf("Delete 50\n");
//     root = deleteNode(root, 50);
//     printf("InOrder traversal of the modified tree: ");
//     inOrder(root);
//     printf("\n");

//     struct Node* findNode = find(root, 40);
//     if (findNode != NULL) {
//         printf("Found node with data 40\n");
//     } else {
//         printf("Node with data 40 not found\n");
//     }

//     return 0;
// }
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    struct Node* root = NULL;
    char command[10];
    int data;

    while (fscanf(file, "%s %d", command, &data) == 2) {
        if (strcmp(command, "insert") == 0) {
            root = insert(root, data);
            printf("Inserted: %d\n", data);
        } else if (strcmp(command, "delete") == 0) {
            root = deleteNode(root, data);
            printf("Deleted: %d\n", data);
        } else if (strcmp(command, "find") == 0) {
            struct Node* foundNode = find(root, data);
            if (foundNode != NULL) {
                printf("Found: %d\n", foundNode->data);
            } else {
                printf("Not Found: %d\n", data);
            }
        }
    }

    fclose(file);

    // Clean up and free allocated memory if needed

    return 0;
}
/* ``` */
/*  */
/* Explanation: */
/* 1. The `Node` structure represents each node in the BST, storing data and pointers to the left and right children. */
/* 2. The `createNode` function creates a new BST node with the given data. */
/* 3. The `insert` function inserts a new node into the BST, maintaining the binary search property. */
/* 4. The `minValueNode` function finds the node with the minimum value in a subtree, used during deletion. */
/* 5. The `deleteNode` function deletes a node from the BST and maintains the BST structure. */
/* 6. The `find` function searches for a node with the given data in the BST. */
/* 7. The `inOrder` function performs an in-order traversal of the BST, printing nodes in ascending order. */
/*  */
/* In `main`, the BST is created, and the insert, find, delete, and in-order traversal functions are demonstrated. This should give you a good starting point for using and understanding binary search trees in C. */
