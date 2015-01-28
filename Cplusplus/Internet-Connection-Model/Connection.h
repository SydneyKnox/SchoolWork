Enter file contents here//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: Connection.h
// Description: Header file for the Connection class
//------------------------------------------------------------------------
#ifndef CONNECTION_H
#define CONNECTION_H
#include <vector>
#include <string>
#include "Packet.h"

class Connection{
public:
/**Public Group**/
    //Constructor with defaults
    Connection(IPHost source = IPHost(), IPHost dest = IPHost(), const std::string& initialMessage = "");

    //Constructor without an input string
    Connection(IPHost source, IPHost destination);

    //member function to set source
    void setSource(IPHost source);

    //member function to set destination
    void setDestination(IPHost dest);

    //member function to set message string
    void setMessageString(std::string message);

    //member function to obtain private member m_source
    IPHost getSource(){return m_source;};

    //member function to obtain private member m_dest
    IPHost getDest(){return m_dest;};

    //member function to obtain private member m_message
    std::string getMessage(){return m_message;};

    //member function to convert Connection information to packets vector
    void convertToPackets();

    //member function to print packets vector to screen in main
    void transmit() const;

    //packets vector
    std::vector<Packet> packets;

private:
    //data member to hold IP source
    IPHost m_source;

    //data member to hold IP destination
    IPHost m_dest;

    //data member to hold user's message
    std::string m_message;

};

#endif
