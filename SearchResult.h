#pragma once

#include <vector>
#include "Table.h"

class SearchResult
{
public:
	SearchResult();
	vector<int> indexes;
	Table* table;
};

