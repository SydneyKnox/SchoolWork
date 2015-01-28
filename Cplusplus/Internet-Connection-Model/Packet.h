//----------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: Packet.h
// Description: Header file for the Packet class
//----------------------------------------------------------------------
#ifndef PACKET_H
#define PACKET_H

#include "IPHost.h"

class Packet{
public:
    //data member: define packet size
    static const unsigned int packetSize=12;

    //member function: set message string
    std::string setMessageString(std::string h);

    //member function: set source
    void setSource(IPHost source) {m_source = source;}

    //member function: set destination
    void setDest(IPHost dest) {m_dest = dest;}

    //Constructor
    Packet(IPHost source, IPHost dest, const std::string& messageChunk);

    //default constructor
    Packet();

    //print packets to screen in main()
    void transmitPacket() const;
private:
    //data member IPHost source
    IPHost m_source;

    //data member IPHost destination
    IPHost m_dest;

    //data member: chunk of message for this packet
    std::string m_messageChunk;

    //data member: entire inputted message
    std::string MessageString;

};

#endif
