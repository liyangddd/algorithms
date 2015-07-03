#include "3queue.h"
#include "test.h"

struct QueueRecord {
	int capacity;
	int front;
	int rear;
	int size;
	ElementTypeQueue *array;
};

int IsEmpty(Queue q) {
	return q->size == 0;
}

void MakeEmpty(Queue q) {
	q->size = 0;
	q->front = 0;
	q->rear = 0;
}

int IsFull(Queue q) {
	return q->capacity == q->size;
}

Queue CreateQueue(int MaxElements) {
	Queue q;
	q = (struct QueueRecord *)malloc(sizeof(QueueRecord));
	if (NULL == q) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	q->array = (ElementTypeQueue *)malloc(MaxElements * sizeof(ElementTypeQueue));
	if (NULL == q->array) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	q->capacity = MaxElements;
	MakeEmpty(q);
	return q;
}

void DisposeQueue(Queue q) {
	if (NULL != q) {
		free(q->array);
		free(q);
	}
}

void Enqueue(ElementTypeQueue value, Queue q) {
	if (!IsFull(q)) {
	    q->array[q->rear] = value;
		q->rear = ++q->rear % q->capacity;
		q->size += 1;
	}
	else {
		cout << "Queue is full." << endl;
	}
}

void Dequeue(Queue q) {
	if (!IsEmpty(q)) {
		q->front = ++q->front % q->capacity;
		q->size -= 1;
	}
	else {
		cout << "Queue is empty." << endl;
	}
}

ElementTypeQueue Front(Queue q) {
	return q->array[q->front];
}

ElementTypeQueue FrontAndDequeue(Queue q) {
	if (!IsEmpty(q)) {
		q->size -= 1;
		return q->array[q->front++];
	}
	else {
		cout << "Queue is empty." << endl;
		return 0;
	}
}

void DisplayQueueValues(Queue q) {
	if (IsEmpty(q)) {
		cout << "Queue is empty." << endl;
		return;
	}
	else {
		int i = 0;
		while (i < q->size) {
			cout << q->array[(q->front + i++)% q->capacity] << " ";
		}
		cout << endl;
	}
}
/*
int main() {
	Queue q = CreateQueue(6);
	Enqueue(2, q);
	Enqueue(444, q);
	Enqueue(9, q);
	DisplayQueueValues(q);
	cout << Front(q) << endl;
	return 0;
}
*/
