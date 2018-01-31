#pragma once
#include <string>
using namespace std;
class ColumnType
{
private:
	string type;
	ColumnType(){}
	ColumnType(string type);
public:
	friend class ColumnTypes;
	string getType() const;
	static ColumnType convertFromString(string st);
};
