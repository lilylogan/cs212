// header file for queue funcitonality (used by project3A_queue.c and project3A.c)

#ifndef PROJECT3A_QUEUE_H
#define PROJECT3A_QUEUE_H

#include <stdio.h>


// define initially queue size and max string length
#define INITIAL_QUEUE_SIZE 10
#define MAX_STRING_LEN 256
#define INITIAL_CAPACITY 8

// define data type Queue structure
typedef struct {
	char** array;	// Queue array - pointer to a char data type
	int front; 			// Queue front index, initially 0
	int rear;			// Queue rear index, initially 0
	int capacity; 		// Queue capacity, initially 8
	int size; 			// Queue array populated count, initially 0
} Queue;

// define the queue function prototypes
void initialize(Queue* q);

void cleanup(Queue* q);

int isFull(Queue* q);

int isEmpty(Queue* q);

void resize(Queue* q);

void enqueue(Queue* q, char* value);

char* dequeue(Queue* q);

void printQueue(Queue* q);

#endif // PROJECT3A_QUEUE_H