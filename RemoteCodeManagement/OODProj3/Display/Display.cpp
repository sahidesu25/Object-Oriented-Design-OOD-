///////////////////////////////////////////////////////////////
// Display.cpp - Displays the information received.		     //
//															 //
// ver 1.1                                                   //
// Language: standard C++                                    //
// Author:      Sahithi Lakshmi Desu 					     //
//             sldesu@syr.edu						         //
///////////////////////////////////////////////////////////////
/*
*/

#include "Display.h"
//converts string to a vector of 1024
std::vector<char> Display::stringToVector(std::string s)
{
	std::vector<char> temp(1024);
	for (size_t i = 0; i < s.size(); i++)
	{
		temp[i] = s[i];
	}
	return temp;
}
//displaying the results based on the command.
void Display::DisplayResults(Message msg)
{
	if (msg.getCommand() == "text")
	{
		std::cout << "\n----------------------------------------------------";
		std::cout << "\n\nReceiving the text message\n\n";
		std::cout << "----------------------------------------------------\n";
		std::cout << "-----------------Message Details--------------------\n";
		std::cout << "SenderIP:" << msg.getSourceIp()<<"\n";
		std::cout << " SenderPort:" << msg.getPort() << "\n";
		std::cout << " type:" << msg.getType() << "\n";
		std::cout << " content:"<<"\n";
		std::string body = msg.getMsgContent();
		std::cout <<"\t\t\t\t"<< body;
	}
	else if (msg.getCommand() == "start")
	{
		std::cout << "\n----------------------------------------------------";
		std::cout << "\n\nReceiving the file\n\n";
		std::cout << "----------------------------------------------------\n";
		std::cout << "-----------------Message Details--------------------\n";
		std::cout << "\t\t";
		std::cout<<"SenderIP:" << msg.getSourceIp() << "\n";
		std::cout << "SenderPort:" << msg.getPort() << "\n";
		std::cout << "type:" << msg.getType() << "\n";
		std::cout<< "File: " << msg.getFileName();
	}
	else
	{
		std::cout << "\nReceived Successfully by the receiver";

	}

}
#ifdef TEST_DISPLAY
int main()
{
	std::cout << "This is a test stub for Display";
	stringToVector("Sample for the test stub");
}
#endif

