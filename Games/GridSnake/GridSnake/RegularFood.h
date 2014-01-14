#pragma once

#include "Food.h"
#include "GridCellOccupant.h"

class Food;

class RegularFood:
	public Food, public GridCellOccupant
{
private:
	const FoodType type;
public:
	RegularFood(void)
		:type(REGULAR_FOOD) {};
	~RegularFood(void);

	const OccupantType getType() const;
	const FoodType getFoodType() const;
};

