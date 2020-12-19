#include "stdio.h"
#include "stdlib.h"
#define QUEUE_SIZE 3

typedef struct queue {
    char *data;
    int tail;
}queue;

queue* queueInit(int queueSize) {
    queue *q;
    q = (queue*)malloc(sizeof(queue));
    q->data = (char*)malloc(sizeof(char));
    q->tail = 0;
}

int queueFull(queue *q) {
    if (q == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (q->tail >= QUEUE_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

int queueEmpty(queue *q) {
    if (q == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (q->tail <= 0) {
        return 1;
    } else {
        return 0;
    }
}

void queueIn(queue *q, char data) {
    if (q == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (!queueFull(q)) {
        q->data[q->tail] = data;
        q->tail++;
    } else {
        printf("queue is full.\n");
    }
}

void queueOut(queue *q, char *data) {
    if (q == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (!queueEmpty(q)) {
        *data = q->data[0];
        for (int i = 1; i < q->tail; i++) {
            q->data[i - 1] = q->data[i];
        }
        q->tail--;
    } else {
        printf("queue is empty.\n");
    }
}

typedef struct stack {
    struct queue *q1;
    struct queue *q2;
    int nonEmptyQNum;
}stack;

stack* stackInit(int stackSize) {
    stack *s;
    s = (stack*)malloc(sizeof(stack));
    s->q1 = queueInit(stackSize);
    s->q2 = queueInit(stackSize);
    s->nonEmptyQNum = 1;
    return s;
}

int stackFull(stack *s) {
    if (s == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (s->nonEmptyQNum == 1) {
        return queueFull(s->q1);
    } else if (s->nonEmptyQNum == 2) {
        return queueFull(s->q2);
    } else {
        printf("invalid nonEmptyQNum, exit.\n");
        exit(1);
    }
}


int stackEmpty(stack *s) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (s->nonEmptyQNum == 1) {
        return queueEmpty(s->q1);
    } else if (s->nonEmptyQNum == 2) {
        return queueEmpty(s->q2);
    } else {
        printf("invalid nonEmptyQNum, exit.\n");
        exit(1);
    }
}

void stackPush(stack *s, char data) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (!stackFull(s)) {
        if (s->nonEmptyQNum == 1) {
            queueIn(s->q1, data);
        } else if (s->nonEmptyQNum == 2) {
            queueIn(s->q2, data);
        } else {
            printf("invalid nonEmptyQNum, exit.\n");
            exit(1);
        }
    }
}

void stackPop(stack *s, char *data) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (s->nonEmptyQNum != 1 && s->nonEmptyQNum != 2) {
        printf("invalid nonEmptyQNum, exit.\n");
        exit(1);
    }
    if (!stackEmpty(s)) {
        queue *q, *nonq;
        if (s->nonEmptyQNum == 1) {
            nonq = s->q1;
            q = s->q2;
        } else {
            nonq = s->q2;
            q = s->q1;
        }
        int mvNum = nonq->tail - 1;
        char mvData;
        for (int i = 0; i < mvNum; i++) {
            queueOut(nonq, &mvData);
            queueIn(q, mvData);
        }
        queueOut(nonq, data);
        if (s->nonEmptyQNum == 1) {
            s->nonEmptyQNum++;
        } else {
            s->nonEmptyQNum--;
        }
    } else {
        printf("stack is empty, exit.\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    stack *s;
    s = stackInit(QUEUE_SIZE);
    stackPush(s, 'a');
    stackPush(s, 'b');
    stackPush(s, 'c');
    char data;
    stackPop(s, &data);
    printf("%c, ", data);
    stackPop(s, &data);
    printf("%c, ", data);
    stackPush(s, 'd');
    stackPop(s, &data);
    printf("%c, ", data);
    stackPop(s, &data);
    printf("%c, ", data);

    stackPop(s, &data);
    printf("%c, ", data);
    return EXIT_SUCCESS;
}