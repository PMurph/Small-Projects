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