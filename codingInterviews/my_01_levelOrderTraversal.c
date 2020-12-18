#include "stdio.h"
#include "stdlib.h"
#define MAX_SIZE  20

typedef struct binaryTreeNode {
    char data;
    struct binaryTreeNode *lChild;
    struct binaryTreeNode *rChild;
}binaryTreeNode;

// circular queue
typedef struct cirQueue {
    binaryTreeNode **data;  // NOTE: 存放binaryTreeNode*的指针
    int head;
    int tail;
}cirQueue;

void cirQueueInit(cirQueue **Q) {
    if (Q == NULL) {return;}
    *Q = (cirQueue*)malloc(sizeof(cirQueue));
    (*Q)->data = (binaryTreeNode**)malloc(MAX_SIZE * sizeof(binaryTreeNode*));
    (*Q)->head = 0;
    (*Q)->tail = 0;
}

int cirQueueFull(cirQueue *Q, int *full) {
    if (Q == NULL) {return EXIT_FAILURE;}
    if (Q->head == (Q->tail + 1) % MAX_SIZE) {
        *full = 1;
    } else {
        *full = 0;
    }
    return EXIT_SUCCESS;
}

int cirQueueEmpty(cirQueue *Q, int *empty) {
    if (Q == NULL) {return EXIT_FAILURE;}
    if (Q->head == Q->tail) {
        *empty = 1;
    } else {
        *empty = 0;
    }
    return EXIT_SUCCESS;
}

int cirQueueIn(cirQueue *Q, binaryTreeNode *data) {
    if (Q == NULL) {return EXIT_FAILURE;}
    int full = -1;
    cirQueueFull(Q, &full);
    if (full == 1) {return EXIT_FAILURE;}
    Q->data[Q->tail] = data;
    Q->tail = (Q->tail + 1) % MAX_SIZE;
    return EXIT_SUCCESS;
}

int cirQueueOut(cirQueue *Q, binaryTreeNode **data) {   // NOTE: binaryTreeNode **data
    if (Q == NULL) {return EXIT_FAILURE;}
    int empty = -1;
    cirQueueEmpty(Q, &empty);
    if (empty == 1) {return EXIT_FAILURE;}
    *data = Q->data[Q->head];
    Q->head = (Q->head + 1) % MAX_SIZE;
    return EXIT_SUCCESS;
}

void cirQueueCleanup(cirQueue *Q) {
    if (Q == NULL) {return;}
    free(Q->data);
    free(Q);
}

// link queue

// binary tree

void createBinaryTreePreOrder(binaryTreeNode **tree) {
    char data;
    scanf("%c", &data);
    if (data != '#') {
        (*tree) = (binaryTreeNode*)malloc(sizeof(binaryTreeNode));
        if ((*tree) == NULL) {
            printf("malloc error, exit.");
            exit(1);
        }
        (*tree)->data = data;
        createBinaryTreePreOrder(&(*tree)->lChild);
        createBinaryTreePreOrder(&(*tree)->rChild);
    }
}

void preOrderTraversal(binaryTreeNode *tree) {
    if (tree == NULL) {return;}
    printf("%c", tree->data);
    preOrderTraversal(tree->lChild);
    preOrderTraversal(tree->rChild);
}

void inOrderTraversal(binaryTreeNode *tree) {
    if (tree == NULL) {return;}
    inOrderTraversal(tree->lChild);
    printf("%c", tree->data);
    inOrderTraversal(tree->rChild);
}

void postOrderTraversal(binaryTreeNode *tree) {
    if (tree == NULL) {return;}
    postOrderTraversal(tree->lChild);
    postOrderTraversal(tree->rChild);
    printf("%c", tree->data);
}

void levelOrderTraversal(binaryTreeNode *tree) {
    if (tree == NULL) {return;}
    cirQueue *queue;
    cirQueueInit(&queue);
    cirQueueIn(queue, tree);
    binaryTreeNode *data;
    int empty = -1;
    cirQueueEmpty(queue, &empty);
    while (!empty) {
        cirQueueOut(queue, &data);
        printf("%c", data->data);
        if (data->lChild != NULL) {
            cirQueueIn(queue, data->lChild);
        }
        if (data->rChild != NULL) {
            cirQueueIn(queue, data->rChild);
        }
        cirQueueEmpty(queue, &empty);
    }

}

void test(char *testCase, char *input) {
    binaryTreeNode *tree;
    printf("%s begins: input: %s\n", testCase, input);
    createBinaryTreePreOrder(&tree);
    printf("result: ");
    levelOrderTraversal(tree);
    printf("\n");
}

void test_1() {
    char input[] = "ABC###DE##F##";
    test("test case 1", input);
    printf("expect: ABDCEF\n");
}

int main() {
    test_1();
    return EXIT_SUCCESS;
}