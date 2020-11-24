#include "stdint.h"
#include "stdio.h"

#include "functionPointer.h"

void main() {

    int num = 1;
    helloWorld(&num);

    num++;
    functionPointer funcP;
    funcP = &helloWorld;
    (*funcP)(&num);
    num++;
    funcP(&num);

    num++;
    helloWorldWrapper(funcP, &num);

    num++;
    void (*funcPWrapper)(functionPointer, int*) = &helloWorldWrapper;
    (*funcPWrapper)(funcP, &num);

    return;
}

void helloWorld(int* num) {
    printf("hello world, %d\n", *num);
}

void helloWorldWrapper(functionPointer funcP, int* num) {
    funcP(num);
}
