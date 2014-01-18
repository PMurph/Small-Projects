#pragma once

#include <list>

#include "GridCell.h"
#include "CollisionResolver.h"
#include "SnakeBodyPart.h"
#include "Game.h"

class Game;
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
	Game * currGame;
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
	bool moveForward(GridCell * collisionCell, const SnakeBodyPart * collider);
	bool gameOver(GridCell * collisionCell, const SnakeBodyPart * collider);

	static Snake * createSnake(const int row, const int column, SnakeBodyPartContainer * headContainer, SnakeBodyPartContainer * middleContainer, SnakeBodyPartContainer * tailContainer, Game * theGame);
};

