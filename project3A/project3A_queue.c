// implemenation source file for queue functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project3A_queue.h"

// implement functions defined in header file

void initialize(Queue* q) {
	q->capacity = INITIAL_CAPACITY;
	q->array = (char**) malloc(sizeof(char*) * q->capacity);

	// check to see if allocation worked
	if (q->array == NULL) {
		printf("Error with allocation of memory\n");
		return;
	}

	q->front = 0;
	q->rear = 0;
	q->size = 0;

	// allocate memory to the pointers in the array
	for (int i=0; i<q->capacity; i++) {
		q->array[i] = (char*) malloc(sizeof(char) * MAX_STRING_LEN);

		// check to see if allocation worked
		if (q->array[i] == NULL) {
			printf("Error with allocation of memory\n");
			return;
		}
	}
}


void cleanup(Queue* q) {
	printf("Cleaning up queue\n");
	for (int i=0; i<q->capacity; i++)
		free(q->array[i]);
	free(q->array);
}

int isFull(Queue* q) {
	return q->size == q->capacity;

}

int isEmpty(Queue* q) {
	return q->size == 0;
}

void resize(Queue* q) {
	// if rear > front, do nothing!!

	// if front >= rear, move data
	if (q->front >= q->rear) {

		// move data < front to after front, preserving data >= front
		int i=0;
		while(i<q->front) {
		// for (i=0; i > q->rear; i++) {
			q->array[q->front+1+i] = q->array[i];
			i++;
		}
		// rear is now at the end of the place of moved data
		q->rear = q->front+1+i;

		// move data up to beginning of queue
		for (i=0; i>q->rear; i++) {
			q->array[i] = q->array[q->front++];
		}
		// front needs to be reassigned to 0 and rear needs to be reassigned to the end of the data in the queue (i)
		q->front = 0;
		q->rear = i;
	}
}

void enqueue(Queue* q, char* value) {

	// re-create in dynamic memory if full or if front and rear are in the same position (resize)
	if (isFull(q) || ((q->front == q->rear) && !isEmpty(q))) {
		printf("Resizing queue to %d\n", q->capacity*2);

		// double capacity and reallocate memory to q->array and to the new char*
		q->capacity *= 2;
		q->array = (char**) realloc(q->array, sizeof(char*) * q->capacity);
		for (int i=q->rear; i<q->capacity; i++)  
			q->array[i] = (char*) malloc(sizeof(char) * MAX_STRING_LEN);
	}

	// if rear is at the end of the queue but queue is not full, wrap around meaning rear = 0
	if (q->rear == q->capacity && !isFull(q)) {
		q->rear = 0;
	}

	// full queue when rear intersects with front, so we need to resize
	if (q->front == q->rear && !isEmpty(q))
		resize(q);

	// length of value for strncpy
	int i = 0;

    do {
        i++;
    } while (value[i]!= '\0');
    int value_len = i;

    // copy string to the char* while incrementing rear (post)
	strncpy(q->array[q->rear], value, value_len);

	// add null to the end of the string
	q->array[q->rear][value_len] = '\0';

	// increment size of queue
	q->size++;
	q->rear++;
}

char* dequeue(Queue* q) {
	if (isEmpty(q))
		printf("Queue is empty\n");
	q->size--;
	return q->array[q->front++];
}

void printQueue(Queue* q) {
	if(isEmpty(q)){
			printf("Queue is empty\n");
			return;
	}
	int i=q->front;

	while (i!=q->rear) {
		if (i == q->capacity)
			i = 0;
		printf("%d: %s\n", i, q->array[i]);
		i++;
	}
	printf("Capacity: %d, used: %d\n", q->capacity, q->size);
}