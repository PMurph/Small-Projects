#pragma once

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"
#include "GridCell.h"
#include <list>

class Grid;
class Drawer;

class Game
{
private:
	std::list<GridCell *> snakeCells;
	Grid * gameGrid;
	Drawer * gameDrawer;

	void initGame();
public:
	Game(void);
	~Game(void);

	void windowReshaped();

	void drawGame() const;
};

