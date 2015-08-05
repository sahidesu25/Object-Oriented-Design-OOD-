#ifndef FILESEARCH_H
#define FILESEARCH_H
///////////////////////////////////////////////////////////////////////
// FileSearch.h -Searches the specified word in the DataStore        //
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









#include"../DataStore/DataStore.h"
//#include "../FileManager/FileSystem.h"
#include "../FileManager/FileManager.h"

#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;
class FileSearch
{
public:
	using iter = DataStore::iterator;
	using Path = std::string;
	using Paths = std::set < Path > ;
	using PathIter = Paths::iterator;
	using ListofIter = std::list < PathIter > ;
	using File = std::string;
	using Store = std::map < File, ListofIter > ;
	using iterator = Store::iterator;
	//constructor which initializes its member variables
	FileSearch(DataStore &ds) :store(ds)
	{

	}
	//function to get all the files that were identified in the searchresult
	std::multimap<std::string, std::string> get_files_found()
	{
		return filesfound;
	}
//function to search the specified text given in the catlouge
	std::multimap<std::string, std::string> search_filecatlog(std::string search_word)
	{
		if (filesfound.size() != 0)
		{
			filesfound.clear();
		}
		bool isFound = 0;
		iter it;
		cout << "-------------------------------------------------------------------------" << endl << endl;
		cout << "Searching for word" << " \t" << "*" << search_word << "*" << "\t" << "\t" << "in the file catlouge" << endl << endl;
		cout << "-------------------------------------------------------------------------" << endl << endl;

		for (auto it = store.begin(); it != store.end(); it++)
		{

			for (ListofIter::const_iterator list_iter = it->second.begin(); list_iter != it->second.end(); list_iter++)
			{
				int offset;
				std::string line;
				std::ifstream file;
				file.open(FileSystem::Path::fileSpec((*(*list_iter)), it->first), ios::in);
				if (file.is_open())
				{
					while (!file.eof())
					{
						getline(file, line);
						if ((offset = line.find(search_word, 0)) != string::npos)
						{
							filesfound.insert(std::pair<std::string, std::string>(it->first, (*(*list_iter))));
							break;
							cout << std::endl;

						}
					}
					file.close();
				}
				else
				{
					cout << endl << "Can't open the file" << it->first << std::endl;
				}
			}
		}
		return filesfound;
	}


//function to search the file catlouge to retrive the files which has user specified word and patterns
	std::multimap<std::string, std::string> search_filecatlog_(std::string search_word,std::vector<std::string>pattern_search)
	{
		if (filesfound.size() != 0)
			filesfound.clear();
		bool isFound = 0;
		iter it;
		cout << "-------------------------------------------------------------------------" << endl << endl;
		cout << "Searching for word" << " \t" << "*" << search_word << "*" << "\t" << "\t" << "in the file catlouge" << endl << endl;
		cout << "-------------------------------------------------------------------------" << endl << endl;

		for (auto it = store.begin(); it != store.end(); it++)
		{
			bool check = false;
			int found_for_path;
			for (auto i : pattern_search)
			{
				found_for_path = it->first.find(i);
				if ((found_for_path != std::string::npos))
				{
					check = true;
					break;
				}
			}
			if (check)
			{
				for (ListofIter::const_iterator list_iter = it->second.begin(); list_iter != it->second.end(); list_iter++)
				{
					int offset;
					std::string line;
					std::ifstream file;
					file.open(FileSystem::Path::fileSpec((*(*list_iter)), it->first), ios::in);
					if (file.is_open())
					{
						while (!file.eof())
						{
							getline(file, line);
							if ((offset = line.find(search_word, 0)) != string::npos)
							{
								filesfound.insert(std::pair<std::string, std::string>(it->first, (*(*list_iter))));
								break;
								cout << std::endl;

							}
						}
						file.close();
					}
					else
					{
						cout << endl << "Can't open the file" << it->first << std::endl;
					}
				}


			}

		}
			
		return filesfound;
	}
	
	// function to search a word from the file catlogue. This returns a list of files that has the search word in it.
	
private:
	std::multimap<std::string,std::string> filesfound;
	DataStore &store;
};

#endif 
