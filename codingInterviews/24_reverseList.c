#include "stdio.h"
#include "stdlib.h"

typedef struct linkListNode {
    char data;
    struct linkListNode *next;
}linkListNode;

int creatLinkList(char *dataArray, linkListNode *pHead) {
    if (dataArray == NULL || pHead == NULL) {return EXIT_FAILURE;}
    linkListNode *node;
    linkListNode *tail;
    tail = pHead;
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

//　以下为易犯错误示例
// void reverseList(linkListNode **pHead) {
//     if ((*pHead)->next == NULL) {return;}
//     linkListNode *p1, *p2;
//     p1 = (*pHead)->next;
//     p2 = (*pHead)->next;
//     (*pHead)->next = NULL;
//     while (p2 != NULL) {
//         p2 = p2->next;
//         p1->next = (*pHead);
//         (*pHead) = p1;
//         p1 = p2;
//     }
//     return;
// }

void reverseList(linkListNode *head) {
    if (head == NULL || head->next == NULL) {return;}
    linkListNode *p, *p1, *p2;
    p = head->next;
    p1 = p->next;
    p2 = p->next;
    p->next = NULL;
    while (p2 != NULL) {
        p2 = p2->next;
        p1->next = p;
        p = p1;
        p1 = p2;
    }
    (head)->next = p;
    return;
}

void test(char *testCase, char *data, char *expect) {
    if (testCase == NULL) {return;}
    printf("%s begins: ", testCase);
    linkListNode *head;
    head = (linkListNode*)malloc(sizeof(linkListNode));
    creatLinkList(data, head);
    reverseList(head);
    linkListNode *p;
    p = head->next;
    while (p != NULL) {
        if (p->data != *expect) {
            printf("failed");
            return;
        }
        p = p->next;
        expect++;
    }
    if (data == NULL && expect == NULL) {
        printf("pass.\n");
        return;
    }
    if (*expect == '\0') {
        printf("pass.\n");
    } else {
        printf("failed.\n");
    }
}

void test_1() {
    char data[] = "AB";
    char expect[] = "BA";
    test("test case 1", data, expect);
}

void test_2() {
    char data[] = "ABBC";
    char expect[] = "CBBA";
    test("test case 2", data, expect);
}

void test_3() {
    char data[] = "A";
    char expect[] = "A";
    test("test case 3", data, expect);
}

void test_4() {
    char *data = NULL;
    char *expect = NULL;
    test("test case 4", data, expect);
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    return EXIT_SUCCESS;
}