#include <stdlib.h>
#include "ElevatorQueue.h"

void addFloor(Queue *queue, int floor, int direction) {
	Node *current = queue->head;
	int newHead = 0;
	if (!isEmpty(queue)) {
		// make sure that we don't put the same floor more than once
		for (Node *check = current; check != NULL; check = check->next)
			if (check->value == floor)
				return;
		if (direction == UP) {
			if (floor < queue->head->value)
				newHead = 1;
			else
				while (current->next != NULL && current->next->value < floor)
					current = current->next;
		}
		else if (direction == DOWN) {
			if (floor > queue->head->value)
				newHead = 1;
			else
				while (current->next != NULL && current->next->value > floor)
					current = current->next;
		}
	}
	Node *n = (Node *) malloc(sizeof(Node));
	n->value = floor;
	if (!isEmpty(queue)) {
		if (newHead) {
			n->next = current;
			queue->head = n;
		}
		else {
			Node *tmp = current->next;
			current->next = n;
			n->next = tmp;
		}
	}
	else {
		queue->head = n;
		n->next = NULL;
	}
	queue->size++;
}

void removeFloor(Queue *queue, int floor) {
	if (!isEmpty(queue)) {
		Node *current = queue->head;
		if (current->value == floor) { // first node
			queue->head = current->next;
			free(current);
			queue->size--;
			return;
		} else { // not first node
			current = current->next;
			for (Node *prev = queue->head; current != NULL; prev->next = current, current = current->next) {
				if (current->value == floor) {
					prev->next = current->next;
					free(current);
					queue->size--;
					return;
				}
			}
		}
	}
}

void printQueue(Queue *queue) {
	if (!isEmpty(queue)) {
		Node *current = queue->head;
		while (current != NULL) {
			printf("%d\n", current->value);
			current = current->next;
		}
	}
}

int isEmpty(Queue *queue) {
	return queue->size == 0;
}
