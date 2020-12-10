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
    if(Q == NULL) {return EXIT_FAILURE;}
    *len = Q->len;
    return EXIT_SUCCESS;
}
int enQueue(linkQueue *Q, int value) {
    if(Q == NULL) {return EXIT_FAILURE;}
    queueNode *node;
    node = (queueNode*)malloc(sizeof(queueNode));
    node->value = value;
    node->next = Q->head;
    Q->head = node;
    Q->len++;
    return EXIT_SUCCESS;
}
int deQueue(linkQueue *Q, int *value) {
    if(Q == NULL || Q->head == NULL) {return EXIT_FAILURE;}
    queueNode *node;
    node = Q->head;
    Q->head = Q->head->next;
    Q->len--;
    *value = node->value;
    free(node);
    return EXIT_SUCCESS;
}
int clearQueue(linkQueue *Q) {
    if(Q == NULL) {return EXIT_FAILURE;}
    int temp, temp1;
    temp = EXIT_SUCCESS;
    while (temp == EXIT_SUCCESS && Q->len != 0) {
        temp = deQueue(Q, &temp1);
    }
    return EXIT_SUCCESS;
}
int queueEmpty(linkQueue *Q, int *emptyFlag) {
    if(Q == NULL) {return EXIT_FAILURE;}
    if (Q->head == NULL) {
        *emptyFlag = 1;
    } else {
        *emptyFlag = 0;
    }
    return EXIT_SUCCESS;
}
int getQueueHead(linkQueue *Q, int *headValue) {
    if(Q == NULL) {return EXIT_FAILURE;}
    int emptyFlag;
    queueEmpty(Q, &emptyFlag);
    if(emptyFlag == 1) {return EXIT_FAILURE;}
    *headValue = Q->head->value;
    return EXIT_SUCCESS;
}
int destoryQueue(linkQueue *Q) {
    if(Q == NULL) {return EXIT_FAILURE;}
    clearQueue(Q);
    free(Q);
    return EXIT_SUCCESS;
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
    if (Q == NULL) {return EXIT_FAILURE;}
    *len = (Q->tail - Q->head + MAX_SIZE) % MAX_SIZE;
    return EXIT_SUCCESS;
}
int enQueue(sqQueue *Q, int valu) {
    if (Q == NULL || (Q->tail + 1) % MAX_SIZE == Q->head) {return EXIT_FAILURE;}
    Q->data[Q->tail] = valu;
    Q->tail = (Q->tail + 1) % MAX_SIZE;
    return EXIT_SUCCESS;
}
int deQueue(sqQueue *Q, int *valu) {
    if(Q == NULL || Q->head == Q->tail) {return EXIT_FAILURE;}
    *valu = Q->data[Q->head];
    Q->head = (Q->head + 1) % MAX_SIZE;
    return EXIT_SUCCESS;
}
int clearQueue(sqQueue *Q) {
    if(Q == NULL) {return EXIT_FAILURE;}
    Q->head = 0;
    Q->tail = 0;
    return EXIT_SUCCESS;
}
int queueEmpty(sqQueue *Q, int *emptyFlag) {
    if(Q == NULL) {return EXIT_FAILURE;}
    if (Q->head == 0 && Q->tail == 0) {
        *emptyFlag = 1;
    } else {
        *emptyFlag = 0;
    }
    return EXIT_SUCCESS;
}
int getQueueHead(sqQueue *Q, int *headValue) {
    if(Q == NULL) {return EXIT_FAILURE;}
    int emptyFlag;
    queueEmpty(Q, &emptyFlag);
    if(emptyFlag == 1) {return EXIT_FAILURE;}
    *headValue = Q->data[Q->head];
    return EXIT_SUCCESS;
}
int destoryQueue(sqQueue *Q) {
    if(Q == NULL) {return EXIT_FAILURE;}
    free(Q);
    return EXIT_SUCCESS;
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
    return EXIT_SUCCESS;
}