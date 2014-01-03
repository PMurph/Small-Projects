#ifndef __GRID_CELL_H
#define __GRID_CELL_H

#include "main.h"

typedef enum GRID_CELL_STATE {
	EMPTY,
	WALL,
	FOOD,
	WORM
} CellState;

class GridCell:
	public Drawable
{
private:
	CellState state;
public:
	GridCell()
		:state(EMPTY) {};
	~GridCell(void);

	const CellState getState() const;
	const bool isOccupied() const;

	void setWall();

	void draw() const;
};

#endif

