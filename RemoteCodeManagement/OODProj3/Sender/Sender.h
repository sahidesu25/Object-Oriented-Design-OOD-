#ifndef SENDER_H
#define SENDER_H
/////////////////////////////////////////////////////////////////
// Sender.cpp - Demonstration of concurrent socket connectors  //
// ver 2                                                       //
// Author Jim Fawcett, CSE687 - Object Oriented Design, Spring //
//Modified By : Sahithi Desu sldesu@syr.edu	                   //
//Reference Used:                                              //
/////////////////////////////////////////////////////////////////
/*
* This Sender expects to write lines of text only.
* So message framing is done by lines.
*
* For HTTP like protocols the Sender should send lines for each
* header attribute and bytes in the body, if there is one,
* specified by a last header line something like:
*    content_length : 1024
* where 1024 is a stand-in for whatever you want your block
* size to be.
*
*/
/*
* Required files:
* - Sender.cpp, Sockets.h, Sockets.cpp,
*   Threads.h, Threads.cpp, Locks.h, Locks.cpp
*   BlockingQueue<Message>.h, BlockingQueue<Message>.cpp
*	Messages.h
*
* Maintanence History:
* ver1.2  - 4/11/2015
*	- Implemented C++ threads
* ver 1.1 - 30 Mar 2013
* - changed Sendthread from terminating to default
* - minor changes to error handling
* ver 1.0 - 29 Mar 2013
* - first release
*/

#include "../Sockets/Sockets.h"
#include "../Threads/Locks.h"
#include "../BlockingQueue/BlockingQueue.h"
#include <string>
#include <iostream>
#include <sstream>
#include "../Message/Message.h"
#include <thread>
#include <fstream>

std::string ToString(int i)
{
	std::ostringstream conv;
	conv << i;
	return conv.str();
}


class Sender
{
public:

	Sender(int listPort, std::string ip, std::string msgType, std::string content) : ListenerPort(listPort), Ip(ip),
		 messageType(msgType), messageContent(content)
	{
		if (messageType == "file")
		{
			try
			{
				store_data_Content(messageContent);
				
			}
			catch (std::exception e){
				std::cout << e.what();
			}
		}
	
	}//stores the data content in the file in to a vector of charecters
	//ref: http://stackoverflow.com/questions/15080652/c-get-one-line-data-in-txt-file
	void store_data_Content(std::string messageContent)
	{
		try
			{
				std::ifstream file(messageContent,std::ios::binary);
				file.seekg(0, std::ios::end);
				size_t file_size = size_t(file.tellg());
				file.seekg(0, std::ios::beg);
				std::vector<char> temp(file_size);
				file.read((char*)&temp[0], file_size);
				fileData = temp;
				file.close();

			}
			catch (std::exception e)
			{
				std::cout << e.what();
			}
	}
	//sets the text message ans enques it in to the queue
	void set_txt_message(Message msg)
	{
		std::vector<char> MessageVector(1024);
		msg.setComnand("text");
		msg.setListnerIp(Ip);
		msg.setListenerPort(ListenerPort);
		msg.setType(messageType);
		msg.setMsgContent(messageContent);
		msg.setSize(messageContent.size());
		std::string systemIp = s_.System().getLocalIP();
		msg.setSourceIp(systemIp);

		std::string str = msg.getMessage();

		for (size_t i = 0; i < str.size(); i++)
		{
			MessageVector[i] = str[i];
		}
		q_.enQ(MessageVector);
	}//creates and enques the file start message,this is used by an receiver to create a file 
	void enque_file_start(Message msg)
	{
		msg.setComnand("start");
		msg.setFileName(messageContent);
		msg.setListnerIp(Ip);
		msg.setListenerPort(ListenerPort);
		msg.setType(messageType);
		msg.setMsgContent(messageContent);
		msg.setSize(messageContent.size());
		std::string systemIp = s_.System().getLocalIP();
		msg.setSourceIp(systemIp);
		std::string str = msg.getMessageWithoutContent();
		std::vector<char> file_start(1024);
		file_start= stringToVector(str);
		q_.enQ(file_start);

	}// takes the file data according to the size of the chuck specified and enques the chunk in to the queue.
	void enque_filedata(Message msg,int index)
	{
		msg.setComnand("downloaddata");
		msg.setSize(200);
		msg.setFileName(messageContent);
		msg.setListnerIp(Ip);
		msg.setListenerPort(ListenerPort);
		msg.setType(messageType);
        std::string systemIp = s_.System().getLocalIP();
		msg.setSourceIp(systemIp);
       std::string str = msg.getMessageWithoutContent();
		std::vector<char> Message(str.size() + 201);
		Message = stringToVector(str);
		int size_ = str.size();
		int count = index;
		while (count < (index + 200))
		{
			Message[size_] = fileData[count];
			size_++;
			count++;
		}
		q_.enQ(Message);
	}
	// enqueus the remaining data that is present in the file.
	void enque_remaining_data(Message msg, int index)
	{
		msg.setComnand("downloaddata");
		msg.setFileName(messageContent);
		msg.setListnerIp(Ip);
		msg.setListenerPort(ListenerPort);
		msg.setType(messageType);
        std::string systemIp = s_.System().getLocalIP();
		msg.setSourceIp(systemIp);
		int RemainingLetters = fileData.size() - index;
		msg.setSize(RemainingLetters);
		std::string str = msg.getMessageWithoutContent();
		std::vector<char> RemainingMessage(1024);
		RemainingMessage = stringToVector(str);
        int _size = str.size();
		for (size_t j = index; j < fileData.size(); j++)
		{
			RemainingMessage[_size] = fileData[j];
			_size++;
		}
		q_.enQ(RemainingMessage);
	}
	//enqueues the end of the file message in to the blocking queue. This command will be used by the receiver
	//to understand when to close the file.
	void enque_file_end(Message msg)
	{
		msg.setComnand("closefile");
		msg.setFileName(messageContent);
		msg.setListnerIp(Ip);
		msg.setListenerPort(ListenerPort);
		msg.setType(messageType);
		msg.setSize(messageContent.size());
		std::string systemIp = s_.System().getLocalIP();
		msg.setSourceIp(systemIp);
		std::string str1 = msg.getMessageWithoutContent();
		std::vector<char> FileEnd(1024);
        FileEnd = stringToVector(str1);
		q_.enQ(FileEnd);
	}
	//converts the string in to the vector of 1024 charecters
	std::vector<char> stringToVector(std::string s)
	{
		std::vector<char> temp(1024);
		for (size_t i = 0; i < s.size(); i++)
		{
			temp[i] = s[i];
		}
		return temp;
	}
	// this is the start of the sender. Here the sender thread creates the child thread which deques the message from the
	//blocking queue and sends to the receiver via socket.
	
	void start(std::string ip, int port)
	{
		std::cout << "\n Sender started \n" ;
		std::cout << "\n Sender IP : " << s_.System().getLocalIP();
		std::thread childThread(&Sender::run, this);
		if (!s_.connect(ip, port))
		{
			std::cout << locker << "\n  couldn't connect to " << ip << ":" << port << "\n\n" << unlocker;
			return;
		}
		else
		{
			std::string logMsg = "\n  connected to " + ip + ":" + ToString(port);
			doLog(logMsg.c_str());
		}
		doLog("starting Sender");
		Message msg;
		int flag = 0;
		if (messageType == "file")
		{
			enque_file_start(msg);
			size_t count = 0;
			
			while(count<fileData.size()){
				if (fileData.size() < (count + 200))//this is the check whether the remaining data in the file is greater 
				{                                   // the chunk size ie:200
					enque_remaining_data(msg, count);
					enque_file_end(msg);
					break;
				}
				enque_filedata(msg, count);
				count = count + 200;
				if (fileData.size() == (count + 200))
				{
					enque_file_end(msg);
					break;
				}
			} 
		}
			
		if (messageType == "text")
		{
			set_txt_message(msg);
		}
		std::vector<char>breakMessage = stringToVector("breakmessage");
		q_.enQ(breakMessage);
		std::vector<char>StopMessage = stringToVector("stopmessage");
		q_.enQ(StopMessage);
		childThread.join();
	}
	// this is executed by the child thread, which deques message from the blocking queue and sends it to the receiver 
	// through socket's send method.
	void run()
	{
		try
		{
			status_ = "good";
			doLog("send thread running");
			std::string msg;
			std::string quit_msg;
			std::vector<char> senderVector;
			while (true)
			{
				doLog("send thread enqing msg");
				senderVector = q_.deQ();
				std::string temp_message(senderVector.begin(), senderVector.begin() + 10);
				std::size_t found = temp_message.find("stopmessage");//sends to the receiver until it see the "stopmessage"
				if (found != std::string::npos)
				{
					break;
				}
				else
				{
					if (!s_.send(&senderVector[0], 1024))
					{
						break;
					}
				}

			}
	}
	catch (std::exception e){
			std::cout << e.what();
		}
		s_.disconnect();
	}
private:
	Socket s_;
	BlockingQueue<std::vector<char>> q_;
	std::string status_;
	std::vector<char> fileData;//this stores the data in the file
	std::string messageType;// this can be file or text
	std::string messageContent;// conatins rthe body of the message
	std::string Ip;
	int ListenerPort;
	size_t size;
	std::string command;// specifies the command, besed on which the receiver will take the action.
};

class StartSenderThread
{
public:
	void run(Sender sndr_, std::string Ip, int DestPort)
	{
		sndr_.start(Ip, DestPort);
	}
};



#endif