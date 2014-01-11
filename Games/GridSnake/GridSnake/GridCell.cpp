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

	if(state == WALL || state == FOOD || state == SNAKE)
	{
		occupied = true;
	}

	return occupied;
}

const CellState GridCell::getState() const
{
	return state;
}

const GridCellOccupant * GridCell::getOccupant() const
{
	return cellOccupant;
}

const bool GridCell::addBodyPartToContainer(const SnakeBodyPart * newOccupant)
{
	return setOccupant(newOccupant);
}

const bool GridCell::setOccupant(const GridCellOccupant * newOccupant)
{
	bool occupantSet = false;

	assert( state != WALL );

	if(state != WALL)
	{
		if(newOccupant == NULL)
		{
			state = EMPTY;
		}
		else
		{
			state = SNAKE;
		}

		cellOccupant = newOccupant;
		occupantSet = true;
	}

	validateState();

	return occupantSet;
}

void GridCell::clearCell()
{
	assert(state != WALL);

	if(state != WALL)
	{
		state = EMPTY;
		
		if(cellOccupant != NULL)
		{
			delete cellOccupant;
		}
	}

	validateState();
}


void GridCell::clearContainer()
{
	assert( state == SNAKE );
	assert( cellOccupant != NULL );

	if( state == SNAKE && cellOccupant != NULL )
	{
		state = EMPTY;
		cellOccupant = NULL;
	}
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
	case SNAKE:
		if( cellOccupant->getType() == SNAKE_HEAD )
		{
			glColor4f(SNAKE_HEAD_COLOUR[0], SNAKE_HEAD_COLOUR[1], SNAKE_HEAD_COLOUR[2], SNAKE_HEAD_COLOUR[3]);
		}
		else
		{
			glColor4f(SNAKE_BODY_COLOUR[0], SNAKE_BODY_COLOUR[1], SNAKE_BODY_COLOUR[2], SNAKE_BODY_COLOUR[3]);
		}
		break;
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

void GridCell::validateState() const
{
	assert( ( state == EMPTY && cellOccupant == NULL ) || ( state == WALL && cellOccupant == NULL ) ||
		( state == SNAKE && cellOccupant != NULL ) );
}