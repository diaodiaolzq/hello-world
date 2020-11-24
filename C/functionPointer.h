#ifndef C_FUNCTIONPOINTER_H
#define C_FUNCTIONPOINTER_H

typedef void (*functionPointer)(int*);

void helloWorld(int* num);
void helloWorldWrapper(functionPointer funcP, int* num);

#endif