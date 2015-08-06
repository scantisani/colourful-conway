OUT = conway

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: conway

conway: main.o gui.o game.o cell.o
	$(CC) main.o gui.o game.o cell.o $(LINKER_FLAGS) -o $(OUT)

main.o: main.cpp
	$(CC) -c $(COMPILER_FLAGS) main.cpp

gui.o: gui.cpp
	$(CC) -c $(COMPILER_FLAGS) gui.cpp

game.o: game.cpp
	$(CC) -c $(COMPILER_FLAGS) game.cpp

cell.o: cell.cpp
	$(CC) -c $(COMPILER_FLAGS) cell.cpp

clean:
	rm *.o conway
