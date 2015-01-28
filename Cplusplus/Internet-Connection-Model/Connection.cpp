//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: Connection.cpp
// Description: Implementation of Connection class
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include "Connection.h"
#include "Packet.h"
#include "IPHost.h"
#include <iostream>
/***Constructor used if all information is inputted***/
/*Input: IPHosts source & dest
         std::string initial message
  Output: create an object of class Connection
*****************************************************/
Connection::Connection(IPHost source, IPHost dest, const std::string& initialMessage)
{
   m_source = source;
   m_dest = dest;
   m_message = initialMessage;
   convertToPackets();
}

/***Constructor used if no initial message is  inputted***/
/*Input: IPHosts source & dest
  Output: creates an object of class Connection with an
          empty string for m_message
**********************************************************/
Connection::Connection(IPHost source, IPHost destination)
{
    m_source = source;
    m_dest = destination;
    m_message = "";//message set to blank

}

/***Member function to set the private source***/
/*Input: IPHost Source
  Output: void
  Purpose: set the private data member m_source
************************************************/
void Connection::setSource(IPHost source)
{
    m_source = source;
}

/***Member function to set the private destination***/
/*Input: IPHost dest
  Output: void
  Purpose: set the private data member m_dest
*****************************************************/
void Connection::setDestination(IPHost dest)
{
    m_dest = dest;
}

/***Member function to set the private string***/
/*Input: std::string message
  Output: void
  Purpose: set the private data member m_message
************************************************/
void Connection::setMessageString( std::string message)
{
    m_message = message;

}

/***Member function to print the packet information***/
/*Input: none
  Output: void
  Purpose: to print packets and their information to
          the screen in main()
******************************************************/
void Connection::transmit() const
{
    unsigned int i;
    for(i=0;i<packets.size();i++)
    {
        (packets.at(i)).transmitPacket();
    }
}

/***Member function to Convert an inputted message to packets***/
/*Input: none
  Output: void
  Purpose: to chunk the inputted message into Packet objects
          with an IPHost source and dest and message chunks of
          a certain size
****************************************************************/
void Connection::convertToPackets()
{
    std::string packetString = "";

    //if the packets vector is not empty
    if(packets.empty() == 0)
    {
        packets.clear();//then clear the vector
    }
    int subStrBegin=0;
    //iterate through the message, pushing a Packet object into the packets vector every packetSize characters
    for(unsigned int i=0;i<(m_message.length());i++)
    {
        if (((i+1)%(Packet::packetSize) ==0)/*if it's at 12 char's*/ || i==((m_message.length())-1)/*if it's at the end of the message*/)
        {
           Packet newPacket(m_source, m_dest, (m_message.substr(subStrBegin, 12)));

           packets.push_back(newPacket);
           subStrBegin=i+1;
        }
    }
}
