#include "Game.h"

#include <iostream>

static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;
static const int MILLISEC_BETWEEN_MOVE = 500;

Game::Game(void)
{
	prevTime = -1;

	initGame();
	newGame();
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

void Game::newGame()
{
	gameGrid->clearGrid();

	gameRunning = true;

	generateNewSnake();

	prevTime = GetTickCount();
}

void Game::updateGame(int value)
{
	int currTime;

	if( prevTime == -1 )
	{
		prevTime = GetTickCount();
	}

	currTime = GetTickCount();

	if( currTime - prevTime >= MILLISEC_BETWEEN_MOVE && gameRunning )
	{
		updateSnakeDirection();
		moveSnake();

		prevTime = GetTickCount();
	}
}

void Game::handleInput(const unsigned char key)
{
	switch( key )
	{
	case ' ':
		if( !gameRunning )
			newGame();
		break;
	case 'w':
		if( snake->getDirection() == LEFT || snake->getDirection() == RIGHT )
			nextDirection = UP;
		break;
	case 'a':
		if( snake->getDirection() == UP || snake->getDirection() == DOWN )
			nextDirection = LEFT;
		break;
	case 'd':
		if( snake->getDirection() == UP || snake->getDirection() == DOWN )
			nextDirection = RIGHT;
		break;
	case 's':
		if( snake->getDirection() == LEFT || snake->getDirection() == RIGHT )
			nextDirection = DOWN;
		break;
	}
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
	Snake * newSnake = NULL;
	SnakeBodyPartContainer * headContainer, * middleContainer, * tailContainer;
	int middleRow, middleColumn;

	middleRow = static_cast<int>( floor( static_cast<float>( gameGrid->getGridHeight() ) / 2.0f ) );
	middleColumn = static_cast<int>( floor( static_cast<float>( gameGrid->getGridWidth() ) / 2.0f ) );

	assert( middleRow > 0 && middleRow < gameGrid->getGridHeight() - 1 && middleColumn > 1 && middleColumn < gameGrid->getGridWidth() - 2 );

	if( middleRow > 0 && middleRow < gameGrid->getGridHeight() -1 && middleColumn > 1 && middleColumn < gameGrid->getGridWidth() - 2 )
	{
		headContainer = gameGrid->getBodyPartContainer(middleRow, middleColumn - 1);
		middleContainer = gameGrid->getBodyPartContainer(middleRow, middleColumn);
		tailContainer = gameGrid->getBodyPartContainer(middleRow, middleColumn + 1);

		assert( headContainer != NULL && middleContainer != NULL && tailContainer != NULL );

		if( headContainer != NULL && middleContainer != NULL && tailContainer != NULL )
		{
			newSnake = Snake::createSnake( middleRow, middleColumn - 1, headContainer, middleContainer, tailContainer );

			assert(newSnake != NULL);

			if( newSnake != NULL )
			{
				snake = newSnake;
				nextDirection = LEFT;
			}
		}
	}
}

void Game::moveSnake()
{
	SnakeDirection currDirection = UP;
	SnakeBodyPartContainer * newContainer = NULL;
	int row = snake->getHeadRow(), col = snake->getHeadCol();

	assert( row >= 0 && row < gameGrid->getGridHeight() && col >= 0 && col < gameGrid->getGridWidth() );

	if( row >= 0 && row < gameGrid->getGridHeight() && col >= 0 && col < gameGrid->getGridHeight() )
	{
		currDirection = snake->getDirection();

		switch( currDirection )
		{
		case UP:
			row += 1;
			break;
		case DOWN:
			row -= 1;
			break;
		case LEFT:
			col -= 1;
			break;
		case RIGHT:
			col += 1;
			break;
		}

		assert( row >= 0 && row < gameGrid->getGridHeight() && col >= 0 && col < gameGrid->getGridWidth() );

		if( row >= 0 && row < gameGrid->getGridHeight() && col >= 0 && col < gameGrid->getGridWidth() )
		{
			newContainer = gameGrid->getBodyPartContainer(row, col);

			if( newContainer->canContainSnakeBodyPart() )
			{
				snake->updateSnake(newContainer);
			}
			else
			{
				gameOver();
			}
		}
	}
}

void Game::gameOver()
{
	gameRunning = false;
	gameGrid->clearGrid();
	gameGrid->setGameOverMessage();
}

void Game::updateSnakeDirection()
{
	snake->setDirection( nextDirection );
}