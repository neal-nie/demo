/* test script for lib functions */

#include "stdio.h"
#include "queue.h"

void ShowQueueInfo(Queue *pQueue)
{
    printf("\tLength:\t[%d]\n", QueueGetLength(pQueue));
    printf("\tIs Empty:\t[%d]\n", QueueIsEmpty(pQueue));
    printf("\tIs Full:\t[%d]\n", QueueIsFull(pQueue));
    QueueShow(pQueue, false);
}

int main()
{
    QueueInfo d0 = {
        .x = 1,
        .y = 100,
    };
    QueueInfo d1;
    puts("Create a new Queue:");
    Queue *pQueue = QueueCreate(10);
    ShowQueueInfo(pQueue);
    printf("Enqueue: x=[%d], y=[%d]\n", d0.x, d0.y);
    EnQueue(pQueue, &d0);
    ShowQueueInfo(pQueue);
    puts("Enqueue 6 data");
    for (size_t i = 0; i < 6; i++)
    {
        d0.x++;
        d0.y--;
        EnQueue(pQueue, &d0);
    }
    ShowQueueInfo(pQueue);
    puts("Dequeue 7 data");
    for (size_t i = 0; i < 7; i++)
    {
        DeQueue(pQueue, &d1);
        printf("\tx=[%d], y=[%d]\n", d1.x, d1.y);
    }
    ShowQueueInfo(pQueue);
    printf("Dequeue Return: [%d]. \n", DeQueue(pQueue, &d1));
    printf("\tx=[%d], y=[%d]\n", d1.x, d1.y);
    puts("Enqueue 6 data");
    for (size_t i = 0; i < 6; i++)
    {
        d0.x++;
        d0.y--;
        EnQueue(pQueue, &d0);
    }
    ShowQueueInfo(pQueue);
    puts("Enqueue 6 data");
    for (size_t i = 0; i < 6; i++)
    {
        d0.x++;
        d0.y--;
        EnQueue(pQueue, &d0);
    }
    ShowQueueInfo(pQueue);

    return 0;
}