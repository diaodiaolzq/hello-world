#include "stdint.h"
#include "stdio.h"

#include "insertionSort.h"

#define N 8

static int arr[] = {154, 129, 248, 134 , 954, 873, 121, 467};

void main() {

    insertionSort(arr, N);

    return;
}

void insertionSort(int* array, int arrLen) {
    int key, j;
    for (int i = 1; i < arrLen; i++) {
        key = array[i];
        j = i - 1;

        // while(j >= 0) {
        //     if (key < array[j]) {
        //         array[j + 1] = array[j];
        //     } else {
        //         break;
        //     }
        //     j--;
        // }

        while((j >= 0) && (array[j] >= key)) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;

        // log
        printf("i = %d, key = %d:  ", i, key);
        for (int i = 0; i < arrLen; i++) {
            printf("%d, ", array[i]);
        }
        printf("\n");

    }
}