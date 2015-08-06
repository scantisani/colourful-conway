CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: tests

tests: cell_test game_test gui_test

gui_test: gui_test.o ../gui.o ../game.o ../cell.o
	$(CC) gui_test.o ../gui.o ../game.o ../cell.o $(LINKER_FLAGS) -o gui_test

game_test: game_test.o ../game.o ../cell.o
	$(CC) game_test.o ../game.o ../cell.o $(LINKER_FLAGS) -o game_test

cell_test: cell_test.o ../cell.o
	$(CC) cell_test.o ../cell.o $(LINKER_FLAGS) -o cell_test

%_test.o: %_test.cpp %_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) $<

%_test_headers.h.gch: %_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) $<

../%.o: ../%.cpp
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

clean:
	rm *.o *_test
