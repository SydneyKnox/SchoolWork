//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: IPHost.cpp
// Description: Implementation of the IPHost class
//------------------------------------------------------------------------

#include <sstream>
#include "IPHost.h"
#include <iostream>

//Constructor
IPHost::IPHost(int ip0, int ip1, int ip2, int ip3){

    m_integers.push_back(ip0);
    m_integers.push_back(ip1);
    m_integers.push_back(ip2);
    m_integers.push_back(ip3);

}
//Default constructor
IPHost::IPHost(){
    m_integers.push_back(0);
    m_integers.push_back(0);
    m_integers.push_back(0);
    m_integers.push_back(0);
}

//Convert IP address to string
std::string IPHost::toString() const {

    std::stringstream IPAddress;

    IPAddress << getInteger(0) << "." << getInteger(1) << "." << getInteger(2) << "." << getInteger(3);
    return IPAddress.str();
}

//equality operator
bool IPHost::operator==(const IPHost& h) const{

    return (h.getInteger(0)==getInteger(0) &&
            h.getInteger(1)==getInteger(1) &&
            h.getInteger(2)==getInteger(2) &&
            h.getInteger(3)==getInteger(3));
}
