#ifndef MESSAGE_H
#define MESSAGE_H
///////////////////////////////////////////////////////////////
// Message.h - Creates a message object which                //
//               encapsulates the information. This is for   //
//                Http protocol 	                         //
//															 //
// ver 1.1                                                   //
// Language: standard C++11                                    //
// Author:      Sahithi Desu					             //
//             sldesu@syr.edu					             //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* ===================
* This is used to crate message details from the input vector of charecters.
* Package includes all the required getters and setters.
*
* Required Files:
* ---------------
*
*
* Maintenance History:
* --------------------
* ver 1.0 : 4/10/2015
* - first release
*/

#include <iostream>
#include <string>
#include <sstream>

class Message
{
private:
	std::string ListenerIp;
	int ListenerPort;
	std::string type;
	std::string command;
	std::string MessageContent;
	size_t size;
	std::string filename;
	std::string SourceIp;
	
public:
	void setListnerIp(std::string ListenerIp);
	std::string getIp();
	void setListenerPort(int Listenerport);
	int getPort();
	void setType(std::string type);
	std::string getType();
	void setComnand(std::string Command);
	std::string getCommand();
	void setMsgContent(std::string MessageContent);
	std::string getMsgContent();
	void setSize(size_t siz);
	size_t getSize();
	void setFileName(std::string FileName);
	std::string getFileName();
	std::string getSourceIp();
	void setSourceIp(std::string SourceIp);
	std::string getMessage();
	std::string getMessageWithoutContent();
 };
#endif