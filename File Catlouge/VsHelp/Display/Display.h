#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////
// Display.h -Displays output based on the calls from the Executive  //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: File Catlogue, Project #1, Spring 2015               //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//*  Has all the functions which displays the Datastore Contents , File search result and the Duplicate files.
//*  These are called by the Executive.
//*
//*Required Files
//*--------------------
//* FileMgr.h,FileMgr.cpp,FileSearch.h,FileSearch.cpp,DataStore.cpp and DataStore.h
//*
//* Maintaiance History
//*--------------------
//* -first release



#include "../DataStore/DataStore.h"
#include "../FileManager/FileManager.h"
#include "../FileSearch/FileSearch.h"
//#include "../DataStore/DataStore.cpp"

class Display
{
public:
	using iterator = DataStore::iterator;
	using Path = std::string;
	using Paths = std::set < Path >;
	using PathIter = Paths::iterator;
	using ListofIter = std::list < PathIter >;
	using File = std::string;
	using Store = std::map < File, ListofIter >;
	using iterator = Store::iterator;
	Display(DataStore &ds, FileSearch &fs) :store(ds) ,filesearch_(fs){}
	void Display_File_Search_List(std::multimap<std::string, std::string> file_search_list);
	void print_duplicates(bool duplicates);
	void Display_Data_store_Contents();
	

private:
	DataStore &store;
	FileSearch &filesearch_;
	

};

#endif
