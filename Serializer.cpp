#include "stdafx.h"
#include "Serializer.h"
#include <fstream>

using namespace std;
void Serializer::saveDatabase(Database& database)
{
	ofstream dbStream = openDbStream(database.getName().c_str());
	saveChanges(dbStream, database);

}

ofstream Serializer::openDbStream(string name)
{
	ofstream dbStream;
	dbStream.open(name);
	if(!dbStream.good())
	{
		throw exception("An erorr ocurred when file with db was opening");
	}
	return dbStream;
}

void Serializer::saveChanges(ofstream& dbStream, Database& database)
{
	auto tables = database.getTables();
	for (int i = 0; i < tables.size(); ++i)
	{
		dbStream << "<table \"" << tables[i].getName() << "\">";
		auto columns = tables[i].getColumns();
		if (columns.size() != 0)
			dbStream << endl;
		for (int j = 0; j<columns.size(); ++j)
		{
			dbStream << columns[j].getName() << "(" << columns[j].getType() << ")";
			if (j != columns.size() - 1)
				dbStream << "|";

		}
		dbStream << endl;

		auto rows = tables[i].getRows();
		for(int j=0; j<rows.size(); ++j)
		{
			auto cells = rows[j].getCells();
			for(int k=0; k<cells.size(); ++k)
			{
				dbStream << cells[k].getValue();
				if (k != cells.size() - 1)
					dbStream << "|";
			}
			dbStream << endl;
		}
		dbStream << "</table>" << endl;
	}

}
