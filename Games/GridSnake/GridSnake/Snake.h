#pragma once

#include <list>

#include "GridCell.h"


class GridCell;

class Snake
{
private:
	std::list<GridCell *> snakeCells;
public:
	Snake(void);
	~Snake(void);

	void createSnake(GridCell * headCell, GridCell * middleCell, GridCell * tailCell);
};

