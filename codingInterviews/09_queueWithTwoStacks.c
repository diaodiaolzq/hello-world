#include "stdio.h"
#include "stdlib.h"
#define STACK_SIZE 3
// queue
typedef struct stack {
    char *data;
    int top;
}stack;

stack* stackInit(int stackSize) {
    stack *s;
    s = (stack*)malloc(sizeof(stack));
    s->data = (char*)malloc(stackSize * sizeof(char));
    s->top = 0;
    return s;
}

int stackFull(stack *s) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (s->top >= STACK_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

int stackEmpty(stack *s) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (s->top <= 0) {
        return 1;
    } else {
        return 0;
    }
}

void stackPush(stack *s, char data) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (!stackFull(s)) {
        s->data[s->top] = data;
        s->top++;
    } else {
        printf("stack is full.\n");
    }
}

void stackPop(stack *s, char *data) {
    if (s == NULL) {
        printf("stack is null, exit.");
        exit(1);
    }
    if (!stackEmpty(s)) {
        s->top--;
        *data = s->data[s->top];
    } else {
        printf("stack is empty.\n");
    }
}

typedef struct queue {
    struct stack *s1;
    struct stack *s2;
}queue;

queue* queueInit(int queueSize) {
    queue *q;
    q = (queue*)malloc(sizeof(queue));
    q->s1 = stackInit(queueSize);
    q->s2 = stackInit(queueSize);
    return q;
}

int queueFul(queue *q) {
    if (q == NULL) {
        printf("queue is null, exit.");
        exit(1);
    }
    if (stackFull(q->s1)) {     // NOTE: if s1 is full, q is full as well
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
    if (stackEmpty(q->s1) && stackEmpty(q->s2)) {   // NOTE: both s1 and s2 are empty, q is empty.
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
    if (!queueFul(q)) {
        stackPush(q->s1, data);
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
        if (stackEmpty(q->s2)) {
            while (!stackEmpty(q->s1)) {
                char temp;
                stackPop(q->s1, &temp);
                if (!stackFull(q->s2)) {
                    stackPush(q->s2, temp);
                } else {
                    printf("s1 is not empty when s2 is full, exit\n");
                    exit(1);
                }
            }
        }
        stackPop(q->s2, data);
    } else {
        printf("queue is empty.\n");
    }
}


int main(int argc, char* argv[]) {

    queue *q;
    q = queueInit(STACK_SIZE);
    queueIn(q, 'a');
    queueIn(q, 'b');
    queueIn(q, 'c');
    char data;
    queueOut(q, &data);
    printf("%c, ", data);
    queueOut(q, &data);
    printf("%c, ", data);
    queueIn(q, 'd');
    queueOut(q, &data);
    printf("%c, ", data);
    queueOut(q, &data);
    printf("%c, ", data);

    queueOut(q, &data);
    printf("%c, ", data);
    return EXIT_SUCCESS;
}