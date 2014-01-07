#include "ListDrawer.h"


ListDrawer::ListDrawer(void)
{

}


ListDrawer::~ListDrawer(void)
{
}

void ListDrawer::registerDrawable(const Drawable * toRegister)
{
	drawables.push_back(toRegister);
}

void ListDrawer::unregisterDrawable(const Drawable * toUnRegister)
{
	std::list<const Drawable *>::const_iterator it;
	bool matches = false;

	for(it = drawables.begin(); it != drawables.end() && matches == false; it++)
	{
		if((*it) == toUnRegister)
		{
			matches = true;
		}
	}

	if(matches == true)
	{
		drawables.erase(it);
	}
}

void ListDrawer::drawAll() const
{
	std::list<const Drawable *>::const_iterator it;

	for(it = drawables.begin(); it != drawables.end(); it++)
	{
		(*it)->draw();
	}
}