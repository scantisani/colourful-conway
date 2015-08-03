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


tests: cell_test game_test

cell_test: cell_test.o cell.o
	$(CC) cell_test.o cell.o $(LINKER_FLAGS) -o cell_test

game_test: game_test.o game.o cell.o
	$(CC) game_test.o game.o cell.o $(LINKER_FLAGS) -o game_test

cell_test.o: cell_test.cpp cell_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) cell_test.cpp

game_test.o: game_test.cpp game_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) game_test.cpp

game_test_headers.h.gch: game_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) game_test_headers.h

cell_test_headers.h.gch: cell_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) cell_test_headers.h


clean:
	rm *.o conway *_test
