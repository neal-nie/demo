/*
 * Copyright (c) 2021-2022 Neal Nie. All rights reserved.
 * Description: library functio for queue operation.
 * Queue Structure:
 * Data:   Empty  D1   D2  ... Dn  Empty ... Empty
 * Array:  [0]   [1]   [2]     [n] [n+1] ... [size-1]
 *                ^                  ^
 * Queue:      header               tailer
 */
#include <stdbool.h>

typedef struct
{
    // element could be modified for application.
    int x;
    int y;
} QueueInfo;

typedef struct
{
    int size;
    int header;
    int tailer;
    QueueInfo *dataArr;
} Queue;

// create Queue
Queue *QueueCreate(int size);

// check Queue is Empty or not
bool QueueIsEmpty(const Queue *pQueue);

// check Queue is Full or not
bool QueueIsFull(const Queue *pQueue);

// enqueue data into Queue
bool EnQueue(Queue *pQueue, const QueueInfo *data);

// dequeue data from Queue
bool DeQueue(Queue *pQueue, QueueInfo *data);

// get data length in Queue
int QueueGetLength(const Queue *pQueue);

// check data in Queue or not
bool QueueIsContain(const Queue *pQueue, const QueueInfo *data);

// visit data in Queue as U8-Hex.
// showAll: true, visit whole buffer; false, data part.
void QueueShow(const Queue *pQueue, bool showAll);
