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


tests: cell_test game_test gui_test

gui_test: gui_test.o gui.o game.o cell.o
	$(CC) gui_test.o gui.o game.o cell.o $(LINKER_FLAGS) -o gui_test

game_test: game_test.o game.o cell.o
	$(CC) game_test.o game.o cell.o $(LINKER_FLAGS) -o game_test

cell_test: cell_test.o cell.o
	$(CC) cell_test.o cell.o $(LINKER_FLAGS) -o cell_test

gui_test.o: gui_test.cpp gui_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) gui_test.cpp

game_test.o: game_test.cpp game_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) game_test.cpp

cell_test.o: cell_test.cpp cell_test_headers.h.gch
	$(CC) -c $(COMPILER_FLAGS) cell_test.cpp

gui_test_headers.h.gch: gui_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) gui_test_headers.h

game_test_headers.h.gch: game_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) game_test_headers.h

cell_test_headers.h.gch: cell_test_headers.h
	$(CC) -c $(COMPILER_FLAGS) cell_test_headers.h


clean:
	rm *.o conway *_test
