#include "stdio.h"
#include "stdlib.h"

int aa[3][2] = {
    {1, 10},
    {3, 4},
    {5, 6}
};

void main() {
    int raw, cal;
    raw = 3;
    cal = 2;

    int *p;
    p = (int*)malloc(raw * cal * sizeof(int));

    int (*matrix)[cal];
    int (*matrix_1)[3];

    matrix = aa;
    matrix_1 = aa;
    // matrix_1 = (int (*)[3])aa;

    printf("%p, %p\n", *aa, *matrix);
    printf("%p, %p\n", *aa + 1, aa[1]);
    printf("%p, %p\n", *matrix + 1, matrix[1]);
    printf("%p, %p\n", *matrix + 2, matrix[2]);
    printf("%p, %p\n", *matrix + 3, matrix[3]); // 越界
    printf("%p, %p\n", *matrix + 3, matrix_1[1]);

    matrix = (int*)malloc(raw * cal * sizeof(int));
    // matrix = (int(*)[cal])malloc(raw * cal * sizeof(int));

    int val = 10;
    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < cal; j++) {
            *(matrix[i] + j) = val;
            val--;
        }
    }
    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < cal; j++) {
            printf("%d, ", matrix[i][j]);
        }
    }
    printf("\n");
    return;
}