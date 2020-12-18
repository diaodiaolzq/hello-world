#include "stdio.h"
#include "stdlib.h"

int find(int *matrix, int raw, int col, int value) {
    if (matrix == NULL && raw > 0 && col > 0) {return EXIT_FAILURE;}
    int raw_ = raw;
    int col_ = col;
    while (col_ > 0 && raw_ > 0) {
#ifdef DEBUG
        printf("\n===================\n");
        for (int i = 0; i < raw; i++) {
            for (int j = 0; j < col; j++) {
                if (i >= (raw - raw_) && j < col_) {
                    printf("%d ", *(matrix + i * col + j));
                }
            }
            printf("\n");
        }
#endif
        int temp = *(matrix + (raw - raw_) * col + col_ - 1);
        if (temp == value) {
            return EXIT_SUCCESS;
        } else if (temp < value) {
            raw_--;
        } else {
            col_--;
        }
    }
    return EXIT_FAILURE;
}

void test(char* testName, int *matrix, int raw, int col, int value, int expectResult) {
    if (testName == NULL) {return;}
    printf("%s begins: ", testName);
    int result = expectResult - 1;
    result = find(matrix, raw, col, value);
    if (result == expectResult) {
        printf("passed.\n");
    } else {
        printf("failed.\n");
    }
}

void test_1() {
    int matrix[][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}
    };
    int raw = 4;
    int col = 4;
    int value = 10;
    int expectResult = EXIT_SUCCESS;
    test("test 1", (int*)matrix, raw, col, value, expectResult);
}

void test_2() {
    int matrix[][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}
    };
    int raw = 4;
    int col = 4;
    int value = 3;
    int expectResult = EXIT_FAILURE;
    test("test 2", (int*)matrix, raw, col, value, expectResult);
}

void test_3() {
    int matrix[][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}
    };
    int raw = 4;
    int col = 4;
    int value = 0;
    int expectResult = EXIT_FAILURE;
    test("test 3", (int*)matrix, raw, col, value, expectResult);
}

void test_4() {
    int matrix[][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}
    };
    int raw = 4;
    int col = 4;
    int value = 16;
    int expectResult = EXIT_FAILURE;
    test("test 4", (int*)matrix, raw, col, value, expectResult);
}

void test_5() {
    int *matrix = NULL;
    int raw = 4;
    int col = 4;
    int value = 16;
    int expectResult = EXIT_FAILURE;
    test("test 5", (int*)matrix, raw, col, value, expectResult);
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    return EXIT_SUCCESS;
}