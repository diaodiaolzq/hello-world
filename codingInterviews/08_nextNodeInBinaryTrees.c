#include "stdio.h"
#include "stdlib.h"
#define MAX_SIZE  20

// #define ENABLE_RECURSION    // recursion based method is more complex

typedef struct binaryTreeNode {
    char data;
    struct binaryTreeNode *pParent;
    struct binaryTreeNode *pLeftChild;
    struct binaryTreeNode *pRightChild;
}binaryTreeNode;

binaryTreeNode* createBinaryTreeNode(int data) {
    binaryTreeNode *node;
    node = (binaryTreeNode*)malloc(sizeof(binaryTreeNode));
    node->data = data;
    node->pParent = NULL;
    node->pLeftChild = NULL;
    node->pRightChild = NULL;
    return node;
}

void connectTreeNodes(binaryTreeNode *pParent, binaryTreeNode *pLeftChild, binaryTreeNode *pRightChild) {
    if (pParent) {
        pParent->pLeftChild = pLeftChild;
        pParent->pRightChild = pRightChild;
        if (pLeftChild) {pLeftChild->pParent = pParent;}
        if (pRightChild) {pRightChild->pParent = pParent;}
    }
}

void printTreeNode(binaryTreeNode* pNode) {
    if(pNode) {
        printf("data of this node is: %d\n", pNode->data);
        if(pNode->pLeftChild)
            printf("data of its left child is: %d.\n", pNode->pLeftChild->data);
        else
            printf("left child is null.\n");
        if(pNode->pRightChild)
            printf("data of its right child is: %d.\n", pNode->pRightChild->data);
        else
            printf("right child is null.\n");
    } else {
        printf("node is null.\n");
    }
    printf("\n");
}

void preOrderTraversal(binaryTreeNode *node) {
    if (!node) {return;}
    printf("%d", node->data);
    preOrderTraversal(node->pLeftChild);
    preOrderTraversal(node->pRightChild);
}

void destroyTree(binaryTreeNode *node) {
    if (!node) {return;}
    destroyTree(node->pLeftChild);
    destroyTree(node->pRightChild);
    free(node);
}

#ifdef ENABLE_RECURSION
void getNextInOrderChild(binaryTreeNode *pNode, binaryTreeNode **pNext) {
    if (pNode->pLeftChild) {
        getNextInOrderChild(pNode->pLeftChild, pNext);
    } else {
        *pNext = pNode;
    }
}

void getNextInorderParent(binaryTreeNode *pNodeChild, binaryTreeNode *pNode, binaryTreeNode **pNext) {
    if (!pNode) {           // NOTE:　pNodeChild为根节点(test 7)
        *pNext = NULL;
        return;
    }
    if (pNode->pLeftChild == pNodeChild) {
        *pNext = pNode;
    } else if (pNode->pRightChild == pNodeChild) {
        getNextInorderParent(pNode, pNode->pParent, pNext);
    } else {
        printf("invalid input, exit.");
        exit(1);
    }
}

void getNextInOrder(binaryTreeNode *pNode, binaryTreeNode **pNext) {
    if (!pNode) {return;}
    if (pNode->pRightChild) {
        getNextInOrderChild(pNode->pRightChild, pNext);
    } else {
        if (pNode->pParent) {
            getNextInorderParent(pNode, pNode->pParent, pNext);
        } else {
            *pNext = NULL;      // NOTE: 无左孩子和父母(test 8)
        }
    }
}
#else
void getNextInOrder(binaryTreeNode *pNode, binaryTreeNode **pNext) {
    if (!pNode) {return;}
    if (pNode->pRightChild) {
        pNode = pNode->pRightChild;
        while (pNode->pLeftChild) {
            pNode = pNode->pLeftChild;
        }
        *pNext = pNode;
    } else {
        if (pNode->pParent) {
            binaryTreeNode *pNodeParent = pNode->pParent;
            while (pNodeParent) {
                if (pNodeParent->pLeftChild == pNode) {
                    *pNext = pNodeParent;
                    return;
                } else if (pNodeParent->pRightChild == pNode) {
                    pNode = pNodeParent;
                    pNodeParent = pNode->pParent;
                } else {
                    printf("invalid input, exit.\n");
                    exit(1);
                }
                *pNext = NULL;
            }
        } else {
            *pNext = NULL;      // NOTE: 无左孩子和父母(test 8)
        }
    }
}
#endif


void test(char* testName, binaryTreeNode* pNode, binaryTreeNode* expected)
{
    if(testName != NULL)
        printf("%s begins: ", testName);

    binaryTreeNode* pNext;
    getNextInOrder(pNode, &pNext);

    if(pNext == expected)
        printf("passed.\n");
    else
        printf("failed.\n");
}

//            8
//        6      10
//       5 7    9  11
void test1_7()
{
    binaryTreeNode* pNode8 = createBinaryTreeNode(8);
    binaryTreeNode* pNode6 = createBinaryTreeNode(6);
    binaryTreeNode* pNode10 = createBinaryTreeNode(10);
    binaryTreeNode* pNode5 = createBinaryTreeNode(5);
    binaryTreeNode* pNode7 = createBinaryTreeNode(7);
    binaryTreeNode* pNode9 = createBinaryTreeNode(9);
    binaryTreeNode* pNode11 = createBinaryTreeNode(11);

    connectTreeNodes(pNode8, pNode6, pNode10);
    connectTreeNodes(pNode6, pNode5, pNode7);
    connectTreeNodes(pNode10, pNode9, pNode11);

    test("Test1", pNode8, pNode9);
    test("Test2", pNode6, pNode7);
    test("Test3", pNode10, pNode11);
    test("Test4", pNode5, pNode6);
    test("Test5", pNode7, pNode8);
    test("Test6", pNode9, pNode10);
    test("Test7", pNode11, NULL);

    destroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void test8_11()
{
    binaryTreeNode* pNode5 = createBinaryTreeNode(5);
    binaryTreeNode* pNode4 = createBinaryTreeNode(4);
    binaryTreeNode* pNode3 = createBinaryTreeNode(3);
    binaryTreeNode* pNode2 = createBinaryTreeNode(2);

    connectTreeNodes(pNode5, pNode4, NULL);
    connectTreeNodes(pNode4, pNode3, NULL);
    connectTreeNodes(pNode3, pNode2, NULL);

    test("Test8", pNode5, NULL);
    test("Test9", pNode4, pNode5);
    test("Test10", pNode3, pNode4);
    test("Test11", pNode2, pNode3);

    destroyTree(pNode5);
}

//        2
//         3
//          4
//           5
void test12_15()
{
    binaryTreeNode* pNode2 = createBinaryTreeNode(2);
    binaryTreeNode* pNode3 = createBinaryTreeNode(3);
    binaryTreeNode* pNode4 = createBinaryTreeNode(4);
    binaryTreeNode* pNode5 = createBinaryTreeNode(5);

    connectTreeNodes(pNode2, NULL, pNode3);
    connectTreeNodes(pNode3, NULL, pNode4);
    connectTreeNodes(pNode4, NULL, pNode5);

    test("Test12", pNode5, NULL);
    test("Test13", pNode4, pNode5);
    test("Test14", pNode3, pNode4);
    test("Test15", pNode2, pNode3);

    destroyTree(pNode2);
}

void test16()
{
    binaryTreeNode* pNode5 = createBinaryTreeNode(5);

    test("Test16", pNode5, NULL);

    destroyTree(pNode5);
}

int main(int argc, char *argv[]) {
    test1_7();
    test8_11();
    test12_15();
    test16();
    return EXIT_SUCCESS;
}