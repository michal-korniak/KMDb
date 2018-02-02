#include "Table.h"
#include <iostream>
#include <numeric>

using namespace std;


vector<size_t> getOrder(Column* column, bool desc);

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v, bool desc);

void reorder(vector<Row> *rows, vector<size_t> indexes);
Table::Table(const string& name)
{

	this->name = name;
}
string Table::getName() const
{
	return name;
}

void Table::addColumn(Column& newColumn)
{
	for (auto column : columns)
	{
		if (column.getName() == newColumn.getName())
			throw runtime_error("Column with this name already exist.");
	}

	if (columns.empty())
		newColumn.index = 0;
	else
		newColumn.index = columns.back().index + 1;


	newColumn.table = this;
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
		if (row.getCells()[i].column != &this->columns[i])
		{
			if(row.getCells()[i].column->getName()==this->columns[i].getName()
				&& row.getCells()[i].column->getType() == this->columns[i].getType()) 
			{
				row.getCells()[i].column = &this->columns[i];
				continue;
			}
			throw runtime_error("Row is not compatible with this table");
		}
	}
	rows.push_back(row);
}

vector<Row> Table::getRows() const
{
	return rows;
}

vector<Column>& Table::getColumns()
{
	return columns;
}


void Table::DeleteRow(int index)
{
	rows.erase(rows.begin() + index);
}
Column * Table::getColumn(const string & columnNameParam)
{
	for (auto& column : columns)
	{
		//Not worling correctly
		/*if (column.getName() == name)
			return &column;*/

		string columnName = column.getName();

		if (columnName.compare(columnNameParam) == 0)
			return &column;

	}

	return nullptr;
}

void Table::SortTable(const string & columnName, bool desc)
{
	auto column = getColumn(columnName);

	if (column == nullptr) {
		cout << "Can't find column with name: " << columnName << endl;
		return;
	}

	vector<size_t> order = getOrder(column, desc);
	reorder(&rows, order);
}


vector<size_t> getOrder(Column* column, bool desc) {
	auto cells = column->getCells();
	return sort_indexes(cells, desc);
}


//Also from stack: stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
template <typename T>
vector<size_t> sort_indexes(const vector<T> &v, bool desc) {

	// initialize original index locations
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v

	if (desc == false)
		sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });
	else
		sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

	return idx;
}

//From: //www.geeksforgeeks.org/reorder-a-array-according-to-given-indexes/s
void reorder(vector<Row> *rows, vector<size_t> indexes) {
	vector<Row> rowsTemp;
	rowsTemp = *rows;
	rows->clear();

	for (auto& index : indexes) {
		rows->push_back(rowsTemp[index]);
	}

}



