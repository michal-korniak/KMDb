#pragma once

#include "Cell.h"
#include "Database.h";
#include "Table.h";

class SelectHelper
{
public:
	static Table& Select(Database *database, string query);
};

