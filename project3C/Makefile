CFLAGS=-W -Wall
CC=gcc
OBJECTS=project3C.o project3C_hashtable.o

PROGRAMS=project3C

all: $(PROGRAMS)

project3C: $(OBJECTS)
	$(CC) $(CFLAGS) -o project3C $(OBJECTS)	

project3C.o: project3C.c project3C_hashtable.h
project3C_hashtable.o: project3C_hashtable.c project3C_hashtable.h