#pragma once

#include "GridCell.h"

class Grid:
	public Drawable
{
private:
	GridCell * cells;
	int gridWidth, gridHeight;
	bool horizontalPadding, verticalPadding;

	void initGrid();
	void initGridCells();
	void initGridCellSize(const GLfloat cellRatio);
	void determineGridPadding(const GLfloat cellSize);

	const float calcCellToDimensionRatio(const int numCells, const int dimSize, const int paddingSize) const; 
public:
	Grid(const int width, const int height);
	~Grid(void);

	void draw() const;
};

const int GRID_PADDING_X = 10;
const int GRID_PADDING_Y = 10;

