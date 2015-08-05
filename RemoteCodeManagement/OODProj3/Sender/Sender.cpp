/////////////////////////////////////////////////////////////////
// Sender.cpp - Demonstration of concurrent socket connectors  //
// ver 2                                                       //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2013   //
//Modified by: Sahithi Desu ; sldesu@syr.edu                   //
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
 *   BlockingQueue.h, BlockingQueue.cpp
 *
 * Maintanence History:
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

///////////////////////////////////////////////////
// SendThread thread

#ifdef TEST_SENDER


int main()
{
	try
	{
		Sender sndr("8080","127.0.0.1" , "file", "hey.txt");
		std::thread SendThread(&StartSenderThread::run, StartSenderThread(), sndr,ip, DestPort);
		std::cout << " Sender Port : " << ListPort;
		SendThread.join();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	std::cout << "\n\n";

	return 0;
}
#endif
