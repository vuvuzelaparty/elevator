#include <stdlib.h>
#include "ElevatorQueue.h"

Node *createNewNode(int value, Node *next){
    Node *n = malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

void addFloor(Queue *queue, int floor) {
    if (floor < FIRST_FLOOR || floor > TOP_FLOOR)
        return;
    if (isEmpty(queue)) { // empty list, first node
        queue->head = createNewNode(floor, NULL);
        queue->size++;
        return;
    }
    Node *current = queue->head;
    int isNewHead;
    // make sure that we don't put the same floor more than once
    for (Node *check = current; check != NULL; check = check->next)
        if (check->value == floor)
            return;
    // find the spot in the queue where the new floor needs to go
    if (queue->direction == UP) {
        isNewHead = floor < queue->head->value;
        if (!isNewHead)
            for (; current->next != NULL && current->next->value < floor; current = current->next);
    } else if (queue->direction == DOWN) {
        isNewHead = floor > queue->head->value;
        if (!isNewHead)
            for (; current->next != NULL && current->next->value > floor; current = current->next);
    }
    if (isNewHead)
        queue->head = createNewNode(floor, current);
    else
        current->next = createNewNode(floor, current->next);
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
    if (queue->direction == UP)
        printf("Up queue:\n");
    else if (queue->direction == DOWN)
        printf("Down queue:\n");
    for (Node *current = queue->head; current != NULL; current = current->next)
        printf("%d\n", current->value);
}

int isEmpty(Queue *queue) {
    return queue->size == 0;
}
