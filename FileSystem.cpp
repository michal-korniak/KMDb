#include "FileSystem.h"
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

const string FileSystem::path = "/home/teaper/KMDb/";

void FileSystem::save(const Database& s) {
	// make an archive
	boost::filesystem::create_directory(path);
	ofstream ofs(path + s.getName() + ".xml");
	assert(ofs.good());
	boost::archive::xml_oarchive oa(ofs);
	oa << BOOST_SERIALIZATION_NVP(s);
}

Database FileSystem::restore(string filename) {
	// open the archive
	Database s;
	ifstream ifs(path + filename);
	assert(ifs.good());
	boost::archive::xml_iarchive ia(ifs);

	// restore the schedule from the archive
	ia >> BOOST_SERIALIZATION_NVP(s);
	for(auto& table: s.getTables()) {
		for (auto& column : table.getColumns())
			column.table = &table;
	}
	for(auto& )
	return s;
}

vector<string> FileSystem::getAllDbNames() {

	vector<string> names;
	boost::filesystem::path p(path);
	
	if ( exists(p) ) 
	{
    	directory_iterator end_itr;
		// cycle through the directory
		for (directory_iterator itr(p); itr != end_itr; ++itr)
		{
			string current_file = itr->path().stem().string();
			names.push_back(current_file);
		}
	}
	return names;
}
