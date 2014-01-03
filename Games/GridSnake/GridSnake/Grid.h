#ifndef __GRID_H
#define __GRID_H

#include "main.h"
#include "GridCell.h"

class Grid:
	public Drawable
{
private:
	int gridWidth;
	int gridHeight;
	GridCell * cells;

	void initGrid();
public:
	Grid(const int width, const int height);
	~Grid(void);

	void draw() const;
};

#endif

