#pragma once
#include "Cell.h"
#include <vector>
using namespace std;
class Row
{
	vector<Cell> cells;
public:
	Row& addCell(Cell cell);
	int numberOfCells() const;
	Cell& operator[](const int index);
	vector<Cell> getCells() const;
};
