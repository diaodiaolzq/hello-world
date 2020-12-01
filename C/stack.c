#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define MAX_SIZE    (20)
// #define ENABLE_SQSTACK

#ifdef ENABLE_SQSTACK
typedef struct {
    int *data;
    int top;
}sqStack;

void *initSqStack(int maxLen) {
    printf("sq stack init: %d\n", maxLen);

    sqStack *inst = (sqStack*)malloc(sizeof(sqStack));
    // (*stack).data = (int*)malloc(maxLen * sizeof(int));
    // (*stack).top = 0;
    inst->data = (int*)malloc(maxLen * sizeof(int));
    inst->top = 0;
    // printf("%s done\n", __FUNCTION__);
    return inst;
}

void deleteSqStack(sqStack *stack) {
    printf("sq stack delete\n");

    sqStack *inst = (sqStack*)stack;
    if(inst == NULL) {
        return;
    }
    if (inst->data != NULL) {
        free(inst->data);
    }

    free(inst);

    return;
}

void clearSqStack(sqStack *stack) {
    printf("sq stack clear");
    sqStack *inst = stack;
    inst->top = 0;
}

void sqStackEmpty(sqStack *stack, int *empty) {

    sqStack *inst = stack;
    if (inst->top == 0) {
        *empty = 1;
    } else {
        *empty = 0;
    }
}

int sqStackGetTop(sqStack *stack, int *topValu) {
    printf("get sq stack top value\n");

    sqStack *inst = stack;
    int empty = 2;
    sqStackEmpty(inst, &empty);
    if (empty == 1) {return 0;}

    *topValu = inst->data[inst->top - 1];
    inst->top = inst->top - 1;
    return 1;
}

int sqStackPush(sqStack *stack, int *pushValu) {
    printf("push a valu into sq stack\n");

    sqStack *inst = stack;

    int empty = 2;
    sqStackEmpty(inst, &empty);
    if (empty == 1 || inst->top > MAX_SIZE - 1) {return 0;}

    inst->data[inst->top] = *pushValu;
    inst->top = inst->top + 1;
    return 1;
}

int sqStackPop(sqStack *stack, int *popValu) {
    printf("pop a valu from sq stack\n");

    sqStack *inst = stack;

    int success = 2;
    success = sqStackGetTop(inst, popValu);

    return success;
}

int sqStackLength(sqStack *stack) {
    printf("get sq stack length\n");

    return MAX_SIZE;
}

#else
typedef struct linkStackNode {
    int valu;
    struct linkStackNode *next;
}linkStackNode;

typedef struct linkStack {
    int num;
    struct linkStackNode *top;
}linkStack;

void *initLinkStack() {
    printf("link stack init\n");

    linkStack *inst = (linkStack*)malloc(sizeof(linkStack));
    inst->top = NULL;
    inst->num = 0;

    // printf("%s done\n", __FUNCTION__);
    return inst;
}

int linkStackPush(linkStack *head, int valu) {
    printf("link stack push: %d\n", valu);

    if (head == NULL) {
        return 0;
    }

    linkStack *inst = head;

    linkStackNode *new;
    new = (linkStackNode*)malloc(sizeof(linkStack));
    new->valu = valu;
    new->next = inst->top;
    inst->top = new;
    inst->num++;

    // printf("%s done\n", __FUNCTION__);
    return 1;
}

int linkStackPop(linkStack *head, int *valu) {
    printf("link stack pop: ");

    if (head == NULL || head->top == NULL || head->num <= 0) {
        printf("pop error\n");
        return 0;
    }

    linkStack *inst = head;

    linkStackNode *popNode;
    popNode = inst->top;
    inst->top = inst->top->next;
    inst->num--;

    *valu = popNode->valu;
    free(popNode);

    printf("%d\n", *valu);
    return 1;
}

int clearLinkStack(linkStack *lStack) {
    printf("link stack clear\n");
    if (lStack == NULL) {return 0;}

    linkStack *inst = lStack;
    linkStackNode *deleteNode;
    deleteNode = inst->top;

    while(deleteNode != NULL) {
        inst->top = inst->top->next;
        inst->num--;
        free(deleteNode);
        deleteNode = inst->top;
    }
    return 1;
}

int deleteLinkStack(linkStack *lStack) {
    printf("link stack delete\n");

    linkStack *inst = lStack;
    if(inst != NULL) {
        clearLinkStack(inst);
        free(lStack);
    }
    return 1;
}

int linkStackGetTop(linkStack *lStack, int *valu) {
    printf("get link stack top value\n");

    linkStack *inst = lStack;

    if (inst->num <= 0) {return 0;}

    *valu = inst->top->valu;

    return 1;
}

int linkStackLength(linkStack *lStack) {
    printf("get link stack length\n");

    return lStack->num;
}

#endif

void main() {
#ifdef ENABLE_SQSTACK
    sqStack *stack;

    int success = 2;

    printf("%p\n", stack);

    stack = initSqStack(MAX_SIZE);

    printf("%p, %p, %d, %d\n", stack, stack->data, stack->data[0], stack->data[1]);

    int empty = 2;
    sqStackEmpty(stack, &empty);
    printf("%d\n", empty);

    int topValu;
    success = sqStackGetTop(stack, &topValu);
    if (success == 1) {
        printf("%d\n", topValu);
    } else {
        printf("error\n");
    }

    int pushValu = 100;
    sqStackPush(stack, &pushValu);
    printf("push success: %d\n", success);

    int popValu;
    success = sqStackPop(stack, &popValu);
    if (success == 1) {
        printf("%d\n", popValu);
    } else {
        printf("error\n");
    }

    deleteSqStack(stack);
    printf("%p, %p\n", stack, stack->data);

#else

    int success;
    linkStack *lStack;
    printf("lStack = %p\n", lStack);
    lStack = (linkStack*)initLinkStack();
    printf("lStack = %p, lStack->num = %d, lStack->top = %p\n", lStack, lStack->num, lStack->top);

    int pushData = 100;
    linkStackPush(lStack, pushData);
    printf("lStack->num = %d, lStack->top = %p, pushData = %d\n", lStack->num, lStack->top, pushData);

    pushData = 200;
    linkStackPush(lStack, pushData);
    printf("lStack->num = %d, lStack->top = %p, pushData = %d\n", lStack->num, lStack->top, pushData);

    int popData = 0;
    linkStackPop(lStack, &popData);
    printf("lStack->num = %d, lStack->top = %p, popData = %d\n", lStack->num, lStack->top, popData);

    linkStackPop(lStack, &popData);
    printf("lStack->num = %d, lStack->top = %p, popData = %d\n", lStack->num, lStack->top, popData);

    success = linkStackPop(lStack, &popData);

    for (int i = 0; i < 10; i++) {
        linkStackPush(lStack, i);
    }
    linkStackPop(lStack, &popData);

    int len = linkStackLength(lStack);
    printf("link stack length = %d\n", len);

    int topValu;
    linkStackGetTop(lStack, &topValu);
    printf("topValu = %d\n", topValu);

    clearLinkStack(lStack);
    len = linkStackLength(lStack);
    printf("link stack length = %d\n", len);

    deleteLinkStack(lStack);

    printf("lStack->top = %p\n", lStack->top);

#endif

    return;
}

