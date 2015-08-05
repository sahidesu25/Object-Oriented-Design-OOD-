#include "Display.h"



///////////////////////////////////////////////////////////////////////
// Display.cpp -Displays output based on the calls from the Executive//
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




//function to display all the duplicate files in the Datastore
void Display::print_duplicates(bool duplicates)
{
	if (duplicates)
	{

		int flag = 0;
		iterator it;
		cout << "------------------------------------------------------------------" << endl;
		cout << endl << "Printing duplicate files in the catlogue" << endl;
		cout << endl << "------------------------------------------------------------------" << endl;
		for (auto it = store.begin(); it != store.end(); it++)
		{
			if (it->second.size() > 1)
			{
				flag = 1;
				cout << std::endl << endl << "File:" << it->first << endl;
				cout << endl << "Paths:" << std::endl;
				for (ListofIter::const_iterator list_iter = it->second.begin(); list_iter != it->second.end(); list_iter++)
				{
					cout << endl << (*(*list_iter));
				}

			}
		}
		if (flag == 0)
		{
			cout << "There are no duplicate files in the file Catlouge" << endl;
		}
	}
}

//function to diaplay all the contents in the Datastore
void Display::Display_Data_store_Contents()
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
		std::cout << std::endl;
	}

}
//Function to display the list of files that has the text given in the search criteria by the user
void Display::Display_File_Search_List(std::multimap<std::string, std::string> file_search_list)
{

	cout << endl << "The search result: " << std::endl;
	for (multimap<std::string, std::string>::iterator it = file_search_list.begin(); it != file_search_list.end(); ++it) {
		cout << "Occurred in the file: " << it->first << std::endl << "\t" << "path:" << it->second << endl << endl << endl;
	}


}


#ifdef TEST_DISPLAY

int main()
{
	DataStore ds;
	FileSearch fs(ds);
	Display dis(ds, fs);
	dis.Display_Data_store_Contents();

	
	
	return 0;
}
#endif