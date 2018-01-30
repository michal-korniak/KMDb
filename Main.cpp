#include "stdafx.h"
#include "ColumnTypes.h"
#include "Database.h"
#include <iostream>
#include "FileSystem.h"
#include "SelectHelper.h"
using namespace std;

Database db;
int getInput();
void displayMainMenu();
void displayDatabaseMenu();
void displayTablesMenu();
void displayTableMenu(Table& table);
void displayNewTableMenu(Table& table);

void displayAddTableDialog();
void displayAddRowDialog(Table& table);
bool displayCreateDatabaseDialog();
bool displayLoadDatabaseDialog();
void enterQueryDialog();

void displayTable(Table& table, int numberOfRows = INT_MAX);
void saveChanges();
void displayAddColumnDialog(Table& table);
void displayRemoveColumnDialog(Table& table);


int main() {
	//displayMainMenu();
	Database db("NowaBaza");
	db.addTable(Table("Pracownicy"));
	db.addTable(Table("Studenci"));

	Table* studentsTable = db.getTable("Studenci");
	auto col1= Column("Imie", ColumnTypes::String);
	auto col2 = Column("Nazwisko", ColumnTypes::String);
	auto col3 = Column("Rok", ColumnTypes::Number);
	studentsTable->addColumn(col1);
	studentsTable->addColumn(col2);
	studentsTable->addColumn(col3);
	
	auto& studColumns = studentsTable->getColumns();
	Row row1 = Row().addCell(Cell("Piotr",&studColumns[0])).addCell(Cell("Adamiak", &studColumns[1])).addCell(Cell("2", &studColumns[2]));
	Row row2 = Row().addCell(Cell("Michal", &studColumns[0])).addCell(Cell("Kowalski", &studColumns[1])).addCell(Cell("1", &studColumns[2]));
	studentsTable->addRow(row1);
	studentsTable->addRow(row2);

	Table*  pracownicyTable = db.getTable("Pracownicy");
	auto col4 = Column("column1", ColumnTypes::Number);
	auto col5 = Column("column2", ColumnTypes::String);
	pracownicyTable->addColumn(col4);
	pracownicyTable->addColumn(col5);
	auto& pracColumns = pracownicyTable->getColumns();
	Row row3 = Row().addCell(Cell("10", &pracColumns[0])).addCell(Cell("NULL_10", &pracColumns[1]));
	Row row4 = Row().addCell(Cell("3", &pracColumns[0])).addCell(Cell("NULL_3", &pracColumns[1]));
	Row row5 = Row().addCell(Cell("0", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	Row row6 = Row().addCell(Cell("1", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	Row row7 = Row().addCell(Cell("2", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	pracownicyTable->addRow(row3);
	pracownicyTable->addRow(row4);
	pracownicyTable->addRow(row5);
	pracownicyTable->addRow(row6);
	pracownicyTable->addRow(row7);
	cout << "STAN POCZATKOWY: " << endl;
	displayTable(*pracownicyTable);
	cout << endl;
	cout << "ZAPYTANIE: ";
	cout << "SELECT column1,column2 FROM Pracownicy WHERE column1>1 STDEC column1 END" << endl;
	cout << "WYNIK:" << endl;
	auto table = SelectHelper::Select(&db, "SELECT column1,column2 FROM Pracownicy WHERE column1>1 STDEC column1 END");
	displayTable(*table);
	cout << endl;
	cout << "ZAPYTANIE: ";
	string query = "SELECT column1,column2 FROM Pracownicy WHERE column1=10 OR column2=0 END";
	cout << query << endl;
	cout << "WYNIK:" << endl;
	auto table1 = SelectHelper::Select(&db, query);
	displayTable(*table1);
	cout << endl;


	//SelectHelper::Select(&db, "SELECT column1,column2 FROM Pracownicy WHERE column1>5 AND column1<12 OR column2=0 OR column1=3 END");
	//SelectHelper::Select(&db, "SELECT column1,column2 FROM Pracownicy WHERE column1!5 ORDER BY column1 END");

	system("pause");


}

void displayMainMenu() {

	int choice = 0;

	do {
		system("cls");

		cout << "Main Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Create Database\n";
		cout << "2 - Load Database\n";
		cout << "3 - Quit\n";
		cout << "Selection: ";

		choice = getInput();
		switch (choice) {
		case 1:
			if(displayCreateDatabaseDialog())
				displayDatabaseMenu();
			break;
		case 2:
			if(displayLoadDatabaseDialog())
				displayDatabaseMenu();
			break;
		case 3:
			break;

		default:
			break;
		}
	}
	while (choice != 3);

}

void displayDatabaseMenu() {
	bool close = false;
	do {
		system("cls");

		cout << "Database Menu\n";
		cout << "Database: " << db.getName() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Show Tables\n";
		cout << "2 - Add Table\n";
		cout << "3 - Enter Select Query\n";
		cout << "4 - Save Changes\n";
		cout << "5 - Back To Main Menu\n";
		cout << "Selection: ";
		int choice = 0;
		choice = getInput();
		switch (choice) {
		case 1:
			displayTablesMenu();
			break;
		case 2:
			displayAddTableDialog();
			break;
		case 3:
			enterQueryDialog();
			continue;
		case 4:
			saveChanges();
			break;
		case 5:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);

}

void displayTablesMenu() {
	do {
		system("cls");
		cout << "Database: " << db.getName() << endl;
		cout << "Tables:\n\n";
		int i = 0;
		for (auto& table : db.getTables()) {
			cout << table.getName() << " (" << table.getRows().size() << " records)" << endl;
		}
		cout << endl;
		cout << "Enter name of table if you want to display table menu." << endl;
		cout << "Enter \"q\" if you want to return to previous menu." << endl;
		cout << "Selection: ";
		string choice;
		cin >> choice;
		if (choice == "q")
			return;
		for (auto& table : db.getTables()) {
			if (choice == table.getName()) {
				displayTableMenu(table);
				break;
			}
		}
	}
	while (true);
}

void displayTableMenu(Table& table) {

	bool close = false;
	do {
		system("cls");
		cout << "Table name: " << table.getName() << endl;
		cout << "Number of records: " << table.getRows().size() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Show Records\n";
		cout << "2 - Add Record\n";
		cout << "3 - Back To Previous Menu\n";
		cout << "Selection: ";
		int choice = 0;
		choice = getInput();
		switch (choice) {
		case 1:
			system("cls");
			displayTable(table);
			system("pause");
			break;
		case 2:
			displayAddRowDialog(table);
		case 3:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);
}

void displayNewTableMenu(Table& table) {

	int choice = 0;
	bool close = false;
	do {
		system("cls");
		cout << "Welcome to the Column Managment Menu" << endl;
		cout << "Database: " << db.getName() << endl;
		cout << "Table: " << table.getName() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Add Column\n";
		cout << "2 - Remove Column\n";
		cout << "3 - Back To Previous Menu\n";
		cout << "Selection: ";
		choice = getInput();
		switch (choice) {
		case 1:
			displayAddColumnDialog(table);
			break;
		case 2:
			displayRemoveColumnDialog(table);
			break;
		case 3:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);
}

bool displayCreateDatabaseDialog() {
	system("cls");
	while (true) {
		cout << "Enter name for your database: ";
		string name;
		cin >> name;
		try {
			db = Database(name);
			return true;
		}
		catch (runtime_error error) {
			cout << "Database with this name already exists" << endl;
			cout << "Try again" << endl;
		}
	}
}

bool displayLoadDatabaseDialog() {
	system("cls");
	int i = 0;
	auto dbNames = FileSystem::getAllDbNames();
	if(dbNames.size()==0) {
		cout << "No databases in system."<<endl;
		system("pause");
		return false;
	}
	for (auto db :dbNames ) {
		cout << ++i << " - " << db << endl;
	}

	bool loaded = false;
	while (!loaded) {
		cout << "Enter name of database that you want to load (q to back): ";
		string name;
		cin >> name;
		if (name == "q")
			return false;
		bool found = false;
		for (auto db : dbNames) {
			if (db == name) {
				found = true;
				break;
			}
		}
		if (found != true) {
			cout << "Database with this name doesn't exists" << endl;
			cout << "Try again" << endl;
			continue;
		}
		db = FileSystem::restore(name + ".xml");
		loaded = true;
	}
	return true;

}

void displayAddTableDialog() {
	bool addedTable = false;
	system("cls");
	cout << "Enter name of new table." << endl;
	cout << "Enter \"q\" if you want to return to previous menu." << endl;
	do {
		cout << "Name: ";
		string name;
		cin >> name;
		if (name == "q")
			return;
		try { db.addTable(Table(name)); }
		catch (runtime_error ex) {
			cout << "Table with this name already exists in database" << endl;
			cout << "Try again." << endl;
			continue;
		}

		displayNewTableMenu(*db.getTable(name));
		addedTable = true;
	}
	while (!addedTable);


}

void displayAddRowDialog(Table& table) {
	system("cls");
	cout << "Enter values" << endl;
	Row newRow;
	for (auto& column : table.getColumns()) {
		bool done = true;
		do {
			cout << column.getName() << " (" << column.getType() << "): ";
			string value;
			cin >> value;
			try {
				Cell cell(value, &column);
				newRow.addCell(cell);
			}
			catch (runtime_error error) {
				done = false;
				cout << error.what() << endl;
				cout << "Try again!" << endl;
			}

		} while (!done);
	}
	table.addRow(newRow);
	cout << "Added!" << endl;
	system("pause");
}

void displayAddColumnDialog(Table& table) {

	system("cls");

	const ColumnType* type = NULL;
	bool validType;


	cout << "Choose type\n";
	cout << "1 - Number\n";
	cout << "2 - String\n";

	do {
		validType = true;
		cout << "Selection: ";
		int selection = getInput();
		switch (selection) {
		case 1:
			type = &ColumnTypes::Number;
			break;
		case 2:
			type = &ColumnTypes::String;
			break;
		default:
			cout << "Wrong selection." << endl;
			cout << "Try again." << endl;
			validType = false;
		}
	}
	while (!validType);

	string name;
	bool validName = false;
	while (!validName) {
		cout << "Enter name for column: ";
		cin >> name;
		try {
			Column column(name, *type);
			table.addColumn(column);
			validName = true;
		}
		catch (runtime_error error) {
			cout << "Column with this name already exists." << endl;
			cout << "Try again." << endl;
		}
	}
}

void displayRemoveColumnDialog(Table& table) {
	system("cls");
	int i = 0;
	for (auto column : table.getColumns()) {
		cout << ++i << " - " <<  column.getName() << " (" << column.getType() << ")";
		
	}

	cout << "Enter name of column that you want to remove: ";
	string name;
	cin >> name;
	bool found = false;
	int index = -1;
	for (auto column :table.getColumns()) {
		index++;
		if (column.getName() == name) {
			found = true;
			break;
		}
	}
	if (found != true) {
		cout << "Column with this name doesn't exist." << endl;
		system("pause");
	}
	else {
		table.getColumns().erase(table.getColumns().begin()+index);
		cout << "Column deleted!" << endl;
		system("pause");
	}

}

void displayTable(Table& table, int numberOfRows) {
	for (auto& column : table.getColumns()) {
		cout << "|";
		cout << column.getName() << "(" << column.getType() << ")";
	}
	if (table.getColumns().size() != 0)
		cout << "|";
	cout << endl;
	int i = 0;
	for (auto rows : table.getRows()) {
		if (i++ < numberOfRows) {
			cout << "|";
			for (auto cell : rows.getCells())
				cout << cell.getValue() << "|";
		}
		cout << endl;
	}
	cout << endl;
	cout.width();
}

void enterQueryDialog() {
	system("cls");
	cout << "Enter query:" << endl;
	string query;
	cin >> query;
	SelectHelper::Select(&db, query);
}

void saveChanges() { FileSystem::save(db); }

int getInput() {
	int choice;
	cin >> choice;
	return choice;
}
