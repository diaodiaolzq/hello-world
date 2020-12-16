#include "stdio.h"
#include "stdlib.h"

int countRange(int *array, int arrayLength, int start, int stop, int *count)
{
    if (array == NULL || arrayLength <= 0 || stop < start) {return EXIT_FAILURE;}
    int num = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] >= start && array[i] <= stop) {num++;}
    }
    *count = num;
    return EXIT_SUCCESS;
}

int getDuplication(int array[], int arrayLength, int *duplicatedValue)
{
    if (array == NULL || arrayLength <= 0) {return EXIT_FAILURE;}
    int start = 1;
    int stop = arrayLength - 1;
    int count;
    while (start <= stop)
    {
        int middle = (stop - start) / 2 + start;
        countRange(array, arrayLength, start, middle, &count);
        if (start == stop)
        {
            if (count > 1)
            {
                *duplicatedValue = start;
                return EXIT_SUCCESS;
            }
        }
        if (count > middle - start + 1)
        {
            stop = middle;
        } else
        {
            start = middle + 1;
        }
    }
    return EXIT_FAILURE;
}

int main()
{
    int array[] = { 1, 2, 2, 6, 4, 5, 2 };
    int duplValue;
    int returnValue;

    duplValue = -1;
    returnValue = -1;
    printf("test case 1: ");
    returnValue = getDuplication(array, sizeof(array) / sizeof(int), &duplValue);
    printf("return value: %d, duplicated value: %d\n", returnValue, duplValue);
    for (int i = 0; i < sizeof(array) / sizeof(int); i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}