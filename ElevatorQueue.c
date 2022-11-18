#include <stdlib.h>
#include "ElevatorQueue.h"

Node *createNewNode(int value, Node *next){
	Node *n = malloc(sizeof(Node));
	n->value = value;
	n->next = next;
	return n;
}

void addFloor(Queue *queue, int floorToAdd, int currentFloor) {
	if (floorToAdd < FIRST_FLOOR || floorToAdd > TOP_FLOOR || floorToAdd == currentFloor)
		return;
	if (isEmpty(queue)) { // empty list, first node
		queue->head = createNewNode(floorToAdd, NULL);
		queue->size++;
		return;
	}
	Node **linkToCurrent = &(queue->head);
	for (Node *current = *linkToCurrent; current != NULL; current = *linkToCurrent) {
		if (current->value == floorToAdd) // make sure we don't put the same floor twice
			return;
		else if ((floorToAdd > currentFloor && floorToAdd > current->value) || // traverse linked list
				 (floorToAdd < currentFloor && floorToAdd < current->value))
			linkToCurrent = &(current->next);
		else { // add new node inside list
			*linkToCurrent = createNewNode(floorToAdd, current);
			queue->size++;
			return;
		}
	}
	*linkToCurrent = createNewNode(floorToAdd, NULL); // append new node at the end of list
	queue->size++;
}

void removeFloor(Queue *queue, int floor) {
	for (Node **linkToCurrent = &(queue->head), *current = *linkToCurrent;
		 current != NULL; current = *linkToCurrent) {
		if (current->value == floor) {
			*linkToCurrent = current->next;
			free(current);
			queue->size--;
			return;
		} else
			linkToCurrent = &(current->next);
	}
}

void printQueue(Queue *queue) {
	printf("Queue:\n");
	for (Node *current = queue->head; current != NULL; current = current->next)
		printf("%d\n", current->value);
}

int isEmpty(Queue *queue) {
	return queue->size == 0;
}
