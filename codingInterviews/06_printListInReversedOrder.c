#include "stdio.h"
#include "stdlib.h"

typedef struct linkListNode {
    char data;
    struct linkListNode *next;
}linkListNode;

int creatLinkList(char *dataArray, linkListNode *head) {
    if (dataArray == NULL || head == NULL) {return EXIT_FAILURE;}
    linkListNode *node;
    linkListNode *tail;
    tail = head;
    while (*dataArray != '\0') {
        node = (linkListNode*)malloc(sizeof(linkListNode));
        node->data = *dataArray;
        dataArray++;

        tail->next = node;
        tail = node;
    }
    return EXIT_SUCCESS;
}

int linkListPrint(linkListNode *head) {
    if (head == NULL) {return EXIT_FAILURE;}
    linkListNode *p;
    p = head->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    return EXIT_SUCCESS;
}

void linkListPrintInverse(linkListNode *node) {
    if (node->next != NULL) {
        linkListPrintInverse(node->next);
    }
    printf("%c ", node->data);
}

void linkListPrintInverseWraped(linkListNode *head) {
    if(head == NULL || head -> next == NULL) {return;}
    linkListNode *node = head->next;
    linkListPrintInverse(node);
}

void test(char *testCase, char *data) {
    if (testCase == NULL) {return;}
    printf("%s begins:\n", testCase);
    linkListNode *head;
    head = (linkListNode*)malloc(sizeof(linkListNode));
    creatLinkList(data, head);
    linkListPrint(head);
    printf("\n");
    linkListPrintInverseWraped(head);
    printf("\n");
}

void test_1() {
    char data[] = "ABBC";
    test("test case 1", data);
}

void test_2() {
    char data[] = "BB";
    test("test case 2", data);
}

void test_3() {
    char data[] = "B";
    test("test case 3", data);
}

void test_4() {
    char *data = NULL;
    test("test case 4", data);
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    return EXIT_SUCCESS;
}