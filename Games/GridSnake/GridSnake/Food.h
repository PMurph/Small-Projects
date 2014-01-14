#pragma once

typedef enum FOOD_TYPE {
	REGULAR_FOOD
} FoodType;

class Food {
public:
	const FoodType getFoodType() const;
};