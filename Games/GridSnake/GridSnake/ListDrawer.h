#pragma once

#include "Drawer.h"

#include <list>
#include <assert.h>

class ListDrawer:
	public Drawer
{
private:
	std::list<const Drawable *> drawables;
public:
	ListDrawer(void);
	~ListDrawer(void);
	void registerDrawable(const Drawable * toRegister);
	void unregisterDrawable(const Drawable * toUnRegister);
	void drawAll() const;
};

