/* Implementing a Red-Black Tree (RBT) in C is a non-trivial task due to its complexity. Below is a complete implementation featuring node insertion, deletion, and inorder tree traversal (printing). We'll include necessary headers and struct definitions along with the required functions: */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

// Enum for node colors
typedef enum { RED, BLACK } Color;

// Red-Black Tree Node
typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

// Function prototypes
Node* createNode(int data);
void leftRotate(Node **root, Node *x);
void rightRotate(Node **root, Node *y);
void fixInsert(Node **root, Node *z);
void insertNode(Node **root, int data);
void fixDelete(Node **root, Node *x);
void transplant(Node **root, Node *u, Node *v);
Node* minimum(Node *node);
void deleteNode(Node **root, int data);
void inorderHelper(Node *root);
void printInorder(Node *root);

// Create a new Red-Black Tree node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Left rotate sub-tree rooted with x
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotate sub-tree rooted with y
void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix violations caused by insert
void fixInsert(Node **root, Node *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert a node in the Red-Black Tree
void insertNode(Node **root, int data) {
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = *root;
    
    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    
    fixInsert(root, z);
}

// Transplant subtree u with subtree v
void transplant(Node **root, Node *u, Node *v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

// Find node with minimum value
Node* minimum(Node *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Fix violations caused by deletion
void fixDelete(Node **root, Node *x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) && 
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node *w = x->parent->left;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->left == NULL || w->left->color == BLACK) && 
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

// Delete a node from the Red-Black Tree
void deleteNode(Node **root, int data) {
    Node *z = *root;
    Node *x, *y;
    while (z != NULL && z->data != data) {
        if (z->data < data)
            z = z->right;
        else
            z = z->left;
    }
    if (z == NULL)
        return;
    y = z;
    Color yOriginalColor = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yOriginalColor == BLACK)
        fixDelete(root, x);
}

// Recursive inorder helper function
void inorderHelper(Node *root) {
    if (root != NULL) {
        inorderHelper(root->left);
        printf("%d ", root->data);
        inorderHelper(root->right);
    }
}

// Print inorder traversal of the Red-Black Tree
void printInorder(Node *root) {
    inorderHelper(root);
    printf("\n");
}

// Main function for testing purposes
int main() {
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);
    
    printf("Inorder Traversal: ");
    printInorder(root);
    
    deleteNode(&root, 20);
    printf("Inorder Traversal after deletion: ");
    printInorder(root);
    
    return 0;
}
/* ``` */
/*  */
/* This code includes the entire Red-Black Tree implementation with functions for insertion, deletion, and inorder traversal. The `main` function demonstrates how to use these functions. Note that the tree balancing is automatically managed by the `fixInsert` and `fixDelete` functions using rotations and color assignments. */
