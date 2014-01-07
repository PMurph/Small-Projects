#pragma once

#include <GL\glut.h>

class Drawable
{
public:
	virtual void draw() const = 0;
};
