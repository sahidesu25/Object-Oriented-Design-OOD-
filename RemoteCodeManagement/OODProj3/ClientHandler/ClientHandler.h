#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
///////////////////////////////////////////////////////////////
// ClientHandler.h: handles the client requests based on the //
//					 messages that are received from client  //
// ver 1.1                                                   //
// Language: standard C++                                    //
// Author:      Sahithi Lakshmi Desu						 //
//             sldesu@syr.edu						         //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* ===================
* Based on the request from the sender it handles the request to either text handler or file Handler.
*/
/*
* Required Files:
* ---------------
* Message.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 4/12/15
* - first release
*/
#include <iostream>
#include <vector>
#include "../Message/Message.h"
#include <map>



class ClientHandler
{
	std::map<std::string, std::ofstream*> fileMap;

	public:
		void RetrivingMessage(std::vector<char> msg);
	void TextHandler(Message msg);
void FileHandler(Message msg);
	std::vector<char> stringToVector(std::string body);

};
#endif