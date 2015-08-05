/////////////////////////////////////////////////////////////////
// RecieverExecutive.cpp - Start of the Receiver               //
//Author  :  Sahithi Lakshmi Desu sldesu@syr.edu			   //		
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
* -
* Maintanence History:

* ver 1.0 - 4/14/2015
* - first release
*/
#ifdef TEST_RECEIVEREXEC
#include "Receiver.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
// this is the start of the receiver executive. 
int	main(int argc, char* argv[])
{
		try{
			Receiver r1;
			 std::string ListenPortStr = argv[1];
			 int ListenPortNumber = atoi(ListenPortStr.c_str());
			 std::cout << "\n Receiver Port : " << ListenPortNumber;
             r1.start(ListenPortNumber);
		}
		catch (std::exception& e)
		{
			std::cout << "\n\n    " << e.what() << "\n\n";
		}
		return 0;
	}

#endif