#pragma once
#include "Cell.h"
#include "ColumnType.h"
using namespace std;
class Column
{
	string name;
	string type;
public:
	Column(const string& name, ColumnType type);
	string getName() const;
	string getType() const;
};


