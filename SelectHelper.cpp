#include "SelectHelper.h"
#include <iostream>
#include "Utilities.h"
#include "SearchHelper.h"


using namespace std;

const string selectStatement = "SELECT";
const string fromStatement = "FROM";
const string whereStatement = "WHERE";
const string endStatment = "END";
const string orderStatement = "ST"; 
const string orderDescStatement = "STDEC";

Table* createResultTable(Table* table, vector<int> indexes, vector<Column*> columns);
vector<Column*> initializeColumns(Table* table, vector<string> columnNames);

Table* SelectHelper::Select(Database * database, string query)
{
	int selectPos = query.find(selectStatement);

	int fromPos = query.find(fromStatement);
	int wherePos = query.find(whereStatement);
	int endPos = query.find(endStatment);
	int fromSelectLength = fromPos - (selectPos + selectStatement.length());
	int whereFromLength = wherePos - (fromPos + fromStatement.length());
	int endWhereLength = endPos - (wherePos + whereStatement.length());

	int tempLength = selectPos + selectStatement.length();
	string columnsString = query.substr(tempLength, fromSelectLength);

	vector<string> columnNames;
	string delimiter = ",";

	int pos = 0;
	string columnName;
	while ((pos = columnsString.find(delimiter)) != std::string::npos) {
		columnName = columnsString.substr(0, pos);
		Utilities::EraseWhitespaces(columnName);
		columnNames.push_back(columnName);
		columnsString.erase(0, pos + delimiter.length());
	}

	Utilities::EraseWhitespaces(columnsString);
	columnNames.push_back(columnsString);


	auto searchResult = SearchHelper::Search(database, query);
	auto columns = initializeColumns(searchResult.table,columnNames);
	Table* result = createResultTable(searchResult.table, searchResult.indexes, columns);

	if (query.find(orderStatement) != -1 || query.find(orderDescStatement) != -1) {
		int orderStatementPos = query.find(orderStatement);
		string columnName;

		int columnNameBegPos = query.find(" ", orderStatementPos + 1);
		int columnNameEndPos = query.find(" ", columnNameBegPos + 1);

		string columnNameOrder = query.substr(columnNameBegPos, columnNameEndPos - columnNameBegPos);
		Utilities::EraseWhitespaces(columnNameOrder);

		int orderDescPos = query.find(orderDescStatement);

		bool sortDec = false;

		if (orderDescPos != -1) {
			sortDec = true;
		}

		result->SortTable(columnNameOrder, sortDec);

	}

	//fromPos = query.find(" ", fromPos + 1);
	//int tableNamePosEnd = query.find(" ", fromPos + 1);

	//string tableName = query.substr(fromPos, tableNamePosEnd - fromPos);
	//tableName.erase(remove(tableName.begin(), tableName.end(), ' '), tableName.end());

	return result;
}

Table* createResultTable(Table* table, vector<int> indexes, vector<Column*> columns) {

	Table* resultTable = new Table("result");
	//Table resultTable("result");

	vector<Row> tableRows;
	tableRows = table->getRows();
	vector<Row> resultTableRows;
	vector<int> columnIndexes;

	for (auto& index : indexes) {
		resultTableRows.push_back(tableRows[index]);
	}

	for (auto& column : columns) {
		Column newColumn(column->getName(), 
			ColumnType::convertFromString(column->getType()));
		newColumn.index = column->index;
		resultTable->addColumn(newColumn);
		columnIndexes.push_back(newColumn.index);
	}

	vector<Row> newRows;

	for (auto& row : resultTableRows) {
		vector<Cell> cells = row.getCells();
		Row newRow;

		for (int i = 0; i < cells.size(); i++) {

			if (find(columnIndexes.begin(), columnIndexes.end(), i) != columnIndexes.end()) {
				newRow.addCell(cells[i]);
			}
		}
		newRows.push_back(newRow);
	}

	for (auto& row : newRows) {
		resultTable->addRow(row);
	}

	return resultTable;
}

vector<Column*> initializeColumns(Table* table, vector<string> columnNames) {

	vector<Column*> columns;

	for (auto& columnName : columnNames)
	{
		auto column = table->getColumn(columnName);
		if (column == nullptr) {
			cout << "Column does not exist " + columnName << endl;;
		}
		else {
			columns.push_back(column);
		}
	}

	return columns;
}