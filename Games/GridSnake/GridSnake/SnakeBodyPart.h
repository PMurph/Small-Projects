#pragma once

#include "GridCellOccupant.h"

class GridCellOccupant;

class SnakeBodyPart:
	public GridCellOccupant
{
	OccupantType partType;
	const SnakeBodyPart * nextPart;
public:
	SnakeBodyPart(const SnakeBodyPart * nextBodyPart, bool isHead)
		: nextPart(nextBodyPart), partType(SNAKE) { isHead ? partType = SNAKE_HEAD : partType = SNAKE; };
	~SnakeBodyPart(void);

	const SnakeBodyPart * getNextBodyPart() const;
	const OccupantType getType() const;
};

