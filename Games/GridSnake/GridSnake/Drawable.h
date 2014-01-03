#ifndef __DRAWABLE_H
#define __DRAWABLE_H

#include <GL\glut.h>

class Drawable
{
public:
	virtual void draw() const = 0;
};

#endif