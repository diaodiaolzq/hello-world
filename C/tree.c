#include "stdio.h"
#include "stdlib.h"

#define     LINK    (0)
#define     THREAD  (1)

// parent tree
typedef struct {
    char value;
    int parent;
}parentTreeNode;

typedef struct {
    parentTreeNode *nodes;
    // struct parentTree *next;
    int root, nodeNum;
}parentTree;

// children tree
typedef struct {
    int child;
    struct childPtr *next;
}childPtr;

typedef struct {
    char value;
    childPtr *firstChild;
}childTreeNode;

typedef struct {
    childTreeNode *nodes;
    int root;
    int number;
}childTree;

// first child and right side brother
typedef struct {
    char value;
    struct childBrotherTreeNode *firstChild;
    struct childBrotherTreeNode *rightSideBrother;
}childBrotherTreeNode;

// binary tree
// typedef struct {         // note: expected ‘binaryTree ** {aka struct <anonymous> **}’ but argument is of type ‘struct binaryTree **’
                            // void createBinaryTreePreOrder(binaryTree **tree
typedef struct binaryTree{
    char value;
    struct binaryTree *leftChild;
    struct binaryTree *rightChild;
}binaryTree;

// threaded binary tree
typedef struct binaryTreeThread {
    char value;
    struct binaryTreeThread *leftChild;
    struct binaryTreeThread *rightChild;
    int leftTag;
    int rightTag;
}binaryTreeThread;
binaryTreeThread *pre;

// pre-order traversal
void preOrderTraversal(binaryTree *tree) {
    if (tree == NULL) {return;}
    printf("%c", tree->value);
    preOrderTraversal(tree->leftChild);
    preOrderTraversal(tree->rightChild);
}

// in-order traversal
void inOrderTraversal(binaryTree *tree) {
    if (tree == NULL) {return;}
    inOrderTraversal(tree->leftChild);
    printf("%c", tree->value);
    inOrderTraversal(tree->rightChild);
}

// post-order traversal
void postOrderTraversal(binaryTree *tree) {
    if(tree == NULL) {return;}
    postOrderTraversal(tree->leftChild);
    postOrderTraversal(tree->rightChild);
    printf("%c", tree->value);
}

// create binary tree according to pre-order traversal
void createBinaryTreePreOrder(binaryTree **tree) {
    char nodeValue;
    scanf("%c", &nodeValue);
    if(nodeValue == '#') {
        *tree == NULL;
    }else {
        *tree = (binaryTree*)malloc(sizeof(binaryTree));
        if(!(*tree)) {
            printf("malloc error\n");
            exit(1);
        }
        (*tree)->value = nodeValue;
        createBinaryTreePreOrder(&(*tree)->leftChild);
        createBinaryTreePreOrder(&(*tree)->rightChild);
    }
}

// create threaded binary tree according to pre-order traversal
void createBinaryTreeThreadPreOrder(binaryTreeThread **tree) {
    char nodeValue;
    scanf("%c", &nodeValue);
    if(nodeValue == '#') {
        *tree == NULL;
    }else {
        *tree = (binaryTreeThread*)malloc(sizeof(binaryTreeThread));
        if(!(*tree)) {
            printf("malloc error\n");
            exit(1);
        }
        (*tree)->value = nodeValue;
        createBinaryTreeThreadPreOrder(&(*tree)->leftChild);
        createBinaryTreeThreadPreOrder(&(*tree)->rightChild);
    }
}

// threading binary tree according to in-order traversal
void inOrderThread(binaryTreeThread *tree) {
    if (tree == NULL) {return;}
    inOrderThread(tree->leftChild);
    if (!tree->leftChild) {
        tree->leftChild = pre;
        tree->leftTag = THREAD;
    }
    if (!pre->rightChild) {
        pre->rightChild = tree;
        pre->rightTag = THREAD;
    }
    pre = tree;
    inOrderThread(tree->rightChild);
}

void inOrderTraversalThread(binaryTreeThread *head) {
    binaryTreeThread *tree;
    tree = head->leftChild;
    while (tree != head) {
        while (tree->leftTag == LINK) {tree = tree->leftChild;}
        printf("%c", tree->value);
        while (tree->rightTag == THREAD && tree->rightChild != head) {
            tree = tree->rightChild;
            printf("%c", tree->value);
        }
        tree = tree->rightChild;
    }
}

int main() {
    // binaryTree *tree;
    // createBinaryTreePreOrder(&tree);
    // preOrderTraversal(tree);
    // printf("\n");
    // inOrderTraversal(tree);
    // printf("\n");
    // postOrderTraversal(tree);
    // printf("\n");

    // ABDH##I##EJ###CF##G## (pre-order extend binary tree)
    binaryTreeThread *tree;
    createBinaryTreeThreadPreOrder(&tree);  // tree points to root

    binaryTreeThread *head;
    head = (binaryTreeThread*)malloc(sizeof(binaryTreeThread));
    pre = head;
    inOrderThread(tree);
    pre->rightChild = head;
    pre->rightTag = THREAD;
    head->leftChild = tree;
    head->leftTag = LINK;

    inOrderTraversalThread(head);
    printf("\n");
    return EXIT_SUCCESS;
}