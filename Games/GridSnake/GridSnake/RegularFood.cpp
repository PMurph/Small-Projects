#include "RegularFood.h"


RegularFood::~RegularFood(void)
{
}

const FoodType RegularFood::getFoodType() const
{
	return type;
}

const OccupantType RegularFood::getType() const
{
	return FOOD;
}

const GLfloat * RegularFood::getColour() const
{
	return REGULAR_FOOD_COLOUR;
}