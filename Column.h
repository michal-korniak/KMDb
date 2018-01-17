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
	//vector<Cell> cells;
public:
	Column(const string& name, ColumnType type);
	vector<Cell> getCells();
	//Column& addCell(Cell cell);
	string getName() const;
	string getType() const;
	Table* table;
	int index;
private:
	Column() {}
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("name", name);
		ar & make_nvp("type", type);
	}
};


