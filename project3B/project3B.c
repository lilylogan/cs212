// deque main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "project3B_deque.h"

void printLong (void *data) {
	long num = *(long *)data;
	printf("%ld", num);
}

void printString(void *data) {
	char *string = (char*)data;
	printf("%s", string);
}

bool isLong(const char *str) {
	char *ptr;
	strtol(str, &ptr, 10);
	if (ptr == str || *ptr != '\0') {
		return false;
	}
	return true;
}

int main() {

	// create a deque to contain long numbers
	Deque *longDeque = createDeque();
	

	// create a deque to contain C strings
	Deque *stringDeque = createDeque();

	// initilize variables for input and placement of nodes in each deque
	bool longFront = true;
	bool stringFront = true;
	char *input = (char*)malloc(sizeof(char)*MAX_STR_LEN);

	do {
		// prompt user
		printf("Please enter an integer or a string (empty to exit): \n");

		// get "input"
		fgets(input, sizeof(char)*MAX_STR_LEN, stdin);

		// if there is input, not just end of line
		if (input[0] != '\n') {
			if (input[strlen(input)-1] == '\n')
				input[strlen(input)-1] = '\0';

			// differentiate between number and string			
			if (isLong(input)) {
				// alternate adding to front first, then back for integer

				long *longData = (long*)malloc(sizeof(long));
				*longData = strtol(input, NULL, 10);

				printf("You entered the number: %ld\n", *longData);
				if (longFront) {
					insertFront(longDeque, longData, sizeof(long));
				}
				else {
					insertBack(longDeque, longData, sizeof(long));
				}
				longFront = !longFront;
				free(longData);
			}
			
			if (!isLong(input)) {
				// alternate adding to the front first, then back for string
				printf("You entered the string: \"%s\"\n", input);
				if (stringFront) {
					insertFront(stringDeque, input, sizeof(char)*MAX_STR_LEN);
				}
				else {
					insertBack(stringDeque, input, sizeof(char)*MAX_STR_LEN);
				}
				stringFront = !stringFront;
			}
		}
		else {
			longFront = !longFront;
			stringFront = !stringFront;
			break;
		}
	} while(1);


	// print deques
	printf("\nPrinting string deque\n");
	printDeque(stringDeque, printString);
	printf("\n");

	printf("\nPrinting long deque\n");
	printDeque(longDeque, printLong);
	printf("\n");



	// remove string deque nodes, alternating from back to front?
	printf("\nRemoving string deque data using count\n");
	while (stringDeque->front != NULL) {
		char *removedString = (char*)malloc(sizeof(char)*MAX_STR_LEN);
		if (stringFront) {
			removeFront(stringDeque, removedString, sizeof(char)*MAX_STR_LEN);
			printf("Removing %s\n", removedString);
		}
		else {
			removeBack(stringDeque, removedString, sizeof(char)*MAX_STR_LEN);
			printf("Removing %s\n", removedString);
		}
		stringFront = !stringFront;
		free(removedString);
	}

	// remove long deque nodes alternating from front to back
	printf("\nRemoving long deque data using count\n");
	while(longDeque->front != NULL) {
		long *removedLongData = (long*)malloc(sizeof(long));
		if (longFront) {
			removeFront(longDeque, removedLongData, sizeof(long));
			printf("Removing %ld\n", *removedLongData);
		}
		else {
			removeBack(longDeque, removedLongData, sizeof(long));
			printf("Removing %ld\n", *removedLongData);
		}
		longFront = !longFront;
		free(removedLongData);
	}

	// free deques and input
	free(longDeque);
	free(stringDeque);
	free(input);

	return 0;
}