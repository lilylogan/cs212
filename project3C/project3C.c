// hashtable main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project3C_hashtable.h"

int main() {

	// create an instance of the hash table
	HashTable *ht = (HashTable*)malloc(sizeof(HashTable));

	if(ht == NULL) {
		printf("Erorr allocating memory for hash table\n");
		exit(0);
	}

	// initialize hash table
	initialize(ht);

	// prompt user for a filename containing text on individual lines
	do {
		char line[MAX_STRING_LEN];
		char filename[MAX_STRING_LEN];
		printf("Enter the filename (or leave blank to quit): ");

		// get file name from standard input
		fgets(filename, sizeof(char)*MAX_STRING_LEN, stdin);

		// check that we got something, if blank then quit program
		if (filename[0] == '\n') {
			printf("No file entered, exiting program...\n");
			freeHashTable(ht);
			exit(0);
		}

		// if there is a filename, add end of line character
		filename[strlen(filename)-1] = '\0';

		// open file (if possible)
		FILE *file = fopen(filename, "r");

		// could not open file properly, re-prompt
		if (file == NULL) {
			printf("Failed to open file \'%s\'. Please try again.\n", filename);
		}

		// got valid filename and was able to open! can now continue and read line by line
		else {
			// print a status message
			printf("Tokenizing file \'%s\' and building hash bucket...", filename);

			// initialize line number
			int linenumber = 1;

			// read the file line by line
			do {
				fgets(line, sizeof(char)*MAX_STRING_LEN, file);

				// add end of line character
				if (line[strlen(line)-1] == '\n')
					line[strlen(line)-1] = '\0';

				// tokenize the words on each line into separte words
				char *token = strtok(line, " ");

				while (token != NULL) {

					// convert to lowercase
					int tokenlen = strlen(token);
					for (int i=0; i < tokenlen; i++) {
						token[i] = tolower(token[i]);
					}

					// use the word as the key and the linenumber as the value to insert into hashtable
					insert(ht, token, linenumber);
					token = strtok(NULL, " ");
				}
				// increment linenumber and go to next line
				linenumber++;
			
			} while(!feof(file));

			// close file and continue
			fclose(file);
			break;
		}

	} while(1);

	// print tokenizing/hash bucket build completion status, append to the earlier tokenizing status message
	printf("done.\n");

	// display the calculated load factor
	printf("Load factor: %.2f\n", calculateLoadFactor(ht));

	char *searchword = (char*)malloc(sizeof(char)*MAX_STRING_LEN+1);
	do {
		// prompt the user with message for a search word
		printf("Enter a word to search (or leave blank to quit): ");


		fgets(searchword, sizeof(char)*MAX_STRING_LEN, stdin);

		// if no search term is entered, terminate program
		if (searchword[0] == '\n') {
			// free any memory used to get search results
			free(searchword);
			break;
		}


		// find string length and add end of line char
		int searchwordLen = strlen(searchword);
		searchword[searchwordLen-1] = '\0';

		searchwordLen--;

		// convert to lowercase
		for (int i=0; i < searchwordLen; i++) {
			searchword[i] = tolower(searchword[i]);
		}


		// if word (coverted to lowercase) is found, display a message that includes all associated line numbers
		// use get to get the line numbers (if there are any)
		int *results = NULL;
		int count = 0;
		get(ht, searchword, &results, &count);
		
		// if word is not found, display message and re-prompt user for a search term
		if(count == 0) {
			printf("Word \'%s\' not found.\n", searchword);
		}

		if(count != 0) {
			// if we found the word
			printf("Word \'%s\' found at line number(s): ", searchword);
			for(int i=0; i <count; i++) {
				printf("%d ", results[i]);
			}
			printf("\n");
		}
		free(results);

	} while(1);

	// free any memory used with hash table
	freeHashTable(ht);

	exit(0);
}