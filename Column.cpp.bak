#include "stdafx.h"
#include "Column.h"
#include "Table.h"
#include "Row.h"
#include <vector>

using namespace std;
Column::Column(const string& name, ColumnType type)
{
	this->name = name;
	this->type = type.getType();
}

vector<Cell> Column::getCells()
{ 
	auto rows = table->getRows();
	vector<Cell> result;

	for (auto& row : rows) {
		auto cells = row.getCells();
		result.push_back(cells[index]);
	}

	return result;
}

//Column & Column::addCell(Cell cell)
//{
//	cells.push_back(cell);
//	return *this;
//}

string Column::getName() const
{
	return name;
}

string Column::getType() const
{
	return type;
}

