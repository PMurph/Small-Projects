#pragma once

#include <GL/glut.h>

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
	virtual const GLfloat * getColour() const = 0;
};