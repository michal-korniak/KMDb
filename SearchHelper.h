#pragma once

#include "Cell.h"
#include "Database.h";
#include "Table.h"
#include "SearchResult.h"

class SearchHelper
{
public:
	static SearchResult Search(Database *database, string query);
};

