#ifndef _ELEVATOR_QUEUE_H // what are these? I see these everywhere in other projects
#define _ELEVATOR_QUEUE_H
#include <stdio.h>

#define UP 1
#define DOWN 0

typedef struct node_st {
	int value;
	struct node_st *next;
} Node;

typedef struct queue_st {
	int direction;
	int size;
	Node *head;
} Queue;

void addFloor(Queue *, int, int);
void removeFloor(Queue *, int);
void printQueue(Queue *);
int isEmpty(Queue *);
#endif
