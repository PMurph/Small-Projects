#pragma once

#include "main.h"
#include "GridCell.h"
#include <list>

class GridCell;

class Grid:
	public Drawable
{
private:
	GridCell ** cells;
	int gridWidth, gridHeight;
	bool horizontalPadding, verticalPadding;

	void centerGridTransformation() const;
	const int getGridCellIndex(const int row, const int column) const;
	const float calcCellToDimensionRatio(const int numCells, const int dimSize, const int paddingSize) const; 

	void initGrid();
	void initGridCells();
	void setGridCellSize(const GLfloat cellRatio);
	void determineGridPadding(const GLfloat cellSize);
	void clearGrid();
	void attachBodyPartsToCells(const SnakeBodyPart * head, const SnakeBodyPart * middle, const SnakeBodyPart * tail);
public:
	Grid(const int width, const int height);
	~Grid(void);

	void calcGridCellSize();
	std::list<GridCell *> generateNewSnake();

	
	void draw() const;
};

const int GRID_PADDING_X = 10;
const int GRID_PADDING_Y = 10;

