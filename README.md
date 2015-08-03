# colourful-conway
Conway's Game of Life with 'genetic' cell colour variation.

Requirements:
- `g++` (or `clang++`--modify CC in the Makefile)
- SDL2
- `make`
- Boost.Test (if you want to run tests)

On Ubuntu and Ubuntu variants:
- `sudo apt-get install g++ libsdl2-dev make` should install the necessary prerequisites
	- `sudo apt-get install g++ libsdl2-dev make libboost1.55-dev` if you want to run tests
- Run `make` from the root directory
- Type `./conway` to start the program

Currently the project's only been tested on Ubuntu 14.04 LTS.

Press `space` to start or stop the simulation.
Provided the simulation is stopped:
- left-click will fill or clear a cell
- `n` will advance the simulation one step
- `r` will clear the grid