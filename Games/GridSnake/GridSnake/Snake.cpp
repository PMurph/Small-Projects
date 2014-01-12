#include "Snake.h"


Snake::~Snake(void)
{
}

const SnakeDirection Snake::getDirection() const
{
	return currDirection;
}

void Snake::setDirection(SnakeDirection newDirection)
{
	switch( currDirection )
	{
	case UP:
	case DOWN:
		if( newDirection == LEFT || newDirection == RIGHT )
			currDirection = newDirection;
		break;
	case LEFT:
	case RIGHT:
		if( newDirection == UP || newDirection == DOWN )
			currDirection = newDirection;
		break;
	}
}

Snake * Snake::createSnake(const int row, const int column, SnakeBodyPartContainer * headContainer, SnakeBodyPartContainer * middleContainer, SnakeBodyPartContainer * tailContainer)
{
	Snake * newSnake = NULL;
	SnakeBodyPart * head, * middle, * tail;

	assert( headContainer != NULL && middleContainer != NULL && tailContainer != NULL );

	if( headContainer != NULL && middleContainer != NULL && tailContainer != NULL )
	{
		tail = new SnakeBodyPart( NULL, false );
		middle = new SnakeBodyPart( tail, false );
		head = new SnakeBodyPart( middle, true );

		newSnake = new Snake();

		assert( tail != NULL && middle != NULL && head != NULL && newSnake != NULL );

		if( tail != NULL && middle != NULL && head != NULL && newSnake != NULL)
		{
			headContainer->addBodyPartToContainer( head );
			middleContainer->addBodyPartToContainer( middle );
			tailContainer->addBodyPartToContainer( tail );

			newSnake->snakeContainers.push_back(headContainer);
			newSnake->snakeContainers.push_back(middleContainer);
			newSnake->snakeContainers.push_back(tailContainer);

			newSnake->headRow = row;
			newSnake->headCol = column;
			newSnake->numBodyParts = 3;
		}
	}

	return newSnake;
}

const int Snake::getHeadRow() const
{
	return headRow;
}

const int Snake::getHeadCol() const
{
	return headCol;
}

void Snake::updateSnake(SnakeBodyPartContainer * nextContainer)
{
	std::list<SnakeBodyPartContainer *> newBodyContainer;
	const SnakeBodyPart * nextPart = NULL;
	SnakeBodyPartContainer * currContainer = NULL, * prevContainer = NULL;
	int i;
	
	currContainer = nextContainer;

	for( i = 0; i < numBodyParts; i++ )
	{
		prevContainer = currContainer;

		currContainer = snakeContainers.front();
		snakeContainers.pop_front();

		assert( currContainer != NULL );

		nextPart = currContainer->getBodyPartInContainer();

		prevContainer->clearContainer();
		prevContainer->addBodyPartToContainer( nextPart );

		newBodyContainer.push_back( prevContainer );
	}

	currContainer->clearContainer();

	snakeContainers = newBodyContainer;

	updateSnakePosition();
}

/* ===============================
 * Private Methods
 * ===============================
 */

void Snake::updateSnakePosition()
{
	switch( currDirection )
	{
	case UP:
		headRow += 1;
		break;
	case DOWN:
		headRow -= 1;
		break;
	case RIGHT:
		headCol += 1;
		break;
	case LEFT:
		headCol -= 1;
		break;
	}
}