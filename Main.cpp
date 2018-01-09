#include "stdafx.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <iostream>
#include "ColumnTypes.h"
#include "Database.h"
using namespace std;
void save(const Database &s, const char * filename) {
	// make an archive
	std::ofstream ofs(filename);
	assert(ofs.good());
	boost::archive::xml_oarchive oa(ofs);
	oa << BOOST_SERIALIZATION_NVP(s);
}
void restore(Database &s, const char * filename)
{
	// open the archive
	std::ifstream ifs(filename);
	assert(ifs.good());
	boost::archive::xml_iarchive ia(ifs);

	// restore the schedule from the archive
	ia >> BOOST_SERIALIZATION_NVP(s);
}

int main()
{
	Database db("NowaBaza");
	db.addTable(Table("Pracownicy"));
	db.addTable(Table("Studenci"));

	Table& studentsTable=db.getTable("Studenci");
	studentsTable.addColumn(Column("Imie",ColumnTypes::String));
	studentsTable.addColumn(Column("Nazwisko", ColumnTypes::String));
	studentsTable.addColumn(Column("Rok", ColumnTypes::Number));

	Row row1 = Row().addCell(Cell("Piotr")).addCell(Cell("Adamiak")).addCell(Cell("2"));
	Row row2 = Row().addCell(Cell("Michal")).addCell(Cell("Kowalski")).addCell(Cell("1"));
	studentsTable.addRow(row1);
	studentsTable.addRow(row2);

	save(db, "db.xml");
	//W tym momencie będzie sprawdzali nazwy plikow i w ten sposob nazwiemy swoja baze
	Database db2("NowaBaza");
	restore(db2, "db.xml");


	
}

