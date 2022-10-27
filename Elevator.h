#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdio.h>
#include <stdlib.h>
#include "ElevatorQueue.h"

#define TOP_FLOOR 20
#define FIRST_FLOOR 1

typedef enum state_et {
	IDLE = 0,
	GOING_UP,
	GOING_DOWN,
	STOPPED_DESTINED_UP,
	STOPPED_DESTINED_DOWN
} STATE;

typedef struct elevator_st {
	int currentFloor;
	STATE state;
} Elevator;

int createButtonPress(void);
void init(void);
void fini(void);
void listenForButtonPress(void);
void buttonPress(int floor);
void tick(void);
void printQueues(void);
#endif
