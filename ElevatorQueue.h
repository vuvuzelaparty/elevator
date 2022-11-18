#ifndef ELEVATOR_QUEUE_H
#define ELEVATOR_QUEUE_H
#include <stdio.h>

#define TOP_FLOOR 20
#define FIRST_FLOOR 1

typedef struct node_st {
	int value;
	struct node_st *next;
} Node;

typedef struct queue_st {
	int size;
	Node *head;
} Queue;

Node *createNewNode(int value, Node *next);
void addFloor(Queue *queue, int floor, int currentFloor);
void removeFloor(Queue *queue, int floor);
void printQueue(Queue *queue);
int isEmpty(Queue *queue);
#endif
