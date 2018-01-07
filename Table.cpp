#include "stdafx.h"
#include "Table.h"
Table::Table(const string& name)
{

	this->name = name;
}
string Table::getName() const
{
	return name;
}

void Table::addColumn(const Column& newColumn)
{
	for (auto column : columns)
	{
		if (column.getName() == newColumn.getName())
			throw runtime_error("Column with this name already exist.");
	}
	columns.push_back(newColumn);
}



void Table::addRow(Row row)
{
	if (row.numberOfCells() > columns.size())
		throw runtime_error("Too many cells in row");
	if (row.numberOfCells() < columns.size())
	{
		throw runtime_error("Not enough cells in row");
		//w momencie wprowadzenia nulli ten if powinien zostac usuniety
	}

	for (int i = 0; i < columns.size(); ++i)
	{
		verifyCompatibiltyWithType(columns[i], row[i]);
	}
	rows.push_back(row);
}

vector<Row> Table::getRows() const
{
	return rows;
}

vector<Column> Table::getColumns() const
{
	return columns;
}


void Table::verifyCompatibiltyWithType(const Column& column, const Cell& cell) const
{
	//trzeba wprowadzic wzorzec strategi bo bedzie to slabo wygladalo
	if(column.getType()=="Number")
	{
		try {
			stoi(cell.getValue());
		}
		catch(exception ex)
		{
			throw runtime_error("Cell is not compatible with type");
		}
	}
	else if(column.getType()=="String")
	{
		//zawsze ok
	}

}
