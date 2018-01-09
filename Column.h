#pragma once
#include "Cell.h"
#include "ColumnType.h"
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;
class Column
{
	string name;
	string type;
public:
	Column(const string& name, ColumnType type);
	string getName() const;
	string getType() const;
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


