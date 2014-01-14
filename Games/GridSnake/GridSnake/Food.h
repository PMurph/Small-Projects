#pragma once

#include "GridCellOccupant.h"

#include <GL/glut.h>

typedef enum FOOD_TYPE {
	REGULAR_FOOD
} FoodType;

class Food:
	public GridCellOccupant
{
public:
	virtual const FoodType getFoodType() const = 0;
};