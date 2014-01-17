#pragma once

#include <list>

#include "GridCell.h"
#include "CollisionResolver.h"
#include "SnakeBodyPart.h"

class CollisionResolver;
class SnakeBodyPartContainer;
class SnakeBodyPart;

typedef enum SNAKE_DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
} SnakeDirection;

class Snake
{
private:
	std::list<SnakeBodyPartContainer *> snakeContainers;
	SnakeDirection currDirection;
	int headRow, headCol;
	int numBodyParts;

	void updateSnakePosition();

	Snake(void)
		:currDirection(LEFT) {};
public:
	~Snake(void);

	const SnakeDirection getDirection() const;
	const int getHeadRow() const;
	const int getHeadCol() const;
	
	void setDirection(SnakeDirection newDirection);
	void updateSnake(SnakeBodyPartContainer * nextContainer, CollisionResolver * collisionResolver);
	bool eatFood(GridCell * collisionCell, const SnakeBodyPart * collider);

	static Snake * createSnake(const int row, const int column, SnakeBodyPartContainer * headContainer, SnakeBodyPartContainer * middleContainer, SnakeBodyPartContainer * tailContainer);
};

