#pragma once
#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>

class Column;

using namespace std;
class Cell
{
	string value;
public:
	Cell(string value, Column *column);
	Cell() {}
	string getValue() const;
	Column* column;
	bool operator > (const Cell& cell) const;
	bool operator < (const Cell& cell) const;
private:
	bool isValueFitIntoType();
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("value", value);
		ar & make_nvp("column", column);
	}
};