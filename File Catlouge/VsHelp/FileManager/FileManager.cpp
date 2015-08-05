//FileMgr.cpp

///////////////////////////////////////////////////////////////////////
// FileMgr.cpp -It proccesses all the command line arguments and      //
//             retrives all the files rooted from the specified       //
//             directory using the functions in the FileSystem project//
// ver 1.0                                                            //
// Language:    Visual C++, Visual Studio 2013                        //
// Platform:    Lenovo Y40, Win8.1                                    //
// Application: File Catlogue, Project #1, Spring 2015                //
// Author:      Sahithi Lakshmi Desu, Syracuse University             //
//              (650)-445-8606 sldesu@syr.edu                         //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//* Processes all the command line arguments and pass it to the Executive. 
//* Finds all the files that are rooted from the specified path and saves it to the datastore
//*
//* Required Files
//*--------------------
//*  File System.cpp, FileSystem.h,DataStore.cpp and DataStore.h
//*
//* Maintaiance History
//*--------------------
//* -first release





#include "FileManager.h"
#include "../FileSearch/FileSearch.h"
#include "../DataStore/DataStore.h"
#include "../DataStore/DataStore.cpp"
#include<iostream>
// Adds patterns that were specified to the patterns vector 
void FileMgr::addpattern(const std::string& patt)
{

	patterns_.push_back(patt);
	
}
//gets the options list that was given in the command prompt
std::list<std::string> FileMgr::get_option_list()
{
	return options;
}
//gets the  number of files that were retrived by the find function 
int FileMgr::get_file_count()
{
	
	return files_count;
}
//get the path 
std::string FileMgr::get_path()
{
	return path_;
}
//get the list of patterns 
std::vector<std::string> FileMgr::get_pattern()
{
	return patterns_;
}
// get the number of directories in the given path
int FileMgr::get_directory_count()
{
	return directory_count;
}
//for all the patterns, it will call the find function which finfs all the files in that particular path
void FileMgr::search(bool recurse)
{
	files_count = 0;
	for (std::string patt : patterns_)
	find(path_,recurse,patt);
}
//stores the path given from the command line
void  FileMgr::find_path(std::string& temp, std::vector<std::string>& path_options, int& flag)
{
	int found_for_path;
	for (auto i : path_options)
	{
		found_for_path = temp.find(i);
		if ((found_for_path != std::string::npos) || (temp == "."))
		{
			path_ = temp;
			flag = 1;
			break;
		}
	}

}
//stores the options that are given by the command line 
void  FileMgr::find_options(std::string& temp, std::vector<std::string>& possible_options, int& flag)
{
	int found;
	for (auto i : possible_options)
	{
		found = temp.find(i);
		if (found != std::string::npos)
		{
			options.push_back(temp);
			flag = 2;
			break;
		}
	}

}

// processes all the command line arguments
void FileMgr::process_command_line(int argc, char* argv[])
{std::vector<std::string> path_options; 
	path_options.push_back("../");
	path_options.push_back("./");
	path_options.push_back(":/");
	std::vector<std::string> possible_options;
	possible_options.push_back("/s");
	possible_options.push_back("/d");
	possible_options.push_back("/f");
	if (argc == 0)
		{
		    path_ = ".";
			patterns_.push_back ( "*.*");
		}
		else
		{
			for (int i = 1; i < argc; i++)
			{
				int flag = 0;
				std::string temp = argv[i];
				find_path(temp, path_options, flag);
				find_options(temp, possible_options, flag);
				if (flag == 0)
					patterns_.push_back(temp);
				temp = " ";
			}
			if (patterns_.size() == 0)
				patterns_.push_back("*.*");
			
			if (path_.size() == 0)
				path_ = ".";
		}
}


// finds all the files in that particular path and pattern. If recurse is true it finds the files in that particular path
// recursively in all the directories rooted from the current directory.
void FileMgr::find(const std::string &path,bool recurse,string patt)
{
		std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
		for (auto f : files)
		{
			std::string filespec_ = FileSystem::Path::fileSpec(path, f);
			std::string fullfilespec_ = FileSystem::Path::getFullFileSpec(filespec_);
			store_.save(FileSystem::Path::getName(fullfilespec_, true), FileSystem::Path::getPath(fullfilespec_));
			files_count++;
		}
		if (recurse)
		{
			std::vector<std::string> currdirs = FileSystem::Directory::getDirectories(path);
			directory_count = currdirs.size();
			for (auto dir : currdirs)
			{
				if (dir != "." && dir != "..")

				{
					find(FileSystem::Path::fileSpec(path, dir),recurse,patt);

				}

			}
		}
}
//test stub for file manager
#ifdef TEST_FILEMGR
int main()
{
	cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
	cout << "\t" << "Testing File Manager" << std::endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl<<std::endl;
	DataStore ds;
	FileSearch fs(ds);
	FileMgr fm(".", ds);
    fm.addpattern("*.h");
    fm.search(true);
	cout << std::endl << "Displaying file count and directory count in the given path:" << std::endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------" << std::endl;
	
	cout << "There are " << fm.get_file_count() << " " << "files in " << fm.get_directory_count() << " Directories" << std::endl<<std::endl<<std::endl;
	

	return 0;
}
#endif