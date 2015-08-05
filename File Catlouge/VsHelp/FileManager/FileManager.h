#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
// FileMgr.h - It proccesses all the command line arguments and      //
//             retrives all the files rooted from the specified      //
//             directory using FileSystem Project                    //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: File Catlogue, Project #1, Spring 2015               //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//* Processes all the command line arguments and pass it to the Executive. 
//* Finds all the files that are rooted from the specified path and saves it to the datastore
//*
//* Required Files
//*--------------------
//* DataStore.cpp and DataStore.h
//*
//* Maintaiance History
//*--------------------
//* -first release




#include "FileSystem.h"
#include"../DataStore/DataStore.h"


class FileMgr
{
	
public:
	using iterator = DataStore::iterator;
	using patterns = std::vector < std::string > ;
	
	
	FileMgr(const std::string& path, DataStore &ds) :path_(path), store_(ds)
	{
		
	}
	std::string get_path();
	std::vector<std::string> get_pattern();
	int get_file_count();
	std::list<std::string> get_option_list();
	int get_directory_count();
    void search(bool);
	std::vector<std::string> getfilelist();
	void addpattern(const std::string& patt);
	void find(const std::string &path,bool,std::string);
	void process_command_line(int argc, char* argv[]);
  void  find_path(std::string& temp,std::vector<std::string>& path_options,int& flag);
  void  find_options(std::string& temp, std::vector<std::string>& possible_options, int& flag);

	
private:
	std::string path_;
	DataStore& store_;
	patterns patterns_;
	std::list<std::string> options;
	std::vector<std::string> file_list;
	std::vector<std::string> full_filespec_list;
	bool recurse;
	int directory_count;
	int files_count;
};



#endif // !FILEMGR_H
