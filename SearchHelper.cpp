#include "stdafx.h"
#include "SearchHelper.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Utilities.h"
#include "SearchResult.h"

using namespace std;

const string selectStatement = "SELECT";
const string fromStatement = "FROM";
const string whereStatement = "WHERE";
const string endStatment = "END";
const string orderStatement = "ST";
const string orderDescStatement = "STDEC";

// Query Ex.: SELECT Colum1,Column2 FROM table WHERE Column1>X END

class WhereCondition {
public:
	string condition;
	string separator;
};

vector<int> whereFilter(Table* table, string whereQuery);
vector<Column*> initializeColumns(Table* table, vector<string> columnNames);
vector<int> conditionIndexes(WhereCondition* condition, Table* table);
vector<int> concatenateVectors(vector<int> A, vector<int> B);
vector<int> getCommonPart(vector<int> A, vector<int> B);
vector<int> allIndexes(Table* table);

SearchResult SearchHelper::Search(Database* database, string query)
{
	int fromPos = query.find(fromStatement);
	int wherePos = query.find(whereStatement);
	int endPos = query.find(endStatment);
	int stPos = query.find(orderStatement);
	int whereFromLength = wherePos - (fromPos + fromStatement.length());

	int endWhereLength = 0;

	if (stPos != -1) {
		endWhereLength = stPos - (wherePos + whereStatement.length());
	}
	else {
		endWhereLength = endPos - (wherePos + whereStatement.length());
	}

	SearchResult searchResult;
	vector<int> indexes;
	int tempLength = fromPos + fromStatement.length();

	fromPos = query.find(" ", fromPos + 1);
	int tableNamePosEnd = query.find(" ", fromPos + 1);

	string tableName = query.substr(fromPos, tableNamePosEnd - fromPos);
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

		if (wherePos == -1) {
			indexes = allIndexes(table);
		}
		else {
			indexes = whereFilter(table, whereQuery);
		}
	}

	searchResult.indexes = indexes;
	return searchResult;
}



vector<int> whereFilter(Table* table, string whereQuery) {

	vector<int> indexes;

	vector<WhereCondition*> conditions;
	string delimiterAND = "AND";
	string delimiterOR = "OR";

	int pos = 0;
	int pos1 = -1;
	int pos2 = -1;
	string conditon;

	WhereCondition* whereCondition = new WhereCondition();

	while ((pos1 = whereQuery.find(delimiterAND)) != -1 || (pos2 = whereQuery.find(delimiterOR)) != -1) {

		pos1 = whereQuery.find(delimiterAND);
		pos2 = whereQuery.find(delimiterOR);

		if (whereCondition->condition != "")
			whereCondition = new WhereCondition();

		if (pos1 == -1) {
			pos = pos2;
			whereCondition->separator = delimiterOR;
		}
		else if (pos2 == -1) {
			pos = pos1;
			whereCondition->separator = delimiterAND;
		}
		else if (pos1 < pos2) {
			whereCondition->separator = delimiterAND;
			pos = pos1;
		}
		else {
			whereCondition->separator = delimiterOR;
			pos = pos2;
		}

		conditon = whereQuery.substr(0, pos);
		Utilities::EraseWhitespaces(conditon);

		if (whereCondition->condition == "") {
			whereCondition->condition = conditon;
			conditions.push_back(whereCondition);
		}

		if (pos == pos1)
			whereQuery.erase(0, pos + delimiterAND.length());
		else if (pos == pos2)
			whereQuery.erase(0, pos + delimiterOR.length());
	}
	Utilities::EraseWhitespaces(whereQuery);

	whereCondition = new WhereCondition();
	whereCondition->condition = whereQuery;
	conditions.push_back(whereCondition);

	if (conditions.size() > 0) {
		indexes = conditionIndexes(conditions[0], table);
	}

	for (int i = 0; i < conditions.size(); i++) {
		if (conditions[i]->separator == "")
			return indexes;
		else if (conditions[i]->separator == "OR") {
			indexes = concatenateVectors(indexes, conditionIndexes(conditions[i+1],table));
		}
		else if (conditions[i]->separator == "AND") {
			indexes = getCommonPart(indexes, conditionIndexes(conditions[i+1], table));
		}
	}

	return indexes;
}



vector<int> getCommonPart(vector<int> A, vector<int> B) {
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	vector<int> result;

	for (auto& index : A) {
		if (std::find(B.begin(), B.end(), index) != B.end())
		{
			result.push_back(index);
		}
	}

	return result;
}

vector<int> concatenateVectors(vector<int> A, vector<int> B) {
	vector<int> AB;

	AB.reserve(A.size() + B.size()); // preallocate memory
	AB.insert(AB.end(), A.begin(), A.end());
	AB.insert(AB.end(), B.begin(), B.end());

	sort(AB.begin(), AB.end());
	auto last = std::unique(AB.begin(), AB.end());
	AB.erase(last, AB.end());

	return AB;
}

vector<int>  conditionIndexes(WhereCondition* condition, Table* table) {

	vector<int> indexes;

	int morePos = condition->condition.find(">");
	int lessPos = condition->condition.find("<");
	int equalPos = condition->condition.find("=");
	int notEqualPos = condition->condition.find("!");
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
	else if (notEqualPos != -1) {
		signPos = notEqualPos;
		operatorSign = '!';
	}

	int columnNameLength = condition->condition.find(operatorSign);
	string columnName = condition->condition.substr(0, columnNameLength);
	Utilities::EraseWhitespaces(columnName);

	//int endPos = whereQuery.find("END");
	string value = condition->condition.substr(signPos + 1);

	Column* column = table->getColumn(columnName);

	if (column == nullptr) {
		cout << "Error can't find column named: " + columnName << endl;
		return indexes;
	}

	vector<Cell> cells = column->getCells();

	/*if (column->getType() != "Number") {
		cout << "Error inappropiate column type" << endl;
	}*/

	for (int i = 0; i < cells.size(); i++)
	{
		Cell cell = cells[i];
		string cellValue = cell.getValue();

		switch (operatorSign)
		{
		case '>':

			if (column->getType() == "Number") {
				if (stoi(cellValue) > stoi(value)) {
					indexes.push_back(i);
				}
			}
			else {
				if (cellValue > value) {
					indexes.push_back(i);
				}
			}

			break;
		case '<':
			if (column->getType() == "Number") {
				if (stoi(cellValue) < stoi(value)) {
					indexes.push_back(i);
				}
			}
			else {
				if (cellValue < value) {
					indexes.push_back(i);
				}
			}
			break;
		case '=':
			if (cellValue == value) {
				indexes.push_back(i);
			}
			break;
		case '!':
			if (cellValue != value) {
				indexes.push_back(i);
			}
		break;

		default:
			break;
		}
	}

	return indexes;
}

vector<int> allIndexes(Table* table) {
	vector<int> result;
	auto rows = table->getRows();

	for (int i = 0; i < rows.size(); i++) {
		result.push_back(i);
	}

	return result;
}