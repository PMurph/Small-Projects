#include "Game.h"

#include <iostream>

static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;
static const int MILLISEC_BETWEEN_MOVE = 500;

Game::Game(void)
{
	timeSinceLastMove = -1;

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
	gameCollisionResolver = new CollisionResolver;
	gameGrid->clearGrid();

	gameRunning = true;

	generateNewSnake();
	generateFood();

	timeSinceLastMove = GetTickCount();
}

void Game::updateGame(int value)
{
	int currTime;

	if( timeSinceLastMove == -1 )
	{
		timeSinceLastMove = GetTickCount();
	}

	currTime = GetTickCount();

	if( currTime - timeSinceLastMove >= MILLISEC_BETWEEN_MOVE && gameRunning )
	{
		updateSnakeDirection();
		moveSnake();

		timeSinceLastMove = GetTickCount();
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

void Game::gameOver()
{
	gameRunning = false;
	gameGrid->clearGrid();
	gameGrid->setGameOverMessage();
	gameCollisionResolver->clearCollisions();

	delete gameCollisionResolver;
	delete snake;

	gameCollisionResolver = NULL;
	snake = NULL;
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
			newSnake = Snake::createSnake( middleRow, middleColumn - 1, headContainer, middleContainer, tailContainer, this );

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
				snake->updateSnake(newContainer, gameCollisionResolver);
			}
			else
			{
				gameOver();
			}
		}
	}
}

void Game::updateSnakeDirection()
{
	snake->setDirection( nextDirection );
}

void Game::generateFood()
{
	GridCell * foodCell = gameGrid->getNonSnakeCell();
	Food * newFood = NULL;

	assert( foodCell != NULL && foodCell->getState() == EMPTY );

	if( foodCell != NULL && foodCell->getState() == EMPTY )
	{
		newFood = generateRandomFoodType();

		assert( newFood != NULL );

		if( newFood != NULL )
		{
			foodCell->setOccupant(newFood);
		}
	}
}

Food * Game::generateRandomFoodType() const
{
	Food * newFood = new RegularFood();

	return newFood;
}