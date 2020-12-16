#include "stdio.h"
#include "stdlib.h"

int duplicate(int array[], int arrayLen, int *duplicatedValue)
{
    if (array == NULL || arrayLen <= 0) {return EXIT_FAILURE;}
    for (int i = 0; i < arrayLen; i++)
    {
        if (array[i] >= arrayLen) {return EXIT_FAILURE;}
    }
    for (int i = 0; i < arrayLen; i++)
    {
        while (array[i] != i)
        {
            if (array[array[i]] == array[i])
            {
                *duplicatedValue = array[i];
                return EXIT_SUCCESS;
            } else
            {
                // swap
                int temp = array[i];
                array[i] = array[array[i]];
                array[temp] = temp;
            }
        }
    }
    return EXIT_FAILURE;
}


int main()
{
    int array1[7] = {2, 3, 1, 0, 2, 5, 3};
    int array2[7] = {2, 3, 1, 0, 4, 6, 5};
    int duplValue;
    int returnValue;

    // case 1
    printf("test case 1: ");
    duplValue = -1;
    returnValue = -1;
    returnValue = duplicate(array1, 7, &duplValue);
    printf("return value: %d, duplicated value: %d\n", returnValue, duplValue);

    // case 2
    duplValue = -1;
    returnValue = -1;
    printf("test case 2: ");
    returnValue = duplicate(array2, 7, &duplValue);
    printf("return value: %d, duplicated value: %d\n", returnValue, duplValue);
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", array2[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}