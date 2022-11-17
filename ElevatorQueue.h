#ifndef ELEVATOR_QUEUE_H
#define ELEVATOR_QUEUE_H
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

void addFloor(Queue *queue, int floor, int currentFloor);
void removeFloor(Queue *queue, int floor);
void printQueue(Queue *queue);
int isEmpty(Queue *queue);
#endif
