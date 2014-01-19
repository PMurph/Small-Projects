#pragma once

#include <list>

#include "Drawer.h"
#include "ListDrawer.h"
#include "Grid.h"
#include "GridCell.h"
#include "Snake.h"
#include "RegularFood.h"
#include "CollisionResolver.h"

typedef enum SNAKE_DIRECTION SnakeDirection;

class Snake;
class Grid;
class Drawer;
class CollisionResolver;

class Game
{
private:
	Snake * snake;
	Grid * gameGrid;
	Drawer * gameDrawer;
	CollisionResolver * gameCollisionResolver;
	SnakeDirection nextDirection;
	int timeSinceLastMove;
	bool gameRunning;

	Food * generateRandomFoodType() const;

	void initGame();
	void generateNewSnake();
	void moveSnake();
	void updateSnakeDirection();
public:
	Game(void);
	~Game(void);

	void windowReshaped();
	void newGame();
	void updateGame(int value);
	void handleInput(const unsigned char key);
	void gameOver();
	void generateFood();

	void drawGame() const;
};

