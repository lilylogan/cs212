// header file for hashtable

#ifndef PROJECT3C_HASHTABLE_H
#define PROJECT3C_HASHTABLE_H

#define BUCKET_SIZE 100
#define MAX_STRING_LEN 256


// hash table Node
typedef struct Node {
	char *key;
	int value;
	struct Node *next;
} Node;

// HashTable (bucket)
typedef struct {
	Node *bucket[BUCKET_SIZE];
	int count; // number of elements (linked list nodes) in the hash table
} HashTable;


// hashtable function prototypes
unsigned int hash(const char *key);

void initialize(HashTable *ht);

Node *creatNode(const char *key, int value);

void insert(HashTable *ht, const char *key, int value);

void get(HashTable *ht, const char *key, int **results, int *count);

void freeHashTable(HashTable *ht);

float calculateLoadFactor(HashTable *ht);
 
#endif //PROJECT3C_HASHTALBE_H