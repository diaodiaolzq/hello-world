#include "stdio.h"
#include "stdlib.h"


typedef struct node
{
    int val;
    struct node* next;
} node;
typedef struct node linkList;

void creatListHeadHeadIncertion(linkList **L, int n) {

    *L = (linkList*)malloc(sizeof(node));
    (*L)->next = NULL;

    linkList* p;
    for (int i = 0; i < n; i++) {
        p = (linkList*)malloc(sizeof(node));
        p->val = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;
    }

    (*L)->val = n;
}

void creatListHeadTailIncertion(linkList** L, int n) {

    *L = (linkList*)malloc(sizeof(node));
    (*L)->next = NULL;

    // linkList* p = (linkList*)malloc(sizeof(node));
    // p->val = rand() % 100 + 1;
    // p->next = NULL;
    // (*L)->next = p;

    // for (int i = 1; i < n; i++) {
    //     p->next = (linkList*)malloc(sizeof(node));
    //     p->next->val = rand() % 100 + 1;
    //     p->next->next = NULL;
    //     p = p->next;
    // }

    linkList *p, *r;
    r = *L;
    for (int i = 0; i < n; i++) {
        p = (linkList*)malloc(sizeof(node));
        p->val = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;

    (*L)->val = n;
}


int linkListInsertion(linkList *L, int k, int val) {
    linkList *p, *r;
    p = (linkList*)malloc(sizeof(node));
    p->val = val;
    r = L;
    for(int i = 0; i < k; i++) {
        if (r->next != NULL) {
            r = r->next;
        }else {
            return 0;
        }
    }

    p->next = r->next;
    r->next = p;

    return 1;
}

int linkListDelet(linkList *L, int k) {
    linkList *p ,*r;
    r = L;
    for(int i = 0; i < k - 1; i++) {
        if (r->next != NULL) {
            r = r->next;
        }else {
            return 0;
        }
    }

    p = r->next;
    r->next = p->next;

    free(p);
}

void printLinkListElement(linkList* L) {
    linkList* p;
    p = L->next;
    while (p != NULL) {
        printf("%d, ", p->val);
        p = p->next;
    }
    printf("\n");
}

int readLinkListElement(linkList *L, int k, int *val) {
    int j;
    linkList *p;
    p = L->next;
    j = 1;
    while(p != NULL && j < k) {
        p = p->next;
        j++;
    }
    if (p == NULL || j > k) {
        return 0;
    } else {
        *val = p->val;
        return 1;
    }
}

int linkListCreatRing(linkList *L, int k) {
    linkList *p;
    int j;
    p = L->next;
    j = 1;
    while(p != NULL && j < k) {
        p = p->next;
        j++;
    }
    if (p == NULL || j > k) {
        return 0;
    }
    linkList *r = p;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = r;
    return 1;
}

int linkListRingExist(linkList *L) {
    linkList *fast, *slow;
    int j, k;
    fast = L->next;
    fast = fast->next;
    slow = L->next;
    j = 1;
    while(fast != slow) {
        fast = fast->next;
        if (fast != NULL){
            fast = fast->next;
        } else {
            break;
        }
        slow = slow->next;
        j++;
    }
    if (fast == NULL || slow == NULL){
        return 0;
    }

    return 1;
}

void main() {

    int success = 0;

    linkList *head = NULL;
    creatListHeadHeadIncertion(&head, 10);
    printLinkListElement(head);

    // creatListHeadTailIncertion(&head, 5);
    // printLinkListElement(head);

    // linkListInsertion(head, 5, 666);
    // printLinkListElement(head);

    // linkListDelet(head, 6);
    // printLinkListElement(head);

    // int elementVal;
    // success = readLinkListElement(head, 5, &elementVal);
    // printf("success = %d, %d\n", success, elementVal);

    success = linkListCreatRing(head, 4);
    printf("success = %d\n", success);
    // printLinkListElement(head);

    success = linkListRingExist(head);
    printf("success = %d\n", success);

    return;
}
