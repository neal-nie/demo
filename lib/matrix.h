/*
 * Copyright (c) 2022-2022 Neal Nie. All rights reserved.
 * Description: matrix operation
 */

#include <stddef.h>

typedef struct
{
    int **data;
    size_t rowNum;
    size_t colNum;
} Matrix;

Matrix *MatrixCreate(int *dataArr, size_t dataNum, size_t colNum);

void MatrixShow(Matrix *pMatrix);
