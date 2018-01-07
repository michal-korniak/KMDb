#include "stdafx.h"
#include "ColumnType.h"

ColumnType::ColumnType(string type)
{
	this->type = type;
}

string ColumnType::getType() const
{
	return type;
}
