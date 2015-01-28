//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: Packet.cpp
// Description: Implementation of Packet class
//------------------------------------------------------------------------

// TODO: YOUR CODE HERE
#include <sstream>
#include "Packet.h"
#include <iostream>
#include <string>

//Constructor
Packet::Packet(IPHost source, IPHost dest, const std::string& messageChunk){

    m_source= source;
    m_dest= dest;
    m_messageChunk= messageChunk;

    MessageString = setMessageString(m_messageChunk);

}

//default constructor
Packet::Packet()
{
    m_source = IPHost();
    m_dest = IPHost();
    m_messageChunk = "";

    MessageString = setMessageString(m_messageChunk);
}

//member function: set string in Packet object
std::string Packet::setMessageString(std::string h){
    if(h.size()>packetSize)//if the message chunk passed in is > the specified packet size
    {
        h.resize(packetSize); //resize it
    }
return h;
}

//print packet to screen in main()
void Packet::transmitPacket() const{

    std::cout << m_source.toString() <<"     "<< m_dest.toString()
         << "    " << MessageString << std::endl;
}
Enter file contents here
