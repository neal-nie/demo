/*
 * Copyright (c) 2021-2022 Neal Nie. All rights reserved.
 * Description: library functio for queue operation.
 */

#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define QUEUE_BUF 10

Queue *QueueCreate(int size)
{
    QueueInfo *dataArr = malloc(sizeof(QueueInfo) * size);
    if (dataArr == NULL)
    {
        printf("ERROR: fail to create Queue.\n");
        return NULL;
    }
    memset(dataArr, 0, sizeof(QueueInfo) * size);
    Queue *pQueue = malloc(sizeof(Queue));
    if (pQueue == NULL)
    {
        printf("ERROR: fail to create Queue.\n");
        free(dataArr);
        return NULL;
    }
    pQueue->header = 0;
    pQueue->tailer = 0;
    pQueue->size = size;
    pQueue->dataArr = dataArr;
    return pQueue;
}

static int QueueMovePosForward(const Queue *pQueue, int pos)
{
    if (pos >= pQueue->size || pos < 0)
    {
        printf("ERROR: get invalid pos [%d], not in [0, %d).\n", pos, pQueue->size);
        return 0;
    }
    int posForward = pos + 1;
    return (posForward == pQueue->size) ? 0 : posForward;
}

bool QueueIsEmpty(const Queue *pQueue)
{
    return pQueue->header == pQueue->tailer;
}

bool QueueisFull(const Queue *pQueue)
{
    return pQueue->header == QueueMovePosForward(pQueue, pQueue->tailer);
}

bool EnQueue(Queue *pQueue, const QueueInfo *data)
{
    if (QueueisFull(pQueue))
    {
        printf("ERROR: queue overflow.\n");
        return false;
    }
    pQueue->dataArr[pQueue->tailer] = *data;
    pQueue->tailer = QueueMovePosForward(pQueue, pQueue->tailer);
    return true;
}

bool DeQueue(Queue *pQueue, QueueInfo *data)
{
    if (QueueisFull(pQueue))
    {
        printf("ERROR: queue underflow.\n");
        return false;
    }
    *data = pQueue->dataArr[pQueue->header];
    pQueue->header = QueueMovePosForward(pQueue, pQueue->header);
    return true;
}

int QueueGetLength(const Queue *pQueue)
{
    int length = pQueue->tailer - pQueue->header;
    return (length < 0) ? (length + pQueue->size) : length;
}

bool QueueIsContain(const Queue *pQueue, const QueueInfo *data)
{
    int i = pQueue->header;
    while (i != pQueue->tailer)
    {
        if (0 == memcmp(&pQueue->dataArr[i], data, sizeof(QueueInfo)))
        {
            return true;
        }
        i = QueueMovePosForward(pQueue, i);
    }
    return false;
}

void QueueVisit(const Queue *pQueue)
{
    int i = pQueue->header;
    char buffer[QUEUE_BUF];
    printf("Visit Queue Data as <U8-Hex>:");
    while (i != pQueue->tailer)
    {
        printf("\n\tAt [%d]:\t");
        unsigned char *pChr = (unsigned char *)&pQueue->dataArr[i];
        for (size_t j = 0; j < sizeof(QueueInfo); j++)
        {
            printf("%X ", *pChr);
            pChr++;
        }
        i = QueueMovePosForward(pQueue, i);
    }
}
