#pragma once
#include "Database.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
class FileSystem
{
private:
	static const string path;
public:
	static void save(const Database& s);
	static Database restore(string filename);
	static vector<string> getAllDbNames();

};
