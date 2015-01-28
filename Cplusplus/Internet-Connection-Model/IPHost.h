//----------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: IPHost.h
// Description: Header file for the IPHost class
//----------------------------------------------------------------------
#ifndef IPHOST_H
#define IPHOST_H
#include <vector>

class IPHost {
public:
    //Constructor
    IPHost(int ip0, int ip1, int ip2, int ip3);

    //default Constructor
    IPHost();

    //Convert the integers to a string containing full IP address
    std::string toString() const;

    //returns a portion of the IP address
    int getInteger(int numInt) const {return m_integers.at(numInt); };

    //equality operator
    bool operator==(const IPHost& h) const;

private:
    //data member- vector of integer components
    std::vector<int> m_integers;
};

#endif
