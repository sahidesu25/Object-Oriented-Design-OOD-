/////////////////////////////////////////////////////////////////
// SenderExecutive.cpp - This is the start of the sender       //
// ver 2                                                       //
// Author : Sahithi Desu sldesu@syr.edu						   //
/////////////////////////////////////////////////////////////////
/*
* This Sender accepts the argumaents from the coomand line and sends 
*them to the sender, which crretes a http message and enques it in to the queue.
* Message framing is done based on the arguments passed to the sender Executive.
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
* - 
* Maintanence History:

* ver 1.0 - 13 Apr 2015
* - first release
*/
#ifdef TEST_SENDEREXEC
#include "Sender.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

int main(int argc, char* argv[])
{ 
	std::string ListenerPort = argv[1];
	int ListPort = atoi(ListenerPort.c_str());
	std::string ip = argv[2];
	int intIp = atoi(ip.c_str());
	std::string DestPortString = argv[3];
	int DestPort = atoi(DestPortString.c_str());
	std::string messageType = argv[4];
	std::string message = argv[5];
	std::string fileName = "";
	try
	{
		Sender sndr(ListPort, ip, messageType, message);
		std::thread SenderThread(&StartSenderThread::run, StartSenderThread(), sndr,ip, DestPort);
		std::cout << " Sender Port : " << ListPort << std::endl;
		std::cout << "Sending" << " " << messageType << " :" << message << std::endl;
		SenderThread.join();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n   " << ex.what() << "\n";
	}
	std::cout << "\n";
}
#endif