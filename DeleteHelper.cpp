#include "DeleteHelper.h"
#include <iostream>
#include "Utilities.h"
#include "SearchHelper.h"

void DeleteHelper::Delete(Database * database, string query)
{
	auto searchResult = SearchHelper::Search(database, query);

	if (searchResult.indexes.size() > 0) {
		for (auto& index : searchResult.indexes) {
			searchResult.table->DeleteRow(index);
		}
	}
}
