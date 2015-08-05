///////////////////////////////////////////////////////////////////////
// FileSearch.cpp -Searches the specified word in the DataStore        //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: File Catlogue, Project #1, Spring 2015               //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//* Gets the search word to be searched from teh Executive and searches for that word in 
//* all the files in the Datastore and gets the filenames along with their paths back to the Executive
//*
//*
//* Required Files
//*--------------------
//* FileMgr.h,FileMgr.cpp,DataStore.cpp and DataStore.h
//*
//* Maintaiance History
//*--------------------
//* -first release








#include<iostream>
#include"FileSearch.h"
#include<string>
#include "../DataStore/DataStore.h"

#ifdef TEST_FILESEARCH
int main()
{

DataStore ds;
	FileSearch fs(ds);
	FileMgr fm(".", ds);
	/*fm.addpattern("*.cpp");
    std::multimap<std::string, std::string> file_search_list;
	fs.search_filecatlog("bool recurse");
	file_search_list=fs.get_files_found();
	cout << endl << "The search result: " << std::endl;
	for (multimap<std::string, std::string>::iterator it = file_search_list.begin(); it != file_search_list.end(); ++it) {
		cout << "Occurred in the file: " << it->first << std::endl << "\t" << "path:" << it->second << endl << endl << endl;
	}*/

	
	return 0;
}

#endif