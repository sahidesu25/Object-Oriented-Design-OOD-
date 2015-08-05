//Data store.cpp
///////////////////////////////////////////////////////////////////////
// DataStore.cpp - It stores all the files and the paths of the files//
//               returned by the file Manager with out repeating the //
//               path and the file name                              //
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




#include"DataStore.h"



#include<iostream>
// this function saves the file name and the path only once in the DataStore 
void DataStore::save(const std::string& filename, const std::string &path)
{
	iterator found = store.find(filename);
	PathIter piter_found = path_set.find(path);
	if (found != store.end())
	{

		if (piter_found != path_set.end())
		{
			found->second.push_back(piter_found);
		}
		else
		{
			path_set.insert(path);
			PathIter iter = std::next(path_set.end(), -1);
			found->second.push_back(iter);
		}
	}
	else
	{
		ListofIter temp;

		if (piter_found != path_set.end())
		{
			temp.push_back(piter_found);
		}
		else
		{
			path_set.insert(path);
			PathIter iter = std::next(path_set.end(), -1);
			temp.push_back(iter);
		}

		store.insert(make_pair(filename, temp));
	}

}

//Diaplays the content in the Data store
void DataStore::display()
{
	std::cout << std::endl << "--------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "\t" << "Displaying the contents in the File Catlouge" << "\t" << std::endl;
	std::cout << std::endl << "--------------------------------------------------------------------------" << std::endl;

	for (auto iter = store.begin(); iter != store.end(); iter++)
	{
		std::cout << "file: " << iter->first << std::endl << "paths:" << std::endl;
		for (ListofIter::const_iterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
		{
			std::cout << " " << (*(*list_iter)) << std::endl << std::endl;
		}

	}
	
}




#ifdef TEST_DATASTORE
int main()
{
	std::cout << "-----------------------------------------------------------------------------------------------";
	std::cout << "\n Testing Data Store\n";
	std::cout << "-----------------------------------------------------------------------------------------------";
	DataStore ds;
	
	ds.save("file1","path1");
	ds.save("file1","path2");
	ds.save("file1", "path3");
	ds.save("file2","path1");
	ds.save("file2", "path2");
	ds.save("file3", "path3");
	ds.save("file4", "path1");
	ds.save("file4", "path4");
	ds.save("file5", "path5");
	ds.display();
    std::cout << "\n\n";

}


#endif