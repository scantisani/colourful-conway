#include "gui_test_headers.h"

struct guiFixture {
	guiFixture() { }
	~guiFixture() { }

	Gui gui;
};

BOOST_FIXTURE_TEST_SUITE(guiSuite, guiFixture);

BOOST_AUTO_TEST_SUITE_END();