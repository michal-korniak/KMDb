#pragma once
#include <string>
#include <vector>
#include "Table.h"
#include <boost/serialization/access.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;

class Database
{
	string name;
	vector<Table> tables;
public:
	Database();
	Database(const string& name);
	void addTable(const Table& newTable);
	Table* getTable(const string& name);
	string getName() const;
	vector<Table>& getTables();
private:
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("name", name);
		ar & make_nvp("tables", tables);
	}
};

