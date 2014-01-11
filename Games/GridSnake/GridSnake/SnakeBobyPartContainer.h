#pragma once

#include "SnakeBodyPart.h"

class SnakeBodyPart;

class SnakeBodyPartContainer
{
public:
	virtual ~SnakeBodyPartContainer() = 0;
	virtual const bool addBodyPartToContainer(const SnakeBodyPart * bodyPart) = 0;
	virtual void clearContainer() = 0;
};