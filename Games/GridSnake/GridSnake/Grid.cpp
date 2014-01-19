#include "Grid.h"
#include <iostream>

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
	int i;

	for( i = 0; i < gridWidth * gridHeight; i++)
	{
		delete cells[i];
	}

	delete[gridWidth * gridHeight] cells;
}

void Grid::draw() const
{
	int i, j;
	const GLfloat cellSize = floor(GridCell::getCellSize()); 

	centerGridTransformation();

	for( i = 0; i < gridHeight; i++)
	{
		for( j = 0; j < gridWidth; j++)
		{
			glPushMatrix();

			glTranslatef(j * cellSize, i * cellSize, 0.0);

			cells[i * gridWidth + j]->draw();

			glPopMatrix();
		}
	}
}

void Grid::calcGridCellSize()
{
	const int width = getWidth(), height = getHeight();
	float cellToWidthRatio, cellToHeightRatio;

	cellToWidthRatio = calcCellToDimensionRatio(gridWidth, width, GRID_PADDING_X);
	cellToHeightRatio = calcCellToDimensionRatio(gridHeight, height, GRID_PADDING_Y);

	if(cellToWidthRatio < cellToHeightRatio)
	{
		setGridCellSize(cellToWidthRatio);
	}
	else
	{
		setGridCellSize(cellToHeightRatio);
	}
}

SnakeBodyPartContainer * Grid::getBodyPartContainer(const int row, const int column) const
{
	GridCell * cell = NULL;

	assert( row >= 0 && row < gridHeight );
	assert( column >= 0 && gridWidth );

	if( row >= 0 && row < gridHeight && column >= 0 && column < gridWidth )
	{
		cell = cells[row * gridWidth + column];
	}

	return cell;
}

const int Grid::getGridWidth() const
{
	return gridWidth;
}

const int Grid::getGridHeight() const
{
	return gridHeight;
}

void Grid::clearGrid()
{
	int i, j;

	for(i = 1; i < gridHeight - 1; i++)
	{
		for(j = 1; j < gridWidth - 1; j++)
		{
			std::cout << "i: " << i << ", j: " << j << std::endl;
			cells[j * gridWidth + i]->clearCell();
		}
	}
}

void Grid::setGameOverMessage() 
{
	int gridRowOffset, gridColOffset;

	assert( gridWidth >= 20 && gridHeight >= 12 );

	gridColOffset = (gridWidth - 18) / 2;
	gridRowOffset = (gridHeight - 10) / 2; 

	if( gridWidth >= 20 && gridHeight >= 12 )
	{
		cells[getIndex(0, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 4, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 12, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 14, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(0, 16, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(1, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 4, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 8, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 14, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(1, 16, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(2, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 4, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 8, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 14, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(2, 15, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(3, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 4, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 8, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 14, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(3, 16, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(4, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 4, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 8, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 12, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 14, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 15, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(4, 16, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(6, 1, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 5, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 9, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 13, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 15, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 16, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(6, 17, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(7, 1, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 5, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 9, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 13, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(7, 15, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(8, 1, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 5, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 9, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 13, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 15, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(8, 16, gridRowOffset, gridColOffset)]->setMsgCell();
		
		cells[getIndex(9, 1, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 5, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 9, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 13, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(9, 15, gridRowOffset, gridColOffset)]->setMsgCell();

		cells[getIndex(10, 1, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 2, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 3, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 5, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 6, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 7, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 9, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 10, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 11, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 12, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 13, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 15, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 16, gridRowOffset, gridColOffset)]->setMsgCell();
		cells[getIndex(10, 17, gridRowOffset, gridColOffset)]->setMsgCell();
	}
}

GridCell * Grid::getNonSnakeCell() const
{
	GridCell * cell = NULL;
	int cellIndex;

	cellIndex = getRandomGridIndex();

	assert( cellIndex != -1 && cellIndex < gridWidth * gridHeight );

	if( cellIndex != -1 )
	{
		while( cells[cellIndex]->getState() == SNAKE_CELL )
		{
			cellIndex = getRandomGridIndex();

			assert( cellIndex != -1 );

			if( cellIndex == -1 )
				break;
		}

		cell = cells[cellIndex];

		assert( cell != NULL && cell->getState() == EMPTY);
	}

	return cell;
}

/* ===============================
 * Private Methods
 * ===============================
 */

void Grid::initGrid()
{
	calcGridCellSize();

	initGridCells();
}

void Grid::setGridCellSize(const GLfloat cellRatio)
{
	GLfloat cellSize;

	assert(cellRatio != 0.0);

	if(cellRatio != 0.0)
	{
		cellSize = cellRatio;

		GridCell::setSize(cellRatio);
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
		cells = new GridCell * [gridWidth * gridHeight];

		for ( i = 0; i < gridWidth * gridHeight; i++ )
		{
			cells[i] = new GridCell;
		}

		for( i = 0; i < gridWidth; i++)
		{
			cells[i]->setWall();
			cells[(gridWidth - 1) * gridHeight + i]->setWall();
		}

		for( i = 1; i < gridHeight - 1; i++)
		{
			cells[i * gridWidth]->setWall();
			cells[(i + 1) * gridWidth - 1]->setWall();
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

void Grid::centerGridTransformation() const
{
	GLint screenWidth, screenHeight;
	GLfloat gridPxWidth, gridPxHeight;
	GLfloat cellSize;
	GLfloat freeHorizontalSpace, freeVerticalSpace;
	GLfloat translateX = 0, translateY = 0;

	screenWidth = getWidth();
	screenHeight = getHeight();

	cellSize = GridCell::getCellSize();

	gridPxWidth = gridWidth * cellSize;
	gridPxHeight = gridHeight * cellSize;

	if(horizontalPadding)
		gridPxWidth += 2 * GRID_PADDING_X;

	if(verticalPadding)
		gridPxHeight += 2 * GRID_PADDING_Y;

	freeHorizontalSpace = screenWidth - gridPxWidth;
	freeVerticalSpace = screenHeight - gridPxHeight;

	if(freeHorizontalSpace > 0)
		translateX = freeHorizontalSpace / 2.0f;

	if(freeVerticalSpace > 0)
		translateY = freeVerticalSpace / 2.0f;

	glTranslatef(translateX, translateY, 0.0f);
}

const int Grid::getIndex( const int row, const int col, const int rowOffset, const int colOffset) const
{
	return (row + rowOffset) * gridWidth + col + colOffset; 
}

const int Grid::getRandomGridIndex() const
{
	int row, col, index = -1;

	row = rand() % (gridHeight - 2);
	col = rand() % (gridWidth - 2);

	assert( row < gridHeight - 2 && col < gridWidth - 2 );

	if( row < gridHeight - 2 && col < gridWidth - 2 )
	{
		index = getIndex( row, col, 1, 1 );
	}

	return index;
}