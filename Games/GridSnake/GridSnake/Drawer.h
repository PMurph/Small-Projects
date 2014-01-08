#pragma once

#include "Drawable.h"

class Drawer
{
public:
	virtual void registerDrawable(const Drawable * toRegister) = 0;
	virtual void unregisterDrawable(const Drawable * toUnRegister) = 0;
	virtual void drawAll() const = 0;
};