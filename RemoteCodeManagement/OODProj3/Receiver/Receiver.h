#ifndef RECEIVER_H
#define RECEIVER_H

/////////////////////////////////////////////////////////////////
// Reciever.h - Demonstration of socket reciever with          //
//                concurrent clients                           //
//                                                             //
// Author : Jim Fawcett, CSE687 - Object Oriented Design       //
//Modified By : Sahithi Desu sldesu@syr.edu  				   //
/////////////////////////////////////////////////////////////////
/*
* This Reciever expects to read lines of text only.
* So message framing is done by lines.
*
* For HTTP like protocols the Reciever should expect
* lines in the header and bytes in the body, if there is one,
* specified by a header line something like:
*    content_length : 1024
* where 1024 is a stand-in for whatever you want your block
* size to be.
*
*/
/*
* Required files:
* - Reciever.cpp, Sockets.h, Sockets.cpp,
*   Threads.h, Threads.cpp, Locks.h, Locks.cpp
*   BlockingQueue.h, BlockingQueue.cpp, Message.h
*
* Maintanence History:
* ver1.2  - 4/12/2015
*	- Implemented C++ threads 
* ver 1.1 - 30 Mar 2013
* - changes to error handling
* ver 1.0 - 29 Mar 2013
* - first release
*/
#include "../Sockets/Sockets.h"
#include "../Message/Message.h"
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include "../ClientHandler/ClientHandler.h"
#include "../Threads/Locks.h"
#include "../Threads/Threads.h"
#include "../BlockingQueue/BlockingQueue.h"


///////////////////////////////////////////////////
// listenThread thread

class Receiver
{
public:
	void start(int port)
	{
		std::cout << "\n Reciever started";
		std::thread ListenThread(&Receiver::StartListenThread,this,port);
		ClientHandler _clienthandler;

		try
		{
			while (true)
			{
				std::vector<char> receiveMsg;
				receiveMsg = q_.deQ();
				std::string temp_message(receiveMsg.begin(), receiveMsg.begin() + 12);
				std::string breakMessage = temp_message + " ";
				if (breakMessage != "breakmessage")
				{
					_clienthandler.RetrivingMessage(receiveMsg);
				}
				else
					break;
			}
		}
		catch (std::exception& ex) 
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		catch (...)
		{
		}
	}
	std::vector<char> stringToVector(std::string s)
	{
		std::vector<char> temp;
		for (size_t i = 0; i < s.size(); i++)
		{
			temp[i] = s[i];
		}
		return temp;
	}

	void run(Socket s)
	{
		std::vector<char> msg(1024);
		
		while (true)
		{
			doLog("receive thread receiving Message from the sender");
			s.recv(&msg[0], 1024);
			if (msg[0] == ' ')
			{
				break;
			}
			else
			{
				std::string temp_string;
				std::string temp(msg.begin(), msg.begin() + 12);
				std::string break_string = temp_string + "";
				if (break_string != "stopmessage")
					q_.enQ(msg);
				else
					break;
			}
		}
	}
	void StartListenThread(int port)
	{
		while (true)
		{
			SocketListener listener_(port);
			SOCKET s = listener_.waitForConnect();
			std::thread clientHandler(&Receiver::run, this, s);
			clientHandler.detach();
		}
	}
private:
	BlockingQueue<std::vector<char>> q_;
	Socket s_;
};
#endif