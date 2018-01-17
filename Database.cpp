#include "stdafx.h"
#include "Database.h"

Database::Database(const string& name)
{
	//walidacja czy baza o takiej nazwie juz nie istnieje
	this->name = name;
}
void Database::addTable(const Table& newTable)
{
	for (auto table : tables)
	{
		if (table.getName() == newTable.getName())
		{
			throw runtime_error("Table with this name already exist.");
		}
	}
	tables.push_back(newTable);
}

Table* Database::getTable(const string& name)
{
	for (auto& table : tables)
	{
		if (table.getName() == name)
			return &table;
	}
	throw runtime_error("Table with this name doesn't exist");
}

string Database::getName() const
{
	return name;
}

vector<Table> Database::getTables() const
{
	return tables;
}
