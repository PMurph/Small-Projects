#pragma once

#include <map>
#include <vector>

#include "GridCellOccupant.h"
#include "GridCell.h"

class GridCellOccupant;

class CollisionResolver
{
private:
	std::map<GridCell *, const GridCellOccupant *> collisions;
	std::vector<GridCell *> keys;
public:
	CollisionResolver(void);
	~CollisionResolver(void);

	bool resolveCollisions();
	void registerCollision(GridCell * collisionCell, const GridCellOccupant * collider);
	void clearCollisions();

	static const bool checkCollision(const GridCell * collisionCell);
};

