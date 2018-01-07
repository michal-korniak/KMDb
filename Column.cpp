#include "stdafx.h"
#include "Column.h"

using namespace std;
Column::Column(const string& name, ColumnType type)
{
	this->name = name;
	this->type = type.getType();
}

string Column::getName() const
{
	return name;
}

string Column::getType() const
{
	return type;
}
