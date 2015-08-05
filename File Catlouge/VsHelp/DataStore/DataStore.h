#ifndef DATASTORE_H
#define DATASTORE_H
#pragma once
///////////////////////////////////////////////////////////////////////
// DataStore.h - It stores all the files and the paths of the files  //
//               returned by the file Manager with out repeating the //
//               path and the file name.                             //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: File Catlogue, Project #1, Spring 2015               //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//* This module takes the path and the filename from the File manager and saves it in the Store
//* This has a set of paths and a Map which has file name as key and list of iterators, pointing to the setof path as value
//* This makes sure that each file has a list of iterators that are pointind to the list of paths in the set.
//* In this way this module saves memory by not repeating filename and as well as path name more than once in the program.
//* Maintenance History :
//*--------------------
//* -first release



//DataStore.h:.....

#include<vector>
#include<set>
#include<map>
#include<string>
#include<list>
#include<iostream>
# pragma once

class DataStore
{
public:
	using Path = std::string;
	using Paths = std::set < Path > ;
	using PathIter = Paths::iterator;
	using ListofIter = std::list < PathIter > ;
	using File = std::string;
	using Store = std::map < File, ListofIter > ;
    using iterator = Store::iterator;
	void save(const std::string& filename, const std::string &path);
	void display();
	
	iterator begin(){ return store.begin(); }
	iterator end(){ return store.end(); }
private:
	Store store;
	Path _path;
	Paths path_set;


};
#endif

