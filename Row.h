#pragma once
#include "Cell.h"
#include <vector>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;
class Row
{
	vector<Cell> cells;
public:
	Row& addCell(Cell cell);
	int numberOfCells() const;
	Cell& operator[](const int index);
	vector<Cell> getCells() const;
private:
	friend class boost::serialization::access;
	template<class archive>
	void serialize(archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("cells", cells);
	}
};
