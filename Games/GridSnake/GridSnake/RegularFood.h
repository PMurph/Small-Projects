#pragma once

#include "Food.h"
#include "GridCellOccupant.h"

class Food;

class RegularFood:
	public Food
{
private:
	const FoodType type;
public:
	RegularFood(void)
		:type(REGULAR_FOOD) {};
	~RegularFood(void);

	const OccupantType getType() const;
	const FoodType getFoodType() const;
	const GLfloat * getColour() const;
};

const GLfloat REGULAR_FOOD_COLOUR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
