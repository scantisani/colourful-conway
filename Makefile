# OBJ = gui.cpp
OUT = conway

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: conway

conway: gui.o game.o
	$(CC) gui.o game.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT)

game.o: game.cpp
	$(CC) -c $(COMPILER_FLAGS) game.cpp

gui.o: gui.cpp
	$(CC) -c $(COMPILER_FLAGS) gui.cpp

clean:
	rm *.o conway
