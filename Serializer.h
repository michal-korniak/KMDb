#pragma once
#include "Database.h"

class Serializer
{
public:
	static void saveDatabase(Database& database);
private:
	static ofstream openDbStream(string name);
	static void saveChanges(ofstream& dbStream, Database& database);
};
