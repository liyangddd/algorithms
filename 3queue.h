#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementTypeQueue;
int IsEmpty(Queue q);
int IsFull(Queue q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue q);
void MakeEmpty(Queue q);
void Enqueue(int value, Queue q);
ElementTypeQueue Front(Queue q);
void Dequeue(Queue q);
ElementTypeQueue FrontAndDequeue(Queue q);
void DisplayQueueValues(Queue q);

#endif