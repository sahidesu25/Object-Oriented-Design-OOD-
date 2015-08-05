///////////////////////////////////////////////////////////////
// ClientHandler.cpp - Handles Client Requests based on the  //
//                     type of message                       //
// ver 1.1 4/14/2015                                         //
// Language: standard C++                                    //
// Author:      Sahithi Lakshmi Desu 						 //
//             sldesu@syr.edu						         //
///////////////////////////////////////////////////////////////
#include "ClientHandler.h"
#include "../Display/Display.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <Algorithm>
//handles all the senders request for text messages
void ClientHandler::TextHandler(Message msg)
{
	Display::DisplayResults(msg);
}
//converts string to vector of size 1024
std::vector<char> ClientHandler::stringToVector(std::string s)
{
		std::vector<char> temp(1024);
		for (size_t i = 0; i < s.size(); i++)
		{
			temp[i] = s[i];
		}
		return temp;
}
//handles all the sender's requests for uploading files to the receiver
void ClientHandler::FileHandler(Message msg)
{
	if (msg.getCommand() == "start")
	{
		Display::DisplayResults(msg);
			std::ofstream *file =  new std::ofstream(msg.getFileName(), std::ios::binary | std::ios_base::app | std::ios::out);
			fileMap.insert(std::make_pair(msg.getFileName(), file));
	}
	 if (msg.getCommand() == "downloaddata")
	{
		std::vector<char> body_ = stringToVector(msg.getMsgContent());
		int size = msg.getSize();
		if (!fileMap[msg.getFileName()])
			std::cout << "\nCannot open the file, there might be something wrong in the creation";
		int count = 0;
		while (count<size)
		{ 
			*fileMap[msg.getFileName()] << body_[count];
			count++;
		}
	 }
	if (msg.getCommand() == "closefile")
	{
		Display::DisplayResults(msg);
		std::ofstream *file = fileMap[msg.getFileName()];
		file->close();
		fileMap.erase(msg.getFileName());
		
		delete file;
	}
}
//gets the message from the sender and sets the message parameters and handles the task to the respective client handler
//based on the type of the message. ie: wether it is file or text
void ClientHandler::RetrivingMessage(std::vector<char> msg)
{
	Message message;
	std::string MessageString(msg.begin(), msg.end());
	int sourcePortPos = MessageString.find("SourcePort");
	int filenamePos = MessageString.find("filename");
	int typePos = MessageString.find("type");
	int commandPos = MessageString.find("command");
	int ipPos = MessageString.find("IP");
	int ListenerportPos = MessageString.find("ListenerPort");
	int sizePos = MessageString.find("size");
    int bodyPos = MessageString.find("body");
	std::string sourceport = MessageString.substr(sourcePortPos + 11, (filenamePos - 3) - (sourcePortPos + 11) + 1);
	std::string filename = MessageString.substr(filenamePos + 9, (ipPos - 3) - (filenamePos + 9) + 1);
	std::string size = MessageString.substr(sizePos + 5, (typePos - 3) - (sizePos + 5) + 1);
	std::string type = MessageString.substr(typePos + 5, (commandPos - 3) - (typePos + 5) + 1);
	std::string command = MessageString.substr(commandPos + 8, (bodyPos - 3) - (commandPos + 8) + 1);
	std::string ip = MessageString.substr(ipPos + 3, (ListenerportPos - 3) - (ipPos + 3) + 1);
	std::string Listenerport = MessageString.substr(ListenerportPos + 13, (sizePos - 3) - (ListenerportPos + 13) + 1);
	std::string body = MessageString.substr(bodyPos + 5, atoi(size.c_str()));
	message.setSourceIp(sourceport);
	message.setType(type);
	message.setComnand(command);
	message.setMsgContent(body);
	message.setFileName(filename);
	message.setListnerIp(ip);
	int Listenerport_Int = atoi(Listenerport.c_str());
	message.setListenerPort(Listenerport_Int);
	size_t sizeInt = atoi(size.c_str());
	message.setSize(sizeInt);
if (message.getType() == "text")
	   TextHandler(message);
if (message.getType() == "file")
	FileHandler(message);
}
#ifdef TEST_CLIENTHANDLER

int main()
{
	std::cout << "The test stub for Client Handler" << std::endl;
	ClientHandler cl;
	Message message;
	message.setSourceIp("13210");
	message.setType("text");
	message.setComnand("start");
	message.setMsgContent("hey");
	message.setListnerIp("127.0.0.1");
	int Listenerport_Int = atoi("127.0.0.1");
	message.setListenerPort(Listenerport_Int);
	size_t sizeInt = atoi("4");
	message.setSize(sizeInt);

	if (message.getType() == "text")
		cl.TextHandler(message);
	if (message.getType() == "file")
	cl.FileHandler(message);

}
#endif