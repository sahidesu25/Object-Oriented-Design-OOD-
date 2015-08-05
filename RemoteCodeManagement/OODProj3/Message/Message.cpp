
///////////////////////////////////////////////////////////////
// Message.cpp - Creates a message object which              //
//               encapsulates the information. This is for   //
//                Http protocol 	                         //
//															 //
// ver 1.1, 4/14/2015                                        //
// Language: standard C++                                    //
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

#include "Message.h"
#include <string>
#include <sstream>

std::string Message::getIp()
{
		return this->ListenerIp;
}
void Message::setListenerPort(int Listenerport)
	 {
		 this->ListenerPort = Listenerport;
	 }
void Message::setListnerIp(std::string ListenerIp)
{
	this->ListenerIp = ListenerIp;
}

int Message::getPort()
{
	return this->ListenerPort;
}
std::string Message::getType()
{
	return this->type;
}
void Message::setType(std::string type)
{
	this->type = type;
}

void Message::setComnand(std::string command)
	 {
		 this->command = command;
	 }
std::string Message::getCommand()
{
	return this->command;
}
std::string Message::getMsgContent()
{
	return this->MessageContent;
}
void Message::setMsgContent(std::string body)
{
	this->MessageContent = body;
}

void Message::setSize(size_t size)
	 {
		 this->size = size;
	 }
size_t Message::getSize()
{
	return this->size;
}
void Message::setFileName(std::string fileName)
	 {
		this->filename = fileName;
	 }

std::string Message::getSourceIp()
{
	return SourceIp;
}
std::string Message::getFileName()
{
	return this->filename;
}
void Message::setSourceIp(std::string SourceIP)
{
	this->SourceIp = SourceIP;
}
//get Message with out the body content
  std::string Message::getMessageWithoutContent()
 {
	 std::string httpMsg;
	 std::string ListenerPort_ = std::to_string(ListenerPort);
	 std::string MessageSize = std::to_string(size);
	 httpMsg = "SourcePort:" + SourceIp + "/n" + "filename:" + filename + "/n" + "IP:" + ListenerIp + "/n" + "ListenerPort:" + ListenerPort_ + "/n" + "size:"
		 + MessageSize + "/n" + "type:" + type + "/n" + "command:" + command + "/n" + "body:" 
		 ;

	 return httpMsg;
 }
  //get message with the body content.
  std::string Message::getMessage()
  {
	  std::string httpMsg;
	  std::string ListenerPort_ = std::to_string(ListenerPort);
	  std::string MessageSize = std::to_string(size);
	  httpMsg = "SourcePort:" + SourceIp + "/n" + "filename:" + filename + "/n" + "IP:" + ListenerIp + "/n" + "ListenerPort:" + ListenerPort_ + "/n" + "size:"
		  + MessageSize + "/n" + "type:" + type + "/n" + "command:" + command + "/n" + "body:" + MessageContent
		  ;
	  return httpMsg;
  }


#ifdef TEST_MESSAGE
  int main()
  {
	  std::cout<<"Test stub for checking";
	  setSourceIp("127.0.0.1");
  }
#endif