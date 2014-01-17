#pragma once

#include <map>
#include <vector>

#include "GridCellOccupant.h"
#include "GridCell.h"
#include "Snake.h"
#include "SnakeBodyPart.h"

class Snake;
class SnakeBodyPart;
class GridCellOccupant;

class CollisionResolver
{
private:
	std::map<GridCell *, const GridCellOccupant *> collisions;
	std::vector<GridCell *> keys;
public:
	CollisionResolver(void);
	~CollisionResolver(void);

	bool resolveCollision(GridCell * resolutionCell, Snake * snake, bool (Snake::*resolutionFunction)(GridCell * collisionCell, const SnakeBodyPart * collider));
	void registerCollision(GridCell * collisionCell, const GridCellOccupant * collider);
	void clearCollisions();

	static const bool checkCollision(const GridCell * collisionCell);
};

