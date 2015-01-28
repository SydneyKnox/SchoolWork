//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: EncryptedConnection.h
// Description: Header file for the EncryptedConnection class
//------------------------------------------------------------------------
#ifndef ENCRYPTEDCONNECTION_H
#define ENCRYPTEDCONNECTION_H
#include <map>
#include "Connection.h"
/**Inherited Class from Connection**/
class EncryptedConnection : public Connection{
public:
    //Constructor (with personalized encryption)
    EncryptedConnection(IPHost source, IPHost dest, std::string initialMessage, std::string encryptFrom, std::string encryptTo);

    //Constructor (default encryption)
    EncryptedConnection(IPHost source, IPHost dest, std::string initialMessage);//define with RO13

    //Constructor (no initial string)
    EncryptedConnection(IPHost source, IPHost dest);

    //Map of paired characters for encryption
    std::map<char, char> encryptionCode;

    //Member function: set private data member encryptedMessage
    void setEncryptedMessage(std::string EnMe) {encryptedMessage = EnMe;}

    //create default encryption map
    void createMap();
private:
    //private data member to store the encrypted message
    std::string encryptedMessage;

};

#endif
