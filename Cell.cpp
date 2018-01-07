#include "stdafx.h"
#include "Cell.h"

Cell::Cell(string value)
{
	this->value = value;
}

string Cell::getValue() const
{
	return value;
}
