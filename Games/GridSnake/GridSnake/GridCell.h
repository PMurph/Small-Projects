#pragma once

#include "main.h"
#include "SnakeBodyPart.h"

class SnakeBodyPart;

typedef enum GRID_CELL_STATE {
	EMPTY,
	WALL,
	FOOD,
	SNAKE,
} CellState;

class GridCell:
	public Drawable
{
private:
	static GLfloat cellSize;

	const SnakeBodyPart * cellOccupant;
	CellState state;

	void setColour() const;
	void setCellOutLineColour() const;

	void validateState() const;
public:
	GridCell(void)
		:cellOccupant(NULL), state(EMPTY) {};
	~GridCell(void);

	const bool setOccupant(const SnakeBodyPart * newOccupant);
	void setWall();
	void clearCell();

	const CellState getState() const;
	const bool isOccupied() const;
	const SnakeBodyPart * getOccupant() const;
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
const GLfloat SNAKE_HEAD_COLOUR[] = { 0.0f, 0.8f, 0.0f, 1.0f };
const GLfloat SNAKE_BODY_COLOUR[] = { 0.0f, 0.5f, 0.0f, 1.0f };

