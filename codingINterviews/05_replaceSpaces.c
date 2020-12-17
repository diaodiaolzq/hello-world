#include "stdio.h"
#include "stdlib.h"

#define MAX_STRING_LEN  100

void replaceBlankSpace(char *string) {
    if (string == NULL) {return;}
    int strLen = 0;
    int blankSpaceNum = 0;
    char *p1, *p2;
    p1 = string;
    while (*p1 != '\0') {
        strLen++;
        if(*p1 == ' ') {
            blankSpaceNum++;
        }
        p1++;
    }
    p2 = p1 + 2 * blankSpaceNum;
    while (p1 != p2) {
        if (*p1 == ' ') {
            p1--;
            *p2 = '0';
            p2--;
            *p2 = '2';
            p2--;
            *p2 = '%';
            p2--;
        } else {
            *p2 = *p1;
            p1--;
            p2--;
        }
    }
}

void test(char *testCase, char *string, char *expectResult) {
    if (testCase == NULL) {return;}
    printf("%s begins: ", testCase);
    replaceBlankSpace(string);
    if (string != NULL && expectResult != NULL) {
        while (*expectResult != '\0') {
            if (*string != *expectResult) {
                break;
            }
            string++;
            expectResult++;
        }
        if (*string == *expectResult) {
            printf("passed.\n");
        } else {
            printf("failed.\n");
        }
    } else if (string == expectResult) {
        printf("passed.\n");
    } else {
        printf("failed.\n");
    }
}

void test_1() {
    char string[MAX_STRING_LEN] = "we are happy";
    char expect[MAX_STRING_LEN] = "we%20are%20happy";
    test("test case 1", string, expect);
}

void test_2() {
    char string[MAX_STRING_LEN] = " we are happy";
    char expect[MAX_STRING_LEN] = "%20we%20are%20happy";
    test("test case 2", string, expect);
}

void test_3() {
    char string[MAX_STRING_LEN] = "we are happy ";
    char expect[MAX_STRING_LEN] = "we%20are%20happy%20";
    test("test case 3", string, expect);
}

void test_4() {
    char string[MAX_STRING_LEN] = " we are happy ";
    char expect[MAX_STRING_LEN] = "%20we%20are%20happy%20";
    test("test case 4", string, expect);
}

void test_5() {
    char string[MAX_STRING_LEN] = "we  are happy";
    char expect[MAX_STRING_LEN] = "we%20%20are%20happy";
    test("test case 5", string, expect);
}

void test_6() {
    char string[MAX_STRING_LEN] = "  ";
    char expect[MAX_STRING_LEN] = "%20%20";
    test("test case 6", string, expect);
}

void test_7() {
    char *string = NULL;
    char *expect = NULL;
    test("test case 7", string, expect);
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    return EXIT_SUCCESS;
}