#pragma once
#include <string>
#include <vector>
#include "Table.h"
using namespace std;

class Database
{
	string name;
	vector<Table> tables;
public:
	Database(const string& name);
	void addTable(const Table& newTable);
	Table& getTable(const string& name);
	string getName() const;
	vector<Table> getTables() const;
};

