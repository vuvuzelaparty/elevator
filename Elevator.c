#include <unistd.h>
#include "Elevator.h"

Elevator *elevator = NULL;
Queue *queue = NULL;

int main(void) {
	init();
	printf("forever elevator!\n\n");
	addFloor(queue, 3, elevator->currentFloor);
	addFloor(queue, 6, elevator->currentFloor);
	addFloor(queue, 9, elevator->currentFloor);
	addFloor(queue, 12, elevator->currentFloor);
	addFloor(queue, 15, elevator->currentFloor);
	addFloor(queue, 18, elevator->currentFloor);
	for (int i = 0; i < 15; i++)
		tick();
	/*
	while (1) {
		tick();
		sleep(2);
	}
	*/
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
			if (queue->head->value > elevator->currentFloor)
				elevator->state = STOPPED_DESTINED_UP;
			else
				elevator->state = isEmpty(queue) ? IDLE : STOPPED_DESTINED_DOWN;
			break;
		case GOING_DOWN :
			printf("GOING DOWN\n");
			elevator->currentFloor = queue->head->value;
			removeFloor(queue, elevator->currentFloor);
			if (queue->head->value < elevator->currentFloor)
				elevator->state = STOPPED_DESTINED_DOWN;
			else
				elevator->state = isEmpty(queue) ? IDLE : STOPPED_DESTINED_UP;
			break;
		case STOPPED_DESTINED_UP :
			printf("STOPPED DESTINED UP\nCurrent floor: %d\n", elevator->currentFloor);
			//listenForButtonPress();
			elevator->state = GOING_UP;
			break;
		case STOPPED_DESTINED_DOWN :
			printf("STOPPED DESTINED DOWN\nCurrent floor: %d\n", elevator->currentFloor);
			//listenForButtonPress();
			elevator->state = GOING_DOWN;
			break;
		case IDLE :
			printf("IDLE\nCurrent floor: %d\n", elevator->currentFloor);
			//listenForButtonPress();
			if (queue->head->value > elevator->currentFloor)
				elevator->state = GOING_UP;
			else if (queue->head->value < elevator->currentFloor)
				elevator->state = GOING_DOWN;
			break;
	}
}

int createButtonPress(void) {
	int x = rand() % TOP_FLOOR + 1;
	printf("button pressed: %d\n", x);
	return x;
}
