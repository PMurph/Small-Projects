#pragma once

#include "main.h"
#include "GridCell.h"
#include <list>

class GridCell;
class SnakeBodyPartContainer;

class Grid:
	public Drawable
{
private:
	GridCell ** cells;
	int gridWidth, gridHeight;
	bool horizontalPadding, verticalPadding;

	void centerGridTransformation() const;
	const float calcCellToDimensionRatio(const int numCells, const int dimSize, const int paddingSize) const;
	const int getIndex(const int row, const int col, const int rowOffset, const int colOffset) const;

	void initGrid();
	void initGridCells();
	void setGridCellSize(const GLfloat cellRatio);
	void determineGridPadding(const GLfloat cellSize);
public:
	Grid(const int width, const int height);
	~Grid(void);

	void calcGridCellSize();
	void clearGrid();
	void setGameOverMessage();

	SnakeBodyPartContainer * getBodyPartContainer(const int row, const int col) const;	
	const int getGridWidth() const;
	const int getGridHeight() const;
	void draw() const;
};

const int GRID_PADDING_X = 10;
const int GRID_PADDING_Y = 10;

