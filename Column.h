#pragma once
#include <string>
#include "Cell.h"
#include <vector>
#include "ColumnType.h"
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;

class Table;

class Column
{
	string name;
	string type;
	string tableName;
	//vector<Cell> cells;
public:
	Column(const string& name, ColumnType type);
	Column() {}
	vector<Cell> getCells();
	//Column& addCell(Cell cell);
	string getName() const;
	string getType() const;
	Table* table;
	int index;
private:
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("name", name);
		ar & make_nvp("table", table);
		ar & make_nvp("type", type);
		ar & make_nvp("index", index);
	}
};


