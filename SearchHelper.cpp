#include "stdafx.h"
#include "SearchHelper.h"
#include <iostream>
#include <vector>
#include "Utilities.h"
#include "SearchResult.h"

using namespace std;

const string selectStatement = "SELECT";
const string fromStatement = "FROM";
const string whereStatement = "WHERE";
const string endStatment = "END";

// Query Ex.: SELECT Colum1,Column2 FROM table WHERE Column1>X END

vector<Column*> initializeColumns(Table* table, vector<string> columnNames);

SearchResult SearchHelper::Search(Database* database, string query)
{
	int selectPos = query.find(selectStatement);

	int fromPos = query.find(fromStatement);
	int wherePos = query.find(whereStatement);
	int endPos = query.find(endStatment);
	int fromSelectLength = fromPos - (selectPos + selectStatement.length());
	int whereFromLength = wherePos - (fromPos + fromStatement.length());
	int endWhereLength = endPos - (wherePos + whereStatement.length());

	SearchResult searchResult;
	vector<int> indexes;
	int tempLength = fromPos + fromStatement.length();

	string tableName = query.substr(tempLength, whereFromLength);
	tableName.erase(remove(tableName.begin(), tableName.end(), ' '), tableName.end());

	auto table = database->getTable(tableName);
	if (table == nullptr) {
		cout << "Table does not exist " + tableName << endl;
		return searchResult;
	}
	else {

		searchResult.table = table;

		tempLength = wherePos + whereStatement.length();
		string whereQuery = query.substr(tempLength, endWhereLength);

		int morePos = whereQuery.find(">");
		int lessPos = whereQuery.find("<");
		int equalPos = whereQuery.find("=");
		int signPos;

		char operatorSign;
		if (morePos != -1) {
			signPos = morePos;
			operatorSign = '>';
		}
		else if (lessPos != -1) {
			signPos = lessPos;
			operatorSign = '<';
		}
		else if (equalPos != -1) {
			signPos = equalPos;
			operatorSign = '=';
		}

		int columnNameLength = whereQuery.find(operatorSign);
		string columnName = whereQuery.substr(0, columnNameLength);
		Utilities::EraseWhitespaces(columnName);

		endPos = whereQuery.find("END");
		string value = whereQuery.substr(signPos + 1);

		Column* column = table->getColumn(columnName);
		vector<Cell> cells = column->getCells();

		if (column->getType() != "Number") {
			cout << "Error inappropiate column type" << endl;
		}

		for (int i = 0; i < cells.size(); i++)
		{
			Cell cell = cells[i];
			string cellValue = cell.getValue();

			switch (operatorSign)
			{
			case '>':
				if (stoi(cellValue) > stoi(value)) {
					indexes.push_back(i);
				}
				break;
			case '<':
				if (stoi(cellValue) < stoi(value)) {
					indexes.push_back(i);
				}
				break;
			case '=':
				if (stoi(cellValue) == stoi(value)) {
					indexes.push_back(i);
				}
				break;
			default:
				break;
			}
		}

	}

	searchResult.indexes = indexes;
	return searchResult;
}


