#include <algorithm>    // std::swap
#include <vector>       // std::vector
#include <string>       // std::vector
#include <cstddef>
#include "stdlib.h"
#include "stdio.h"

using namespace std;


void swapData(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *arr, int len) {
    for (int i = 0; i < len; i++) {             // NOTE: the range of i and j and their change direction
        for (int j = len - 1; j > i; j--) {
            if (arr[j] < arr[j - 1]) {
                swapData(&arr[j], &arr[j - 1]);
            }
        }
    }
}

void selectSort(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        int min_ind = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        if (min_ind != i) {
            swapData(&arr[i], &arr[min_ind]);
        }
    }
}

void insertSort(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        int temp = arr[i];
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > temp) {
                arr[j + 1] = arr[j];
                arr[j] = temp;          // NOTE: "arr[j] = temp" is necessary
            } else {
                arr[j] = temp;
                break;
            }
        }
    }
}

int main() {
    // int A[11] = {1, 8, 8, 1, 1, 1, 3, 3, 5, 4, 0};
    int A[3] = {3, 2, 1};
    insertSort(A, sizeof(A) / sizeof(int));
    return 0;
}