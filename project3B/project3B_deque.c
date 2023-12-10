// deque implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "project3B_deque.h"


Node *newNode(void *data, size_t dataSize) {
	Node *node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Error allocating memory for node.");
		exit(EXIT_FAILURE);
	}
	node->data = (void*)malloc(dataSize);
	if (node->data == NULL){
		fprintf(stderr, "Error allocating memory for node data.");
		exit(EXIT_FAILURE);
	}
	memcpy(node->data, data, dataSize);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

Deque *createDeque() {
	Deque *deque = (Deque*)malloc(sizeof(Deque));
	if (deque == NULL) {
		fprintf(stderr, "Error allocating memory for deque");
		exit(EXIT_FAILURE);
	}

	deque->front = NULL;
	deque->back = NULL;

	deque->count = 0;
	return deque;

}

void insertFront(Deque *deque, void *data, size_t dataSize) {
	Node *new = newNode(data, dataSize);

	if (deque->front == NULL) {
		deque->front = new;
		deque->back = new;
	}

	else {
		new->next = deque->front;
		(deque->front)->prev = new;
		deque->front = new;
	}

	deque->count++;
}

void insertBack(Deque *deque, void *data, size_t dataSize) {
	Node *new = newNode(data, dataSize);

	if (deque->back == NULL) {
		deque->back = new;
		deque->front = new;
	}

	else {
		new->prev = deque->back;
		deque->back->next = new;
		deque->back = new;
	}

	deque->count++;
}

void removeFront(Deque *deque, void *data, size_t dataSize) {
	if (deque->count == 0) {
		printf("Deque is empty or there is no front node");
		return;
	}

	Node *currentNode = deque->front;
	memcpy(data, deque->front->data, dataSize);

	if (deque->count == 1) {
		// only one node
		deque->front = NULL;
		deque->back = NULL;
	}

	if (deque->count > 1) {
		deque->front = currentNode->next;
		deque->front->prev = NULL;
	}

	free(currentNode->data);
	free(currentNode);
	deque->count--;
}

void removeBack(Deque *deque, void *data, size_t dataSize) {
	if (deque->count == 0) {
		printf("Deque is empty or there is no back node");
		return;
	}

	Node *currentNode = deque->back;
	memcpy(data, deque->back->data, dataSize);

	if(deque->count == 1) {
		// only one node, both front and back
		deque->front = NULL;
		deque->back = NULL;
	}
	
	if (deque->count > 1) {
		deque->back = currentNode->prev;
		(deque->back)->next = NULL;
	}

	free(currentNode->data);
	free(currentNode);
	deque->count--;
}

void freeDeque(Deque *deque) {
	Node *currentNode = deque->front;
	while(currentNode != NULL) {

		deque->front = currentNode->next;

		free(currentNode->data);
		free(currentNode);
		currentNode = deque->front;

		deque->count--;
	}
	free(deque);
}

void printDeque(Deque *deque, printData print) {
	Node *currentNode = deque->front;
	while (currentNode != NULL) {
		print(currentNode->data);
		printf(" ");
		currentNode = currentNode->next;
	}
}