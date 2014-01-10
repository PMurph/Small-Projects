#include "SnakeBodyPart.h"

SnakeBodyPart::~SnakeBodyPart(void)
{
}

const SnakeBodyPart * SnakeBodyPart::getNextBodyPart() const
{
	return nextPart;
}
