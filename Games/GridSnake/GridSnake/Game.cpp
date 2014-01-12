#include "Game.h"

#include <iostream>

static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;
static const int MILLISEC_BETWEEN_MOVE = 1000;

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
	generateNewSnake();
}

void Game::updateGame(int value)
{
	int currTime;

	if( prevTime == -1 )
	{
		prevTime = GetTickCount();
	}

	currTime = GetTickCount();

	std::cout << "Current time: " << currTime << std::endl << "Previous time: " << prevTime << std::endl << "Difference: " << (currTime - prevTime) << std::endl;

	if( currTime - prevTime >= MILLISEC_BETWEEN_MOVE )
	{
		moveSnake();

		prevTime = GetTickCount();
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

			snake->updateSnake(newContainer);
		}
	}
}
