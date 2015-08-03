#include "game_test_headers.h"

struct gameFixture {
	gameFixture() : game(5, 5) { }
	~gameFixture() { }

	Game game;
};

BOOST_FIXTURE_TEST_SUITE(gameSuite, gameFixture);

BOOST_AUTO_TEST_CASE(gameConstructor_createsGridOfDeadCells) {
	int numberOfLiveCells = game.getLiveCells().size();
	BOOST_CHECK_EQUAL(numberOfLiveCells, 0);
}

BOOST_AUTO_TEST_CASE(gameToggleCell_killsAndRevivesCell) {
	int liveCells = game.getLiveCells().size();

	game.toggleCell(1, 1);
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), liveCells + 1);
	game.toggleCell(1, 1);
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), liveCells);
}

BOOST_AUTO_TEST_CASE(gameReset_killsAllCells) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			game.toggleCell(i, j);
	}

	game.reset();
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), 0);
}

BOOST_AUTO_TEST_CASE(gameGetLiveCells_passesCorrectCellObjects) {
	game.toggleCell(1, 2);
	game.toggleCell(2, 4);
	vector<Cell> liveCells = game.getLiveCells();

	BOOST_CHECK_EQUAL(liveCells[0].x, 1);
	BOOST_CHECK_EQUAL(liveCells[0].y, 2);
	BOOST_CHECK_EQUAL(liveCells[1].x, 2);
	BOOST_CHECK_EQUAL(liveCells[1].y, 4);
}

BOOST_AUTO_TEST_SUITE_END();