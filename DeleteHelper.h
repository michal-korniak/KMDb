#pragma once

#include "Cell.h"
#include "Database.h";
#include "Table.h";

class DeleteHelper
{
public:
	static void Delete(Database *database, string query);
};


