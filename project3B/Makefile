CFLAGS=-W -Wall
CC=gcc
OBJECTS=project3B_deque.o project3B.o

PROGRAMS=project3B

all: $(PROGRAMS)

project3B: $(OBJECTS)
	$(CC) $(CFLAGS) -o project3B $(OBJECTS)

project3B.o: project3B.c project3B_deque.h
project3B_deque.o: project3B_deque.c project3B_deque.h