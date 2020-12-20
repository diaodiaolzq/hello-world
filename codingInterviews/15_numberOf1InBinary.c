#include "stdio.h"
#include "stdlib.h"

int numberOf1(int n) {
    int count = 0;
    uint32_t flag = 1;
    while(flag) {
        if (n & flag) {count++;}
        flag = flag << 1;
    }
    return count;
}

int numberOf1_(int n) {
    int count = 0;
    while(n) {
        count++;
        n = (n - 1) & n;
    }
    return count;
}

void test(int number, unsigned int expected)
{
    int actual = numberOf1(number);
    if (actual == expected)
        printf("Solution1: Test for %d passed.\n", number);
    else
        printf("Solution1: Test for %d failed.\n", number);

    actual = numberOf1_(number);
    if (actual == expected)
        printf("Solution2: Test for %d passed.\n", number);
    else
        printf("Solution2: Test for %d failed.\n", number);

    printf("\n");
}


int main(int argc, char *argv[]) {
    // 输入0，期待的输出是0
    test(0, 0);

    // 输入1，期待的输出是1
    test(1, 1);

    // 输入10，期待的输出是2
    test(10, 2);

    // 输入0x7FFFFFFF，期待的输出是31
    test(0x7FFFFFFF, 31);

    // 输入0xFFFFFFFF（负数），期待的输出是32
    test(0xFFFFFFFF, 32);

    // 输入0x80000000（负数），期待的输出是1
    test(0x80000000, 1);

    return EXIT_SUCCESS;
}