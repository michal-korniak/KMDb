#include "stdafx.h"
#include "FileSystem.h"
#include <windows.h>
#include <iostream>
#include <filesystem>

using namespace std;

const string FileSystem::path = "Databases/";

void FileSystem::save(const Database& s) {
	// make an archive
	CreateDirectory("Databases", NULL);
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
	return s;
}

vector<string> FileSystem::getAllDbNames() {

	vector<string> names;
	string search_path = path + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				string nameWithExt = fd.cFileName;
				string nameWithoutExt = nameWithExt.substr(0, nameWithExt.rfind("."));
				names.push_back(nameWithoutExt);
			}
		}
		while (::FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return names;
}
