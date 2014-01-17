#include "SnakeBodyPart.h"

SnakeBodyPart::~SnakeBodyPart(void)
{
}

const SnakeBodyPart * SnakeBodyPart::getNextBodyPart() const
{
	return nextPart;
}

const OccupantType SnakeBodyPart::getType() const
{
	return partType;
}

void SnakeBodyPart::setBody() const
{
	assert( partType == SNAKE_HEAD );

	partType = SNAKE;
}

const GLfloat * SnakeBodyPart::getColour() const
{
	GLfloat * colour = NULL;

	if( partType == SNAKE_HEAD )
		colour = const_cast<GLfloat *>(SNAKE_HEAD_COLOUR);
	else
		colour = const_cast<GLfloat *>(SNAKE_BODY_COLOUR);

	return colour;
}