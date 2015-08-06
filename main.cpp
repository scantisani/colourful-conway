#include <iostream>
using std::cout; using std::endl;
using std::cerr;

#include <stdexcept>
using std::runtime_error;

#include "gui.h"

int main(int argc, char const * argv[]) {
	try {
		Gui gui;
		gui.loop();
	} catch (runtime_error e) {
		cerr << e.what() << endl;
	}

	return 0;
}