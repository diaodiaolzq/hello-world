#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define MAX_SIZE    100

int stringToNumber(char *string, int *number) {
    if (string == NULL || *string == '\0') {return EXIT_FAILURE;}
    int stringTemp = -1;
    long num = 0;
    if (*string == '-' || *string == '+') {
        stringTemp = *string == '-' ? 1 : 0;
        string++;
    }
    while (*string != '\0') {
        if (*string <= '9' && *string >= '0') {
            num = num * 10 + *string - '0';
            string++;
        } else {
            return EXIT_FAILURE;
        }
    }
    if (num > INT32_MAX || num < INT32_MIN) {
        return EXIT_FAILURE;
    }
    if (stringTemp == 1) {
        num = -num;
    }
    *number = num;
    return EXIT_SUCCESS;
}

int stringPrintf(char *string) {
    if (string == NULL) {return EXIT_FAILURE;}
    while(*string != '\0') {
        printf("%c", *string);
        string++;
    }
    return EXIT_SUCCESS;
}

int indexStr(char *stringS, char *stringT, int *pos) {
    if (stringS == NULL || stringT == NULL) {return EXIT_FAILURE;}
    if (*(stringS) == '\0' && *(stringT) == '\0') {
        *pos = 0;
        return EXIT_SUCCESS;
    }
    int i, j;
    i = 0;
    j = 0;
    while (*(stringS + i) != '\0' && *(stringT + j) != '\0') {
        int ii = i;
        int jj = j;
        while (*(stringS + ii) == *(stringT + jj)) {
            if(*(stringS + ii) == '\0') {break;}
            ii++;
            jj++;
        }
        if (*(stringT + jj) == '\0') {
            *pos = i;
            return EXIT_SUCCESS;
        } else {
            i++;
        }
    }
    return EXIT_FAILURE;
}

int indexStr1(char *stringS, char *stringT, int *pos) {
    if (stringS == NULL || stringT == NULL) {return EXIT_FAILURE;}
    int stringSLen, stringTLen;
    stringSLen = 0;
    stringTLen = 0;
    while (*(stringS + stringSLen) != '\0') {stringSLen++;}
    while (*(stringT + stringTLen) != '\0') {stringTLen++;}
    int i, j;
    i = 0;
    j = 0;
    while (i < stringSLen && j < stringTLen) {
        if (*(stringS + i) == *(stringT + j)) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= stringTLen) {
        *pos = i - stringTLen;
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int indexStr2(char *stringS, char *stringT, int *pos) {
    if (stringS == NULL || stringT == NULL) {return EXIT_FAILURE;}
    int i, j;
    i = 0;
    j = 0;
    while (*(stringS + i) != '\0' && *(stringT + j) != '\0') {
        if (*(stringS + i) == *(stringT + j)) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (*(stringT + j) == '\0') {
        *pos = i - j;
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int indexStrKmp(char *stringS, char *stringT, int *pos) {
    if (stringS == NULL || stringT == NULL) {return EXIT_FAILURE;}
}

int getStringLength(char *string, int *length) {
    if (string == NULL || length == NULL) {return EXIT_FAILURE;}
    int len = 0;
    while (*string != '\0') {
        len++;
        string++;
    }
    *length = len;
    return EXIT_SUCCESS;
}

int kmpGetNext(char *string, int *next) {
    if (string == NULL || next == NULL) {return EXIT_FAILURE;}
    int i, j;
    i = 0;
    j = -1;
    *next = -1;
    int strLen = -1;
    getStringLength(string, &strLen);
    while (i < strLen) {
        if (j == -1 || *(string + i) == *(string + j)) {
            i++;
            j++;
            *(next + i) = j;
        } else {
            j = *(next + j);
        }
    }
    return EXIT_SUCCESS;
}
int main() {
    int testCase = 4;
    char *str;
    char *strS;
    char *strT;
    switch (testCase) {
    case 0:
        str = "0123456789";
        strS = "goodgoogle";
        strT = "google";
        break;
    case 1:
        str = "01234567899876543210123456789";
        strS = "google";
        strT = "goodgoogle";
        break;
    case 2:
        str = "+123";
        strS = "goodgoogle";
        strT = "goodgoogle";
        break;
    case 3:
        str = "-123";
        strS = "";
        strT = "";
        break;
    case 4:
        str = "";
        strS = "abababca";
        strT = "aaaaaaaab";
        break;
    case 5:
        str = "-12(3";
        break;
    default:
        printf("unsupport test case, exit.\n");
        return EXIT_FAILURE;
        break;
    }

    int returnValu = -1;
    int num = 0;
    printf("testCase: %d, string = \"", testCase);
    returnValu = stringPrintf(str);
    if (returnValu == 0) {printf("\"\n");}
    returnValu = stringToNumber(str, &num);
    printf("returnValu = %d, num = %d\n", returnValu, num);

    int pos = -1;
    returnValu = -1;
    returnValu = indexStr1(strS, strT, &pos);
    printf("returnValu = %d, pos = %d\n", returnValu, pos);

    int strLen = -1;
    returnValu = -1;
    returnValu = getStringLength(strT, &strLen);
    printf("returnValu = %d, string length = %d\n", returnValu, strLen);
    int next[strLen];
    returnValu = -1;
    returnValu = kmpGetNext(strT, (int*)(next));
    if (returnValu == 0) {
        for (int i = 0; i < strLen; i++) {
            printf("%d ", next[i]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
