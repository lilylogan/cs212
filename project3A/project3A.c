// contains main 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project3A_queue.h"

int main(int agrc, char *argv[]) {

	// accepts two command line arguments, input file and tokenizer delimiter string (if there are 2 arguments)
	if (agrc!=3) {
		printf("Please provide a file name and a delimiter\n");
		return 1;
	}

	const char* delimiter = argv[2];

	// open file
	FILE *file = fopen(argv[1], "r");

	// produce error message if input file cannot be read
	if (file==NULL){
		printf("Could not open file %s\n", argv[1]);
	}

	// find the length of the file, set back to beginning, and create buffer
	fseek(file, 0, SEEK_END);
	int file_len = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = (char *)malloc(sizeof(char) *file_len +1);


	// check to see if memory allocation of buffer worked
	if (buffer==NULL) {
		printf("Error with allocation of memory");
		return 1;
	}

	// read the file into the buffer
	fread(buffer, sizeof(char), file_len, file);
	buffer[file_len] = '\0';

	// initialize the queue and allocate memory
	Queue *q = (Queue*) malloc(sizeof(Queue));
	initialize(q);

	// tokenize the string loaded from the file
	char *token = strtok(buffer, delimiter);

	// add each string token to the queue
	printf("=> First enqueuing pass\n");
	while (token != NULL) {
		enqueue(q, token);
		printf("Enqueued (%d): %s\n", q->rear-1, q->array[q->rear-1]);
		token = strtok(NULL, delimiter);
	}
	printf("\n");

	// dequeue all queue entries
	printf("=> Dequeuing all elements\n");
	while(!isEmpty(q)) {
		// printf("Dequeued (%d): %s\n", q->front-1, dequeue(q));
		printf("Dequeued (%d): ", q->front);
		printf("%s\n", dequeue(q));
	}
	printf("\n");

	// read file and tokenize string loaded from the file again
	fseek(file, 0, SEEK_SET);
	fread(buffer, sizeof(char), file_len, file);
	token = strtok(buffer, delimiter);

	// re-add each string token to the queue
	printf("=> Second enqueuing pass\n");
	while (token != NULL) {
		enqueue(q, token);
		printf("Enqueued (%d): %s\n", q->rear-1, q->array[q->rear-1]);
		token = strtok(NULL, delimiter);
	}
	printf("\n");

	// use queue functionality to print the contents of the queue
	printf("=> Printing queue\n");
	printQueue(q);
	printf("\n");

	// call clean to free up the memory used by the strings and the memeory used by the string pointers
	printf("=> Calling Queue cleanup\n");
	cleanup(q);
	printf("\n");

	// close and free all files and memory contents
	free(q);
	fclose(file);
	free(buffer);
	return 0;
}