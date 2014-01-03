#include "GridCell.h"

GLfloat GridCell::cellSize = 1.0;

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

void GridCell::draw() const
{
	setColour();

	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(cellSize, 0);
	glVertex2f(cellSize, cellSize);
	glVertex2f(0, cellSize);
	glEnd();
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

/* ===============================
 * Private Methods
 * ===============================
 */

void GridCell::setColour() const
{
	glColor4f(EMPTY_COLOUR[0], EMPTY_COLOUR[1], EMPTY_COLOUR[2], EMPTY_COLOUR[3]);
}