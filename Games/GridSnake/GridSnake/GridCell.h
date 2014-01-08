#pragma once

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
	static GLfloat cellSize;

	void setColour() const;
	void setCellOutLineColour() const;
public:
	GridCell(void)
		:state(EMPTY) {};
	~GridCell(void);

	const CellState getState() const;
	const bool isOccupied() const;

	void setWall();

	void draw() const;

	static const GLfloat getCellSize() 
	{
		return GridCell::cellSize;
	}

	static void setSize(const GLfloat newSize)
	{
		GridCell::cellSize = newSize;
	}
};

const GLfloat WALL_COLOUR[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat EMPTY_COLOUR[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat OUTLINE_COLOUR[] = { 0.7f, 0.7f, 0.7f, 1.0f };

