#pragma once

#include "main.h"
#include "SnakeBodyPart.h"
#include "SnakeBobyPartContainer.h"

class SnakeBodyPart;
class GridCellOccupant;
class SnakeBodyPartContainer;
class Drawable;

typedef enum GRID_CELL_STATE {
	EMPTY,
	WALL,
	FOOD_CELL,
	SNAKE_CELL,
} CellState;

class GridCell:
	public Drawable, public SnakeBodyPartContainer
{
private:
	static GLfloat cellSize;

	const GridCellOccupant * cellOccupant;
	CellState state;

	void setColour() const;
	void setCellOutLineColour() const;

	void validateState() const;
public:
	GridCell(void)
		:cellOccupant(NULL), state(EMPTY) {};
	~GridCell(void);

	const bool addBodyPartToContainer(const SnakeBodyPart * bodyPart);
	const bool setOccupant(const GridCellOccupant * newOccupant);
	void setWall();
	void clearCell();
	void clearContainer();

	const CellState getState() const;
	const bool isOccupied() const;
	const GridCellOccupant * getOccupant() const;
	const SnakeBodyPart * getBodyPartInContainer() const;
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

