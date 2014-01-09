#pragma once

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"

class Grid;
class Drawer;

class Game
{
private:
	Grid * gameGrid;
	Drawer * gameDrawer;

	void initGame();
public:
	Game(void);
	~Game(void);

	void windowReshaped();

	void drawGame() const;
};

