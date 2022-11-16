#include <stdlib.h>
#include "ElevatorQueue.h"

void addFloor(Queue *queue, int floor) {
	Node *current = queue->head;
	int isNewHead;
	if (!isEmpty(queue)) {
		// make sure that we don't put the same floor more than once
		for (Node *check = current; check != NULL; check = check->next)
			if (check->value == floor)
				return;
		if (queue->direction == UP) {
			isNewHead = floor < queue->head->value;
			if (!isNewHead)
				for (; current->next != NULL && current->next->value < floor; current = current->next);
		} else if (queue->direction == DOWN) {
			isNewHead = floor > queue->head->value;
			if (!isNewHead)
				for (; current->next != NULL && current->next->value > floor; current = current->next);
		}
	}
	Node *n = malloc(sizeof(Node));
	n->value = floor;
	if (isEmpty(queue))
		queue->head = n;
	else {
		if (isNewHead) {
			n->next = current;
			queue->head = n;
		} else {
			n->next = current->next;
			current->next = n;
		}
	}
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
	if (isEmpty(queue))
		return;
	for (Node *current = queue->head; current != NULL; current = current->next)
		printf("%d\n", current->value);
}

int isEmpty(Queue *queue) {
	return queue->size == 0;
}
