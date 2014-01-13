#pragma once

#include <list>

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"
#include "GridCell.h"
#include "Snake.h"

typedef enum SNAKE_DIRECTION SnakeDirection;

class Snake;
class Grid;
class Drawer;

class Game
{
private:
	Snake * snake;
	Grid * gameGrid;
	Drawer * gameDrawer;
	SnakeDirection nextDirection;
	int prevTime;
	bool gameRunning;

	void initGame();
	void generateNewSnake();
	void moveSnake();
	void updateSnakeDirection();
	void gameOver();
public:
	Game(void);
	~Game(void);

	void windowReshaped();
	void newGame();
	void updateGame(int value);
	void handleInput(const unsigned char key);

	void drawGame() const;
};

