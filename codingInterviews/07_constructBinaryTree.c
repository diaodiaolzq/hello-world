#include "stdio.h"
#include "stdlib.h"


typedef struct binaryTreeNode {
    int data;
    struct binaryTreeNode *lChild;
    struct binaryTreeNode *rChild;
}binaryTreeNode;

binaryTreeNode* biTreeConstruct(int *preOrder, int *inOrder, int length) {
    if (length < 0) {                       // NOTE: case 7: length < 0 invalid input;
        printf("invalid input, exit.\n");
        exit(1);
    }
    if (length == 0) {return NULL;}
    binaryTreeNode *root;
    root = (binaryTreeNode*)malloc(sizeof(binaryTreeNode));
    root->data = preOrder[0];
    int lTreeSize = 0;
    for (int i = 0; i < length; i++) {
        if (inOrder[i] == root->data) {break;}
        lTreeSize++;
    }
    int rTreeSize = length - lTreeSize - 1;
    root->lChild = biTreeConstruct(preOrder + 1, inOrder, lTreeSize);
    root->rChild = biTreeConstruct(preOrder + lTreeSize + 1, inOrder + lTreeSize + 1, rTreeSize);
}

binaryTreeNode* biTreeConstructWraped(int *preOrder, int *inOrder, int length) {
    if (preOrder == NULL || inOrder == NULL || length <= 0) {return NULL;}

    return biTreeConstruct(preOrder, inOrder, length);
}

void validation(binaryTreeNode *tree, int *expect, int *index) {
    if (tree == NULL) {return;}
    printf("%d, %d\n", tree->data, *(expect + *index));
    if (tree->data != *(expect + *index)) {
        printf("failed.");
        exit(1);
    };
    *index = *index + 1;
    validation(tree->lChild, expect, index);
    validation(tree->rChild, expect, index);
}

void test(char *testCase, int* preOrder, int *inOrder, int length) {
    if (testCase == NULL || preOrder == NULL || inOrder == NULL || length <= 0) {return;}
    printf("%s begins: \n", testCase);
    binaryTreeNode *tree;
    tree = biTreeConstructWraped(preOrder, inOrder, length);
    int index = 0;
    validation(tree, preOrder, &index);
    if (length == index) {
        printf("%s passed.\n", testCase);
    }
}

void test_1() {
    int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inOrder[] = {4, 7, 2, 1, 5, 3, 8, 6};
    test("test case 1", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

void test_2() {
    int preOrder[] = {1, 2, 3, 4, 5};
    int inOrder[] = {5, 4, 3, 2, 1};
    test("test case 2", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

void test_3() {
    int preOrder[] = {1, 2, 3, 4, 5};
    int inOrder[] = {1, 2, 3, 4, 5};
    test("test case 3", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

void test_4() {
    int preOrder[] = {1};
    int inOrder[] = {1};
    test("test case 4", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

void test_5() {
    int preOrder[] = {1, 2, 4, 5, 3, 6, 7};
    int inOrder[] = {4, 2, 5, 1, 6, 3, 7};
    test("test case 5", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

void test_6() {
    int *preOrder = NULL;
    int *inOrder = NULL;
    test("test case 6", preOrder, inOrder, 0);
}

void test_7() {
    int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inOrder[] = {4, 6, 2, 1, 5, 3, 8, 6};
    test("test case 7", preOrder, inOrder, sizeof(preOrder) / sizeof(int));
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    return EXIT_SUCCESS;
}