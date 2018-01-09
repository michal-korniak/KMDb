#pragma once
#include <string>
#include <vector>
#include "Column.h"
#include "Row.h"
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;
class Table
{
	string name;
	vector<Column> columns;
	vector<Row> rows;
public:
	Table(const string& name);
	string getName() const;
	void addColumn(const Column& column);
	void verifyCompatibiltyWithType(const Column& column, const Cell& cell) const;
	void addRow(Row row);
	vector<Row> getRows() const;
	vector<Column> getColumns() const;
private:
	Table() {}
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("name", name);
		ar & make_nvp("columns", columns);
		ar & make_nvp("rows", rows);
	}
};
