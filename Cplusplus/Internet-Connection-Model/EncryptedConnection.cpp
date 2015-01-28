//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: EncryptedConnection.cpp
// Description: Implementation of EncryptedConnection class
//------------------------------------------------------------------------
#include "EncryptedConnection.h"
#include "Connection.h"
#include "Packet.h"
#include "IPHost.h"
#include <iostream>
#include <map>
#include <vector>

//Constructor (with personalized encryption)
EncryptedConnection::EncryptedConnection(IPHost source, IPHost dest, std::string initialMessage, std::string encryptFrom, std::string encryptTo)
{
    //set source, dest, and initial message from myConnection
    Connection::setSource(source);
    Connection::setDestination(dest);
    Connection::setMessageString(initialMessage);

    unsigned int i;

    //instantiate map members
    for(i=0; i<encryptFrom.length(); i++)
    {
        encryptionCode[encryptFrom.at(i)] = encryptTo.at(i);
    }

    for(i=0; i<initialMessage.length(); i++)//iterate through initial message, resetting each char to the new one from the map
    {
        (getMessage()).at(i) = (encryptionCode.find((getMessage()).at(i)))->second;
    }
    //std::cout << "Encrypted Message: " << getMessage() << std::endl;
}

//Constructor (no personalized encryption)
EncryptedConnection::EncryptedConnection(IPHost source, IPHost dest, std::string initialMessage)
{
    Connection::setSource(source);
    Connection::setDestination(dest);
    Connection::setMessageString(initialMessage);

    createMap();

    /*unsigned int i;
    for(i=0; i<initialMessage.length(); i++)//iterate through initial message, resetting each char to the new one from the map
    {
        (getMessage()).at(i) = (encryptionCode.find((getMessage()).at(i)))->second;
    }*/
    //std::cout << "Encrypted Message: " << getMessage() << std::endl;
}

//Constructor with no inputted string
EncryptedConnection::EncryptedConnection(IPHost source, IPHost dest)
{
    Connection::setSource(source);
    Connection::setDestination(dest);
    Connection::setMessageString("");

    createMap();
    //std::cout << "Encrypted Message: " << getMessage() << std::endl;
}

//member function: create default encryption map
void EncryptedConnection::createMap()
{
   //uppercase letter encryption
   int j='N';
   int i;
   for(i='A'; i<'['; i++)
   {
       if(j=='[')
       {
           j='A';
       }
       encryptionCode[i]=j;
       j++;

   }
   j='n';

   //lowercase letter encryption
   for(i='a'; i<'{'; i++)
   {
       if(j=='{')
       {
           j='a';
       }
       encryptionCode[i]=j;
       j++;

   }
}
