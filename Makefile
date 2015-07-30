OUT = conway

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: conway

conway: gui.o game.o cell.o
	$(CC) gui.o game.o cell.o $(LINKER_FLAGS) -o $(OUT)

gui.o: gui.cpp
	$(CC) -c $(COMPILER_FLAGS) gui.cpp

game.o: game.cpp
	$(CC) -c $(COMPILER_FLAGS) game.cpp

cell.o: cell.cpp
	$(CC) -c $(COMPILER_FLAGS) cell.cpp


cell_test: cell_test.o cell.o
	$(CC) cell_test.o cell.o $(LINKER_FLAGS) -o cell_test

cell_test.o: cell_test.cpp
	$(CC) -c $(COMPILER_FLAGS) cell_test.cpp

clean:
	rm *.o conway cell_test
