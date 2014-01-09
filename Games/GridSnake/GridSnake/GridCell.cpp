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
	
	glPushMatrix();

	glTranslatef(0.5f, 0.5f, 0.0f);
	glScalef(floor(cellSize), floor(cellSize), 1.0f);

	glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();

	setCellOutLineColour();

	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
	glEnd();

	glPopMatrix();
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
	switch( state )
	{
	case FOOD:
	case WORM:
	case WALL:
		glColor4f(WALL_COLOUR[0], WALL_COLOUR[1], WALL_COLOUR[2], WALL_COLOUR[3]);
		break;
	case EMPTY:
	default:
		glColor4f(EMPTY_COLOUR[0], EMPTY_COLOUR[1], EMPTY_COLOUR[2], EMPTY_COLOUR[3]);
		break;
	}
}

void GridCell::setCellOutLineColour() const
{
	glColor4f(OUTLINE_COLOUR[0], OUTLINE_COLOUR[1], OUTLINE_COLOUR[2], OUTLINE_COLOUR[3]);
}