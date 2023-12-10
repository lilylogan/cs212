// hashtable implemenation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "project3C_hashtable.h"

// hash function
unsigned int hash(const char *key) {
	unsigned int hash = 0;
	for (int i=0; key[i] != '\0'; i++) {
		hash = hash * 31 + key[i];
	}
	return hash % BUCKET_SIZE;
}

void initialize(HashTable *ht) {
	for (int i=0; i<BUCKET_SIZE; i++) {
		ht->bucket[i] = NULL;
	}

	ht->count = 0;
}

Node *creatNode(const char *key, int value) {
	Node *node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("Failed to allocate memory for new node\n");
		exit(EXIT_FAILURE);
	}
	node->key = strdup(key);
	node->value = value;
	node->next = NULL;
	return node;
}

void insert(HashTable *ht, const char *key, int value) {
	Node *newNode = creatNode(key, value);

	// get hash index
	unsigned int hashIndex = hash(key);

	if(ht->bucket[hashIndex] != NULL) {		
		Node *currentNode = ht->bucket[hashIndex];

		// get to the end of the linked list to insert new node
		while(currentNode->next != NULL) {
			currentNode = currentNode->next;
		}

		// insert new node to end of the linked list
		currentNode->next = newNode;
	}

	// if empty
	if(ht->bucket[hashIndex] == NULL) {
		ht->bucket[hashIndex] = newNode;
	}

	ht->count++;
}

void get(HashTable *ht, const char *key, int **results, int *count) {

	unsigned int keyHash = hash(key);

	if(ht->bucket[keyHash] != NULL) {
		*results = (int*)malloc(sizeof(int)*BUCKET_SIZE);
		Node *currentNode = ht->bucket[keyHash];

		while(currentNode != NULL) {
			if (strcmp(currentNode->key, key) == 0) {
				(*results)[*count] = currentNode->value;
				(*count)++;
			}
			currentNode = currentNode->next;
		}
	}
}

void freeHashTable(HashTable *ht) {
	for(int i=0; i<BUCKET_SIZE; i++) {

		if(ht->bucket[i] != NULL) {
			Node *currentNode = ht->bucket[i];

			while(currentNode->next != NULL) {
				Node *tempNode = currentNode->next;

				free(currentNode->key);
				free(currentNode);

				currentNode = tempNode;
			}
			
			free(currentNode->key);
			free(currentNode);
		}
	}
	free(ht);
}

float calculateLoadFactor(HashTable *ht) {

	return (ht->count / BUCKET_SIZE) + ((float)(ht->count % BUCKET_SIZE)/BUCKET_SIZE);
}