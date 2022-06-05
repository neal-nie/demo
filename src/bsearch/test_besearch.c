/*
 * Copyright (c) 2022-2022 Neal Nie. All rights reserved.
 * Description: test stdlib bsearch function
 */

#include <stdlib.h>
#include <stdio.h>

int IncreaseCmp(const void *value0, const void *value1)
{
    return (*(int *)value0 - *(int *)value1);
}

void ShowList(const int *list, size_t len)
{
    // int *ptr = &(list[0]);
    printf("[");
    for (size_t i = 0; i < len; i++)
    {
        printf("%d, ", list[i]);
    }
    printf("]\n");
}

int main()
{
    int values[] = {};
    int key = 17;
    size_t length = sizeof(values) / sizeof(values[0]);

    printf("Raw List of length [%d]: \n\t", length);
    ShowList(values, length);

    printf("Test qsort: \n\t");
    qsort(values, length, sizeof(int), IncreaseCmp);
    ShowList(values, length);

    printf("Test bsearch with key [%d]: \n", key);
    int *rlt = (int *)bsearch(&key, values, length, sizeof(int), IncreaseCmp);
    printf("\tList head at [%p].\n", values);
    if (rlt)
    {
        size_t offset = rlt - values;
        printf("\tFound key at [%p] index=[%d].\n", rlt, offset);
    }
    else
    {
        printf("\tNot found key.");
    }
    return 0;
}