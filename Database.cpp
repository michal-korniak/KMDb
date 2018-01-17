#include "stdafx.h"
#include "Database.h"
#include "FileSystem.h"

Database::Database() {
}

Database::Database(const string& name)
{
	auto dbNames = FileSystem::getAllDbNames();
	for(const auto dbName: dbNames) {
		if (dbName == name)
			throw runtime_error("Database with this name already exist");
	}
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
