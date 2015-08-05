#ifndef EXECUTIVE
#define EXECUTIVE
///////////////////////////////////////////////////////////////////////
// Executive.cpp - The entry point of the program                     //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: File Catlogue, Project #1, Spring 2015               //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//
//Module Operations:
// ==============
//* This is the entry of the project and it calls all the functions in the project.
//* This takes the user input from the console multiple times and call the file search to seach for the word specified.
//* Exits the project when the user gives "N" in the console
//* Required Files:
//* ==============
//* Datastore.cpp, DataStore.h, FileMgr.cpp, FileMgr.h,FileSearch.h and FileSearch.cpp
// Maintenance History :
//*--------------------
//* -first release




// Executive package(Executive.cpp)

#include<iostream>
#include<string>
#include<sstream>
#include"../FileSearch/FileSearch.h"
#include"../DataStore/DataStore.h"
#include"../FileManager/FileManager.h"
#include"../FileManager/FileSystem.h"
#include"../FileManager/FileManager.cpp"
#include"../FileManager/FileSystem.cpp"
#include"../FileSearch/FileSearch.cpp"
#include"../Display/Display.h"
#include"../Display/Display.cpp"
#include<algorithm>
using namespace std;

//Entry of the project
int main(int argc, char *argv[])

{
	try
	{
		if (argc == 0)
		{
			std::cout << "Please enter the path and the patterns" << std::endl;
			return 0;
		}
		std::cout << "-------------------------------------------------------------------------------------" << std::endl;
		std::cout << "                           Demonstrating File Catlogue" << std::endl;
		std::cout << "-------------------------------------------------------------------------------------" << std::endl;
		std::multimap<std::string, std::string> file_search_list;
		std::list<std::string> duplicate_list;
		std::list<std::string> option_list;
		bool recurse = false;
		bool duplicates = false;
		bool search = false;
		std::string search_word;
		DataStore ds;
		FileSearch fs(ds);
		FileMgr fm(".", ds);
		Display dis(ds, fs);
		fm.process_command_line(argc, argv);
		option_list = fm.get_option_list();
		std::cout<<std::endl<<"path:"<< fm.get_path()<<std::endl;
		std::vector<std::string> patterns_selected = fm.get_pattern();
		for (auto i : patterns_selected)
		{
			cout << "patterns:" << i << endl;
		}

// checking the user given options in the command line and setting them to the user defiend values
		if (option_list.size() != 0)
		{
			for (std::list<std::string>::const_iterator it = option_list.begin(); it != option_list.end(); it++)
			{

				if ((*it == "/s") || (*it == "/S"))
				{
					recurse = true;
				}
				else if ((*it == "/d") || (*it == "/D"))
				{
					duplicates = true;
				}
				else
				{// extracting the searchstring from the "/f<search_string>" command
					int found;
					std::string temp = *it;
					found = temp.find("/f");
					if (found != std::string::npos)
					{
						int count = 0;
						char *context = NULL;
						char *s2 = (char *)alloca(temp.size() + 1);
						memcpy(s2, temp.c_str(), temp.size() + 1);
						char* p = strtok_s(s2, "f < >", &context);
						while (p != NULL)
						{

							if (count == 1)
							{
								search_word = p;
							}

							p = strtok_s(NULL, "", &context);
							count = count + 1;
						}
					}
				}
			}
		}
//calling file manager to retrive all the files from the specified path and pattern 
		fm.search(recurse);
		if (option_list.size() == 0)
		{
			std::cout << std::endl << " Options not given, displaying file count and directory count in the given path:" << std::endl;
			std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

			std::cout << "There are " << fm.get_file_count() << " " << "files in current Directory" << std::endl << std::endl << std::endl;

		}
		else
		{
			std::cout << endl << "Listing all the options provided in the commandline" << endl;
			for (std::list<std::string>::const_iterator it = option_list.begin(); it != option_list.end(); it++)
			{
				std::cout << endl << *it << endl;
			}

		}

		std::cout << endl;
		dis.Display_Data_store_Contents();
		std::cout << endl;
		// searching for the word given in the command prompt
		if (!search_word.empty())
		{
			file_search_list = fs.search_filecatlog(search_word);
			if (file_search_list.size() == 0)
			{
				std::cout << "There is no search result for the given text" << std::endl;
			}
			else
			dis.Display_File_Search_List(file_search_list);


		}
		std::cout << endl << endl;
		if (duplicates)
			dis.print_duplicates(duplicates);
		cout << endl<<endl<<endl<<"---------------------------------------------------------------------------------------";
		cout << endl << "Demonstrating requirement 8" << endl;
		cout << "---------------------------------------------------------------------------------------";
		std::string search_string;
		std::string example_string = "/f\"bool recurse\" *.cpp *.h";
		//accepting strings to search from the file catlogue to find the files that has the user specified string
		while (true)
		{
			std::vector<std::string> search_patterns;
			std::string search_str = " ";
			std::cout << endl << endl << "Enter the string you want to search with patterns or with out patterns" << endl<<endl;
			
			std::cout << "For Example:" << example_string << std::endl;
			std::cout << "----------------------------------------" << endl;
			std::cout << endl << "If you dont want to search enter NO" << endl;
			std::getline(std::cin, search_string);
			if (search_string != "NO")
			{
				file_search_list.clear();
				FileSearch * fs_ = new FileSearch(ds);
				int found;
				std::string temp = search_string;
				found = temp.find("/f");
				if (found != std::string::npos)
				{
					int count = 0;
					char *context = NULL;
					char *s2 = (char *)alloca(temp.size() + 1);
					memcpy(s2, temp.c_str(), temp.size() + 1);
					char* p = strtok_s(s2, "f\"'*", &context);
					while (p != NULL)
					{
						cout << p<<endl;
						if (count == 1)
						{
							search_str = p;
							
							
						}
						if ((count > 1))

						{
							std::string temp_ = p;
							
							search_patterns.push_back(temp_);
							if (count == 2)
							{
								search_patterns.pop_back();
							}
							temp_ = " ";
							cout << endl << p;
						}

						p = strtok_s(NULL, "\"'*", &context);
						count = count + 1;
					}
				}
				
				if (search_patterns.size() == 0)
				{//calls when user has not specified any patterns 
					file_search_list = fs.search_filecatlog(search_str);
				}
				else
				{//calls when user specifies the patterns
					file_search_list = fs.search_filecatlog_(search_str, search_patterns);

				}
				
				if (file_search_list.size() == 0)
				{
					std::cout << "There is no search result for the given text" << std::endl;
					delete fs_;
				}

				else
				{
					dis.Display_File_Search_List(file_search_list);
					delete fs_;

				}


			}
		
			else
			{
				break;
			}

		}
		cout << std::endl << "-----------------------------Exiting----------------------------------------";
		
		return 0;
	}
	catch (exception e)
	{
		e.what();
	}
}
#endif