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

	if(state == WALL || state == FOOD_CELL || state == SNAKE_CELL)
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
		else if( newOccupant->getType() == SNAKE || newOccupant->getType() == SNAKE_HEAD )
		{
			state = SNAKE_CELL;
		}
		else if( newOccupant->getType() == FOOD )
		{
			state = FOOD_CELL;
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
			cellOccupant = NULL;
		}
	}

	validateState();
}


void GridCell::clearContainer()
{
	if( state == SNAKE_CELL && cellOccupant != NULL )
	{
		state = EMPTY;
		cellOccupant = NULL;
	}
}

const SnakeBodyPart * GridCell::getBodyPartInContainer() const
{
	const SnakeBodyPart * bodyPart = NULL;

	assert( state == SNAKE_CELL && cellOccupant != NULL && ( cellOccupant->getType() == SNAKE || cellOccupant->getType() == SNAKE_HEAD ) );

	if( state == SNAKE_CELL && cellOccupant != NULL && ( cellOccupant->getType() == SNAKE || cellOccupant->getType() == SNAKE_HEAD ) )
	{
		bodyPart = dynamic_cast<const SnakeBodyPart *>( cellOccupant );
	}

	return bodyPart;
}

const bool GridCell::canContainSnakeBodyPart() const
{
	bool canContain = false;

	if( state != WALL )
	{
		canContain = true;
	}

	return canContain;
}

void GridCell::setMsgCell()
{
	assert( state == EMPTY );

	if( state == EMPTY )
	{
		state = MSG_CELL;
	}
}

/* ===============================
 * Private Methods
 * ===============================
 */

void GridCell::setColour() const
{
	const GLfloat * colour;

	switch( state )
	{
	case FOOD_CELL:
	case SNAKE_CELL:
		colour = cellOccupant->getColour();
		glColor4f(colour[0], colour[1], colour[2], colour[3]);
		break;
	case WALL:
		glColor4f(WALL_COLOUR[0], WALL_COLOUR[1], WALL_COLOUR[2], WALL_COLOUR[3]);
		break;
	case MSG_CELL:
		glColor4f( MSG_COLOUR[0], MSG_COLOUR[1], MSG_COLOUR[2], MSG_COLOUR[3]);
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
		( state == SNAKE_CELL && cellOccupant != NULL ) || ( state == MSG_CELL && cellOccupant == NULL ) ||
		( state == FOOD_CELL && cellOccupant != NULL));
}