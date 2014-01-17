#pragma once

#include "GridCellOccupant.h"

#include <GL/glut.h>
#include <assert.h>

class GridCellOccupant;
class SnakeBodyPart;

class SnakeBodyPart:
	public GridCellOccupant
{
	mutable OccupantType partType;
	const SnakeBodyPart * nextPart;
public:
	SnakeBodyPart(const SnakeBodyPart * nextBodyPart, bool isHead)
		: nextPart(nextBodyPart), partType(SNAKE) { isHead ? partType = SNAKE_HEAD : partType = SNAKE; };
	~SnakeBodyPart(void);

	void setBody() const;
	const SnakeBodyPart * getNextBodyPart() const;
	const OccupantType getType() const;
	const GLfloat * getColour() const;
};

const GLfloat SNAKE_HEAD_COLOUR[] = { 0.0f, 0.8f, 0.0f, 1.0f };
const GLfloat SNAKE_BODY_COLOUR[] = { 0.0f, 0.5f, 0.0f, 1.0f };

