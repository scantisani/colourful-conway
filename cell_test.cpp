#define BOOST_TEST_MODULE cell

#include "boost/test/included/unit_test.hpp"
#include "cell.h"

BOOST_AUTO_TEST_CASE(constructor_test) {
	Cell cell(1, 2);
	BOOST_CHECK_EQUAL(cell.x, 1);
	BOOST_CHECK_EQUAL(cell.y, 2);
}