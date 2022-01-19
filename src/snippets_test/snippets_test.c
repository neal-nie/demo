/* this file is used to test snippets */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Increase Sort:
// int values[] = {5, 20, 1, 23, 17, 55, 27, 17};
// qsort(values, sizeof(values) / sizeof(values[0]), sizeof(int), IncreaseCmp);
int IncreaseCmp(const void *value0, const void *value1)
{
    return (*(int *)value0 - *(int *)value1);
}


void ArrayVisit(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("\t[%d]", arr[i]);
    }
    printf("\n");
}

int main()
{
    int values[] = {5, 20, 1, 23, 17, 55, 27, 17};
    char str[20] = "\0";
    char buffer[20];
    printf("Before sort:\n");
    ArrayVisit(values, sizeof(values) / sizeof(values[0]));
    qsort(values, sizeof(values) / sizeof(values[0]), sizeof(int), IncreaseCmp);
    printf("After sort:\n");
    ArrayVisit(values, sizeof(values) / sizeof(values[0]));
    for (size_t i = 0; i < 5; i++)
    {
        printf("Input your string:\n");
        // scanf("%s", buffer);
        gets(buffer);
        strncat(str, buffer, 1);
        printf("the new string: [%s]\n", str);
    }
    
    return 0;
}