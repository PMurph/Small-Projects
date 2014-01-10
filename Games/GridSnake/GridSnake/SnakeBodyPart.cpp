#include "SnakeBodyPart.h"

SnakeBodyPart::~SnakeBodyPart(void)
{
}

const SnakeBodyPart * SnakeBodyPart::getNextBodyPart() const
{
	return nextPart;
}

const bool SnakeBodyPart::isSnakeHead() const
{
	return isHead;
}
