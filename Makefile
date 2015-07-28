OUT = conway

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: conway

conway: gui.o game.o cell.o
	$(CC) gui.o game.o cell.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT)

gui.o: gui.cpp
	$(CC) -c $(COMPILER_FLAGS) gui.cpp

game.o: game.cpp
	$(CC) -c $(COMPILER_FLAGS) game.cpp

cell.o: cell.cpp
	$(CC) -c $(COMPILER_FLAGS) cell.cpp

clean:
	rm *.o conway
