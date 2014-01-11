#pragma once

#include <list>

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"
#include "GridCell.h"

class Snake;
class Grid;
class Drawer;

class Game
{
private:
	Snake * snake;
	Grid * gameGrid;
	Drawer * gameDrawer;

	void initGame();
	void generateNewSnake();
public:
	Game(void);
	~Game(void);

	void windowReshaped();

	void drawGame() const;
};

