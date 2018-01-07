#pragma once
#include <string>
#include <vector>
#include "Column.h"
#include "Row.h"
using namespace std;
class Table
{
	string name;
	vector<Column> columns;
	vector<Row> rows;
public:
	Table(const string& name);
	string getName() const;
	void addColumn(const Column& column);
	void verifyCompatibiltyWithType(const Column& column, const Cell& cell) const;
	void addRow(Row row);
	vector<Row> getRows() const;
	vector<Column> getColumns() const;
};
