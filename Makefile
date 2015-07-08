OBJ = gui.cpp
OUT = gui

CC = g++
COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

all:
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT)
