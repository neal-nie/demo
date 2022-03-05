#include "matrix.h"

int main()
{
    int data[] = {1, 2, 4, 5, 6, 7, 4, 3, 5, 6, 3, 6};
    Matrix *pMap = MatrixCreate(data, sizeof(data) / sizeof(data[0]), 5);
    MatrixShow(pMap);
    return 0;
}