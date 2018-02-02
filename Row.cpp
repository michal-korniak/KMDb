#include "Row.h"

Row& Row::addCell(Cell cell)
{
	cells.push_back(cell);
	return *this;
}

int Row::numberOfCells() const
{
	return cells.size();
}

Cell& Row::operator[](const int index)
{
	return cells[index];
}

vector<Cell> Row::getCells() const
{
	return cells;
}
