#pragma once

typedef enum OCCUPANT_TYPE
{
	SNAKE,
	SNAKE_HEAD,
	FOOD
} OccupantType;

class GridCellOccupant
{
public:
	virtual const OccupantType getType() const = 0;
};