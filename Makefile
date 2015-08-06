OUT = conway

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all: conway

conway: main.o gui.o game.o cell.o
	$(CC) main.o gui.o game.o cell.o $(LINKER_FLAGS) -o $(OUT)

%.o: %.cpp
	$(CC) -c $(COMPILER_FLAGS) $<

clean:
	rm *.o conway
