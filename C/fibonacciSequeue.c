#include "stdio.h"
#include "stdlib.h"
#define ENABLE_REGRESSION

#ifdef ENABLE_REGRESSION
int fibonacciGen(int i) {
    if (i < 2) {
        return i == 0 ? 0 : 1;
    }
    return fibonacciGen(i - 1) + fibonacciGen(i - 2);
}
int* fibonacci(int len) {
    int *head;
    head = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        head[i] = fibonacciGen(i);
    }
    return head;
}
#else
int* fibonacci(int len) {
    int *head;
    head = (int*)malloc(len * sizeof(int));
    head[0] = 0;
    head[1] = 1;
    for (int i = 2; i < len; i++) {
        head[i] = head[i - 1] + head[i - 2];
    }
    return head;
}
#endif

int main() {
    int fibonacciSeqLen = 40;
    int *fibonacciSeq;
    fibonacciSeq = fibonacci(fibonacciSeqLen);
    for (int i = 0; i < fibonacciSeqLen; i++) {
        printf("%d ", fibonacciSeq[i]);
    }
    printf("\n");
    return 1;
}