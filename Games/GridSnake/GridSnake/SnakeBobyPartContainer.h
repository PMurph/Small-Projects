#pragma once

#include "SnakeBodyPart.h"

class SnakeBodyPart;

class SnakeBodyPartContainer
{
public:
	virtual const bool canContainSnakeBodyPart() const = 0;
	virtual const bool addBodyPartToContainer(const SnakeBodyPart * bodyPart) = 0;
	virtual void clearContainer() = 0;

	virtual const SnakeBodyPart * getBodyPartInContainer() const = 0;
};