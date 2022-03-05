/*
 * Copyright (c) 2022-2022 Neal Nie. All rights reserved.
 * Description: matrix operation
 */

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix *MatrixCreate(int *dataArr, size_t dataNum, size_t colNum)
{
    if (dataArr == NULL)
    {
        printf("Error: invalid dataArr [NULL]\n");
        return NULL;
    }
    if (dataNum == 0)
    {
        printf("Error: invalid dataNum [%d]\n", dataNum);
        return NULL;
    }
    if (colNum == 0)
    {
        printf("Error: invalid colNum [%d]\n", colNum);
        return NULL;
    }
    size_t rowNum = dataNum / colNum;
    size_t leftNum = dataNum - rowNum * colNum;
    if (leftNum != 0)
    {
        printf("Warning: dataArr converted to [%d*%d] Matrix with [%d] data ignored.\n", rowNum, colNum, leftNum);
    }
    Matrix *pMatrix = (Matrix *)malloc(sizeof(Matrix));
    if (pMatrix == NULL)
    {
        printf("Error: failed to malloc pointer to matrix!\n");
        return NULL;
    }
    int **pData = (int **)malloc(rowNum * sizeof(int **));
    if (pData == NULL)
    {
        printf("Error: failed to malloc pointer to matrix data!\n");
        return NULL;
    }
    for (size_t i = 0; i < rowNum; i++)
    {
        *(pData + i) = dataArr + i * colNum;
    }
    pMatrix->data = pData;
    pMatrix->colNum = colNum;
    pMatrix->rowNum = rowNum;
    return pMatrix;
}

void MatrixShow(Matrix *pMatrix)
{
    if (pMatrix == NULL)
    {
        printf("Error: invalid pMatrix[NULL]\n");
        return;
    }
    printf("Matrix: [%d*%d]\n", pMatrix->rowNum, pMatrix->colNum);
    int **pData = pMatrix->data;
    for (size_t i = 0; i < pMatrix->rowNum; i++)
    {
        printf("row[%d]:\t", i);
        for (size_t j = 0; j < pMatrix->colNum; j++)
        {
            printf("[%d]\t", *(pData[i] + j));
        }
        printf("\n");
    }
}