#include "Game.h"

static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;

Game::Game(void)
{
	initGame();
}

Game::~Game(void)
{
	delete snake;
	delete gameDrawer;
	delete gameGrid;
}

void Game::drawGame() const
{
	gameDrawer->drawAll();
}

void Game::windowReshaped()
{
	gameGrid->calcGridCellSize();
}

/* ===============================
 * Private Methods
 * ===============================
 */

void Game::initGame()
{
	gameDrawer = new ListDrawer();
	gameGrid = new Grid(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	
	gameDrawer->registerDrawable(gameGrid);
}

void Game::generateNewSnake()
{
	/* TODO:	1. Generate 3 snake body parts
	 *			2. Connect the 2nd last to the first, and last to the 2nd last
	 *			3. Set last one to snake head
	 *			4. Determine gridCells that snake will be positioned at
	 *			5. Set gridCell's occupants to the newly generated snake body parts
	 */
}
