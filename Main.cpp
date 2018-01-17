#include "stdafx.h"
#include "ColumnTypes.h"
#include "Database.h"
#include <iostream>
#include "FileSystem.h"
using namespace std;

Database db;
int getInput();
void displayMainMenu();
void displayCreateDatabaseDialog();
void displayLoadDatabaseDialog();
void displayDatabaseMenu();
void displayTableManu();
void showTable(const Table& table, int numberOfRows = INT_MAX);
void displayAddTableDialog();
void enterQueryDialog();
void saveChanges();
void displayNewTableMenu(Table& table);
void addColumnDialog(Table& table);
void removeColumnDialog(Table& table);


int main() {
	displayMainMenu();
	//db=FileSystem::restore("NowaBaza.xml");
	//db.addTable(Table("Nauczyciele"));
	//Table& teachersTable=db.getTable("Nauczyciele");
	//teachersTable.addColumn(Column("Imie",ColumnTypes::String));
	//teachersTable.addColumn(Column("Nazwisko", ColumnTypes::String));
	//teachersTable.addColumn(Column("Rok", ColumnTypes::Number));

	//Row row1 = Row().addCell(Cell("Piotr")).addCell(Cell("Adamiak")).addCell(Cell("2"));
	//Row row2 = Row().addCell(Cell("Michal")).addCell(Cell("Kowalski")).addCell(Cell("1"));
	//studentsTable.addRow(row1);
	//studentsTable.addRow(row2);

	//FileSystem::save(db);
	////W tym momencie będzie sprawdzali nazwy plikow i w ten sposob nazwiemy swoja baze
	//Database db2("NowaBaza");
	//FileSystem::restore(db2, "db.xml");


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
			displayCreateDatabaseDialog();
			displayDatabaseMenu();
			break;
		case 2:
			displayLoadDatabaseDialog();
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
			displayTableManu();
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

void displayTableManu() {
	do {
		system("cls");
		cout << "Database: " << db.getName() << endl;
		cout << "Tables:\n\n";
		int i = 0;
		for (auto table : db.getTables()) { showTable(table, 3); }
		cout << "Enter name of table if you want to display all records." << endl;
		cout << "Enter \"q\" if you want to return to previous menu." << endl;
		cout << "Selection: ";
		string choice;
		cin >> choice;
		if (choice == "q")
			return;
		for (auto table : db.getTables()) {
			if (choice == table.getName()) {
				system("cls");
				showTable(table);
				system("pause");
			}
		}
	}
	while (true);
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
			addColumnDialog(table);
			break;
		case 2:
			removeColumnDialog(table);
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

void displayCreateDatabaseDialog() {
	bool created = false;
	system("cls");
	while (!created) {
		cout << "Enter name for your database: ";
		string name;
		cin >> name;
		try {
			db = Database(name);
			created = true;
		}
		catch (runtime_error& error) {
			cout << "Database with this name already exists" << endl;
			cout << "Try again" << endl;
		}
	}
}

void displayLoadDatabaseDialog() {
	int i = 0;
	for (auto db : FileSystem::getAllDbNames()) {
		system("cls");
		cout << ++i << " - " << db << endl;
	}

	bool loaded = false;
	while (!loaded) {
		cout << "Enter name of database that you want to load: ";
		string name;
		cin >> name;
		bool found = false;
		for (auto db : FileSystem::getAllDbNames()) {
			if (db == name) {
				found = true;
				break;
			}
		}
		if (found != true) {
			cout << "Database with this name doesn't exists" << endl;
			cout << "Try again" << endl;
		}
		db = FileSystem::restore(name + ".xml");
		loaded = true;
	}

}

void displayAddTableDialog() {
	bool addedTable = false;
	system("cls");
	cout << "Enter name of new table." << endl;
	cout << "Enter \"q\" if you want to return to previous menu." << endl;
	do {
		cout << "Name:";
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
		displayNewTableMenu(db.getTable(name));
		addedTable = true;
	}
	while (!addedTable);


}

void addColumnDialog(Table& table) {

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
			table.addColumn(Column(name, *type));
			validName = true;
		}
		catch (runtime_error& error) {
			cout << "Column with this name already exists." << endl;
			cout << "Try again." << endl;
		}
	}
}

void removeColumnDialog(Table& table) {
}

void enterQueryDialog() {
}

void saveChanges() { FileSystem::save(db); }

void showTable(const Table& table, int numberOfRows) {
	cout << table.getName() << endl;
	for (auto column : table.getColumns()) {
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

int getInput() {
	int choice;
	cin >> choice;
	return choice;
}
