#include "Game.h"

static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;

Game::Game(void)
{
	initGame();
}

Game::~Game(void)
{
	delete gameDrawer;
	delete gameGrid;
}

void Game::initGame()
{
	gameDrawer = new ListDrawer();
	gameGrid = new Grid(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	
	gameDrawer->registerDrawable(gameGrid);
}

void Game::drawGame() const
{
	gameDrawer->drawAll();
}
