#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////
// Display.h - To print the information				         //
//															 //
// ver 1.1                                                   //
// Language: standard C++                                    //
// Author:      Sahithi Desu						         //
//             sldesu@syr.edu						         //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* ===================
* Display has function which displays the contentd received by the receiver.
* Required Files:
* ---------------
* Message.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 4/13/2015
* - first release
*/
#include <iostream>
#include "../Message/Message.h"
#include <vector>

class Display
{
public:
	static std::vector<char> Display::stringToVector(std::string s);
	static void DisplayResults(Message msg);
};

#endif