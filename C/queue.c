#include "stdio.h"
#include "stdlib.h"
#define ENABLE_LINK_LIST

#define MAX_SIZE    20

#ifdef ENABLE_LINK_LIST
typedef struct queueNode {
    int value;
    struct queueNode *next;
}queueNode;
typedef struct {
    struct queueNode *head;
    int len;
}linkQueue;
void* initQueue() {
    linkQueue *Q;
    Q = (linkQueue*)malloc(sizeof(linkQueue));
    Q->head = NULL;
    Q->len = 0;
    return Q;
}
int queueLength(linkQueue *Q, int *len) {
    if(Q == NULL) {return 0;}
    *len = Q->len;
    return 1;
}
int enQueue(linkQueue *Q, int value) {
    if(Q == NULL) {return 0;}
    queueNode *node;
    node = (queueNode*)malloc(sizeof(queueNode));
    node->value = value;
    node->next = Q->head;
    Q->head = node;
    Q->len++;
    return 1;
}
int deQueue(linkQueue *Q, int *value) {
    if(Q == NULL || Q->head == NULL) {return 0;}
    queueNode *node;
    node = Q->head;
    Q->head = Q->head->next;
    Q->len--;
    *value = node->value;
    free(node);
    return 1;
}
int clearQueue(linkQueue *Q) {
    if(Q == NULL) {return 0;}
    int temp, temp1;
    temp = 1;
    while (temp == 1 && Q->len != 0) {
        temp = deQueue(Q, &temp1);
    }
    return 1;
}
int queueEmpty(linkQueue *Q, int *emptyFlag) {
    if(Q == NULL) {return 0;}
    if (Q->head == NULL) {
        *emptyFlag = 1;
    } else {
        *emptyFlag = 0;
    }
    return 1;
}
int getQueueHead(linkQueue *Q, int *headValue) {
    if(Q == NULL) {return 0;}
    int emptyFlag;
    queueEmpty(Q, &emptyFlag);
    if(emptyFlag == 1) {return 0;}
    *headValue = Q->head->value;
    return 1;
}
int destoryQueue(linkQueue *Q) {
    if(Q == NULL) {return 0;}
    clearQueue(Q);
    free(Q);
    return 1;
}
#else
typedef struct {
    int data[MAX_SIZE];
    int head;
    int tail;
}sqQueue;
void* initQueue() {
    sqQueue *Q = (sqQueue*)malloc(sizeof(sqQueue));
    Q->head = 0;
    Q->tail = 0;
    return Q;
}
int queueLength(sqQueue *Q, int *len) {
    if (Q == NULL) {return 0;}
    *len = (Q->tail - Q->head + MAX_SIZE) % MAX_SIZE;
    return 1;
}
int enQueue(sqQueue *Q, int valu) {
    if (Q == NULL || (Q->tail + 1) % MAX_SIZE == Q->head) {return 0;}
    Q->data[Q->tail] = valu;
    Q->tail = (Q->tail + 1) % MAX_SIZE;
    return 1;
}
int deQueue(sqQueue *Q, int *valu) {
    if(Q == NULL || Q->head == Q->tail) {return 0;}
    *valu = Q->data[Q->head];
    Q->head = (Q->head + 1) % MAX_SIZE;
    return 1;
}
int clearQueue(sqQueue *Q) {
    if(Q == NULL) {return 0;}
    Q->head = 0;
    Q->tail = 0;
    return 1;
}
int queueEmpty(sqQueue *Q, int *emptyFlag) {
    if(Q == NULL) {return 0;}
    if (Q->head == 0 && Q->tail == 0) {
        *emptyFlag = 1;
    } else {
        *emptyFlag = 0;
    }
    return 1;
}
int getQueueHead(sqQueue *Q, int *headValue) {
    if(Q == NULL) {return 0;}
    int emptyFlag;
    queueEmpty(Q, &emptyFlag);
    if(emptyFlag == 1) {return 0;}
    *headValue = Q->data[Q->head];
    return 1;
}
int destoryQueue(sqQueue *Q) {
    if(Q == NULL) {return 0;}
    free(Q);
    return 1;
}
#endif

int main() {
    int empty, len, headValue, deValue;

#ifdef ENABLE_LINK_LIST
    linkQueue *queue;
    queue = (linkQueue*)initQueue();
#else
    sqQueue *queue;
    queue = (sqQueue*)initQueue();
#endif
    for(int i = 0; i < 5; i++) {
        enQueue(queue, i);
    }
    queueEmpty(queue, &empty);
    queueLength(queue, &len);
    getQueueHead(queue, &headValue);
    deQueue(queue, &deValue);
    queueLength(queue, &len);
    destoryQueue(queue);

    printf("done\n");
    return 1;
}