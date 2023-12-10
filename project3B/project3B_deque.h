// header file for deque

#ifndef PROJECT3B_DEQUE_H
#define PROJECT3B_DEQUE_H

#include <stdio.h>

#define MAX_STR_LEN 256


// node and deque data type structures

typedef struct Node 
{
	void *data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Deque 
{
	Node *front;
	Node *back;
	int count;
} Deque;

// deque function prototypes

Node *newNode(void *data, size_t dataSize);
Deque *createDeque();
void insertFront(Deque *deque, void *data, size_t dataSize);
void insertBack(Deque *deque, void *data, size_t dataSize);
void removeFront(Deque *deque, void *data, size_t dataSize);
void removeBack(Deque *deque, void *data, size_t dataSize);
void freeDeque(Deque *deque);
// type to declare the requirements for the deque print function pointer
// creates a new type called printData which is a pointer to the function that takes a void agrument and returns a void
typedef void (*printData)(void *); 
void printDeque(Deque *deque, printData print);

#endif //PROJECT3B_DEQUE_H// header file for deque

#ifndef PROJECT3B_DEQUE_H
#define PROJECT3B_DEQUE_H

#include <stdio.h>

#define MAX_STR_LEN 256


// node and deque data type structures

typedef struct Node 
{
	void *data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Deque 
{
	Node *front;
	Node *back;
	int count;
} Deque;

// deque function prototypes

Node *newNode(void *data, size_t dataSize);
Deque *createDeque();
void insertFront(Deque *deque, void *data, size_t dataSize);
void insertBack(Deque *deque, void *data, size_t dataSize);
void removeFront(Deque *deque, void *data, size_t dataSize);
void removeBack(Deque *deque, void *data, size_t dataSize);
void freeDeque(Deque *deque);
// type to declare the requirements for the deque print function pointer
// creates a new type called printData which is a pointer to the function that takes a void agrument and returns a void
typedef void (*printData)(void *); 
void printDeque(Deque *deque, printData print);

#endif //PROJECT3B_DEQUE_H