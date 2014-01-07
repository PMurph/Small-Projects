#pragma once

#include "Drawer.h"
#include <list>

class ListDrawer:
	public Drawer
{
private:
	std::list<const Drawable *> drawables;
public:
	ListDrawer(void);
	~ListDrawer(void);
	virtual void registerDrawable(const Drawable * toRegister);
	virtual void unregisterDrawable(const Drawable * toUnRegister);
	virtual void drawAll() const;
};

