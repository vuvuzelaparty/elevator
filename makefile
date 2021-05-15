EXE = Elevator
SRC = Elevator.c ElevatorQueue.c
CC = gcc
RM = rm -f

.PHONY : clean

all :
	$(CC) $(SRC) -o $(EXE)

clean :
	$(RM) $(EXE)
