#include "Utilities.h"

#include <iostream>
#include <algorithm>
using namespace std;

void Utilities::EraseWhitespaces(string & text)
{
	text.erase(remove_if(text.begin(), text.end(), isSpace), text.end());

	//remove_if(text.begin(), text.end(), isspace);
	//text.erase(remove(text.begin(), text.end(), ''), text.end());
	//text.erase(remove(text.begin(), text.end(), ' '), text.end());
}
int Utilities::isSpace(int ch)
{
	return isspace(ch);
}

