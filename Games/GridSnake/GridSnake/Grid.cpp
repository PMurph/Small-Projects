#include "Grid.h"

Grid::Grid(const int width, const int height)
{
	gridWidth = width + 2;
	gridHeight = height + 2;
	verticalPadding = false;
	horizontalPadding = false;

	initGrid();
}


Grid::~Grid(void)
{
	delete[gridWidth * gridHeight] cells;
}

void Grid::draw() const
{
	int i, j;
	const GLfloat cellSize = GridCell::getCellSize();

	for( i = 0; i < gridHeight; i++)
	{
		for( j = 0; j < gridWidth; j++)
		{
			glPushMatrix();

			glTranslatef(j * cellSize, i * cellSize, 0.0);

			cells[i * gridWidth + j].draw();

			glPopMatrix();
		}
	}
}

/* ===============================
 * Private Methods
 * ===============================
 */

void Grid::initGrid()
{
	const int width = getWidth(), height = getHeight();
	float cellToWidthRatio, cellToHeightRatio;

	cellToWidthRatio = calcCellToDimensionRatio(gridWidth, width, GRID_PADDING_X);
	cellToHeightRatio = calcCellToDimensionRatio(gridHeight, height, GRID_PADDING_Y);

	if(cellToWidthRatio < cellToHeightRatio)
	{
		initGridCellSize(cellToWidthRatio);
	}
	else
	{
		initGridCellSize(cellToHeightRatio);
	}

	initGridCells();
}

void Grid::initGridCellSize(const GLfloat cellRatio)
{
	GLfloat cellSize;

	assert(cellRatio != 0.0);

	if(cellRatio != 0.0)
	{
		cellSize = floor(cellRatio);

		GridCell::setSize(cellSize);
	}
	else
	{
		cellSize = 1.0;

		GridCell::setSize(cellSize);
	}

	determineGridPadding(cellSize);
}

void Grid::initGridCells()
{
	int i;

	assert(gridWidth > 0);
	assert(gridHeight > 0);
	
	if(gridWidth > 0 && gridHeight > 0)
	{
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
}

const float Grid::calcCellToDimensionRatio(const int numCells, const int dimSize, const int paddingSize) const
{
	GLfloat ratio = 1.0;

	assert(numCells > 0);
	assert(dimSize > 0);
	assert(paddingSize >= 0);

	if(numCells > 0 && dimSize > 0 && paddingSize >= 0)
	{
		if(numCells < dimSize - 2.0 * paddingSize)
		{
			ratio = static_cast<GLfloat>((dimSize - 2.0 * paddingSize) / static_cast<GLfloat>(numCells));
		}
		else if(numCells < dimSize)
		{
			ratio = static_cast<GLfloat>(dimSize / static_cast<GLfloat>(numCells));
		}
	}

	return ratio;
}

void Grid::determineGridPadding(const GLfloat cellSize)
{
	int width = getWidth(), height = getHeight();

	assert(cellSize > 0);

	if(cellSize > 0)
	{
		if(2 * GRID_PADDING_X + cellSize * gridWidth < width)
			horizontalPadding = true;

		if(2 * GRID_PADDING_Y + cellSize * gridHeight < height)
			verticalPadding = true;
	}
}