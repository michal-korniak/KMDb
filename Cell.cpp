#include "stdafx.h"
#include "Cell.h"
#include "Column.h"

Cell::Cell(string value, Column *column)
{
	this->value = value;
	this->column = column;
	if(!isValueFitIntoType()) {
		throw runtime_error("Value is not compatible with type");
	}
}

string Cell::getValue() const
{
	return value;
}
bool Cell::isValueFitIntoType()
{
	//trzeba wprowadzic wzorzec strategi bo bedzie to slabo wygladalo
	if (column->getType() == "Number")
	{
		try {
			stoi(value);
			return true;
		}
		catch (exception ex)
		{
			return false;
		}
	}
	else if (column->getType() == "String")
	{
		return true;
	}
	return false;

}
