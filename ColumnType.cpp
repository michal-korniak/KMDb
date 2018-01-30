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

ColumnType ColumnType::convertFromString(string st) {
	if (st == "String")
		return ColumnType("String");
	if (st == "Number")
		return ColumnType("Number");
	throw runtime_error("Wrong type.");
}
