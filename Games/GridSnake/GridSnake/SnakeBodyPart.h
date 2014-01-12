#pragma once

#include "GridCellOccupant.h"

#include <assert.h>

class GridCellOccupant;
class SnakeBodyPart;

class SnakeBodyPart:
	public GridCellOccupant
{
	OccupantType partType;
	const SnakeBodyPart * nextPart;
public:
	SnakeBodyPart(const SnakeBodyPart * nextBodyPart, bool isHead)
		: nextPart(nextBodyPart), partType(SNAKE) { isHead ? partType = SNAKE_HEAD : partType = SNAKE; };
	~SnakeBodyPart(void);

	void setBody();

	const SnakeBodyPart * getNextBodyPart() const;
	const OccupantType getType() const;
};

