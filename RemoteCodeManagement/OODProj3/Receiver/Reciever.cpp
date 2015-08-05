/////////////////////////////////////////////////////////////////
// Reciever.cpp - Demonstration of socket reciever with        //
//                concurrent clients                           //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2013   //
//Modifiedby :Sahithi Desu ,sldesu@syr.edu                     //
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
 *   BlockingQueue.h, BlockingQueue.cpp
 *
 * Maintanence History:
 * ver 1.1 - 30 Mar 2013
 * - changes to error handling
 * ver 1.0 - 29 Mar 2013
 * - first release
 */
#include "../Sockets/Sockets.h"
#include "../Threads/Threads.h"
#include "../Threads/Locks.h"
#include "../BlockingQueue/BlockingQueue.h"
#include <string>

///////////////////////////////////////////////////
// ClientHandlerThread thread
#ifdef TEST_RECEIVER

int	main(int argc, char* argv[])
{
	try{
		Receiver r1;
		std::string ListenPortStr = "13210";
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
