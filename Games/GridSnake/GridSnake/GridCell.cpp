#include "GridCell.h"

GridCell::~GridCell(void)
{
}

void GridCell::setWall()
{
	assert(state == EMPTY);

	if(state == EMPTY)
	{
		state = WALL;
	}
}

const bool GridCell::isOccupied() const
{
	bool occupied = false;

	if(state == WALL || state == FOOD || state == WORM)
	{
		occupied = true;
	}

	return occupied;
}

const CellState GridCell::getState() const
{
	return state;
}
