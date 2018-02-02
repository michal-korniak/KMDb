#pragma once
using namespace std;
#include <string>

class Utilities
{
public:
	static void EraseWhitespaces(string& text);
private:
	static int isSpace(int ch);
};

