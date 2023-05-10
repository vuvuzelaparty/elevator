#include <unistd.h>
#include "Elevator.h"

Elevator *elevator = NULL;
Queue *upQueue = NULL;
Queue *downQueue = NULL;

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

void init(void) {
    elevator = malloc(sizeof(elevator));
    elevator->currentFloor = FIRST_FLOOR;
    elevator->state = IDLE;
    upQueue = malloc(sizeof(Queue));
    upQueue->size = 0;
    upQueue->direction = UP;
    downQueue = malloc(sizeof(Queue));
    downQueue->size = 0;
    downQueue->direction = DOWN;
}

void fini(void) {
    free(elevator);
    free(upQueue);
    free(downQueue);
}

void listenForButtonPress(void) {
    int presses = rand() % (TOP_FLOOR/6);
    for (int i = 0; i < presses; i++)
        buttonPress(createButtonPress());
}

void buttonPress(int floor) {
    if (floor > elevator->currentFloor)
        addFloor(upQueue, floor);
    else if (floor < elevator->currentFloor)
        addFloor(downQueue, floor);
}

void tick(void) {
    printf("\n");
    switch(elevator->state) {
        case GOING_UP :
            printf("GOING UP\n");
            elevator->currentFloor = upQueue->head->value;
            removeFloor(upQueue, elevator->currentFloor);
            if (!isEmpty(upQueue))
                elevator->state = STOPPED_DESTINED_UP;
            else
                elevator->state = isEmpty(downQueue) ? IDLE : STOPPED_DESTINED_DOWN;
            break;
        case GOING_DOWN :
            printf("GOING DOWN\n");
            elevator->currentFloor = downQueue->head->value;
            removeFloor(downQueue, elevator->currentFloor);
            if (!isEmpty(downQueue))
                elevator->state = STOPPED_DESTINED_DOWN;
            else
                elevator->state = isEmpty(upQueue) ? IDLE : STOPPED_DESTINED_UP;
            break;
        case STOPPED_DESTINED_UP :
            printf("STOPPED DESTINED UP\nCurrent floor: %d\n", elevator->currentFloor);
            listenForButtonPress();
            elevator->state = GOING_UP;
            printQueue(upQueue);
            if (!isEmpty(downQueue))
                printQueue(downQueue);
            break;
        case STOPPED_DESTINED_DOWN :
            printf("STOPPED DESTINED DOWN\nCurrent floor: %d\n", elevator->currentFloor);
            listenForButtonPress();
            elevator->state = GOING_DOWN;
            printQueue(downQueue);
            if (!isEmpty(upQueue))
                printQueue(upQueue);
            break;
        case IDLE :
            printf("IDLE\nCurrent floor: %d\n", elevator->currentFloor);
            listenForButtonPress();
            if (!isEmpty(upQueue)) {
                elevator->state = GOING_UP;
                printQueue(upQueue);
            }
            else if (!isEmpty(downQueue)) {
                elevator->state = GOING_DOWN;
                printQueue(downQueue);
            }
            break;
    }
}

int createButtonPress(void) {
    int x = rand() % TOP_FLOOR + 1;
    printf("button pressed: %d\n", x);
    return x;
}
