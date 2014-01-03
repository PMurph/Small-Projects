#include "Grid.h"


Grid::Grid(const int width, const int height)
{
	gridWidth = width + 2;
	gridHeight = height + 2;

	initGrid();
}


Grid::~Grid(void)
{
	delete[gridWidth * gridHeight] cells;
}

void Grid::draw() const
{
	
}

/* ===============================
 * Private Methods
 * ===============================
 */
void Grid::initGrid()
{
	int i;

	cells = new GridCell [gridWidth * gridHeight];

	for( i = 0; i < gridWidth; i++)
	{
		cells[i].setWall();
		cells[(gridWidth - 1) * gridHeight + i].setWall();
	}

	for( i = 1; i < gridHeight - 1; i++)
	{
		cells[i * gridWidth].setWall();
		cells[i * (gridWidth + 1) - 1].setWall();
	}
}