#pragma once

#include <list>

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"
#include "GridCell.h"
#include "Snake.h"

class Snake;
class Grid;
class Drawer;

class Game
{
private:
	Snake * snake;
	Grid * gameGrid;
	Drawer * gameDrawer;
	int prevTime;

	void initGame();
	void generateNewSnake();
	void moveSnake();
public:
	Game(void);
	~Game(void);

	void windowReshaped();
	void newGame();
	void updateGame(int value);

	void drawGame() const;
};

