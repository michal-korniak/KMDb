#pragma once
#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>

using namespace std;
class Cell
{
	string value;
public:
	Cell(string value);
	string getValue() const;
private:
	Cell() {}
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("value", value);
	}
};