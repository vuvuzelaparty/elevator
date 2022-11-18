#include <unistd.h>
#include "Elevator.h"

Elevator *elevator = NULL;
Queue *queue = NULL;

int main(void) {
	init();
	printf("forever elevator!\n\n");
	while (1) {
		tick();
		sleep(2);
	}
	fini();
	return 0;
}

void init() {
	elevator = malloc(sizeof(elevator));
	elevator->currentFloor = FIRST_FLOOR;
	elevator->state = IDLE;
	queue = malloc(sizeof(Queue));
	queue->size = 0;
}

void fini(void) {
	free(elevator);
	free(queue);
}

void listenForButtonPress(void) {
	int presses = rand() % (TOP_FLOOR/6);
	for (int i = 0; i < presses; i++)
		buttonPress(createButtonPress());
}

void buttonPress(int floor) {
	addFloor(queue, floor, elevator->currentFloor);
}

void tick(void) {
	printf("\n");
	switch(elevator->state) {
		case GOING_UP :
			printf("GOING UP\n");
			elevator->currentFloor = queue->head->value;
			removeFloor(queue, elevator->currentFloor);
			if (!isEmpty(queue))
				elevator->state = queue->head->value > elevator->currentFloor ? STOPPED_DESTINED_UP : STOPPED_DESTINED_DOWN;
			else
				elevator->state = IDLE;
			break;
		case GOING_DOWN :
			printf("GOING DOWN\n");
			elevator->currentFloor = queue->head->value;
			removeFloor(queue, elevator->currentFloor);
			if (!isEmpty(queue))
				elevator->state = queue->head->value > elevator->currentFloor ? STOPPED_DESTINED_UP : STOPPED_DESTINED_DOWN;
			else
				elevator->state = IDLE;
			break;
		case STOPPED_DESTINED_UP :
			printf("STOPPED DESTINED UP\nCurrent floor: %d\n", elevator->currentFloor);
			listenForButtonPress();
			elevator->state = GOING_UP;
			printQueue(queue);
			break;
		case STOPPED_DESTINED_DOWN :
			printf("STOPPED DESTINED DOWN\nCurrent floor: %d\n", elevator->currentFloor);
			listenForButtonPress();
			elevator->state = GOING_DOWN;
			printQueue(queue);
			break;
		case IDLE :
			printf("IDLE\nCurrent floor: %d\n", elevator->currentFloor);
			listenForButtonPress();
			if (isEmpty(queue))
				break;
			if (queue->head->value > elevator->currentFloor)
				elevator->state = GOING_UP;
			else if (queue->head->value < elevator->currentFloor)
				elevator->state = GOING_DOWN;
			printQueue(queue);
			break;
	}
}

int createButtonPress(void) {
	int x = rand() % TOP_FLOOR + 1;
	printf("button pressed: %d\n", x);
	return x;
}
