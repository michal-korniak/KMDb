#pragma once
#include <string>

using namespace std;
class Cell
{
	string value;
public:
	Cell(string value);
	string getValue() const;
};