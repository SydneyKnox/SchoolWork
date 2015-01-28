//------------------------------------------------------------------------
// Programmer: Sydney Knox
// Name: main.cpp
// Description: Main program for homework #6
// Pseudocode: This program is meant to model the sending of information
//             packets between two IP Addresses. Four classes were defined:
//             IPHost, Connection, Packet, and EncryptedConnection

//             The class IPHost is used to store an IP Address. A map is
//             created containing pairs of IPHosts and associated host
//             names.  The user is prompted to select a source IPHost and
//             a destination IPHost. The map is used to ensure that the
//             choices exist and do not contain the same IP Address.

//             The class Connection is used to simulate the connection
//             between the two IP Addresses.  It stores data members for
//             the source, the destination, and a message to be transmitted
//             (inputted by the user).  It also contains a vector of Packets
//             and the means to print these to the screen (to "transmit" them)
//             The class also contains the function necessary to break the
//             initial inputted message into chunks that are of the correct
//             size to be "transmitted."

//             The class Packet is used to simulate "packets" of information
//             to be sent over the "connection."  The initial message is
//             broken into packetSize and stored in an Object Packet with
//             its source and destination IP Addresses (IPHost)

//             The class EncryptedConnection is used to simulate an
//             Encrypted connection.  The user can either choose to use a
//             personalized encryption or the default.  To encrypt the message
//             a map is created that pairs one character with the second
//             character that it will be changed to in the encryption.  This
//             map is then used to "Encrypt" the original message before
//             "sending" it in packets.

//             These classes are implemented in main() where a menu is
//             available to the user that contains options to manipulate
//             the connection.
//------------------------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Connection.h"
#include "Packet.h"
#include "IPHost.h"
#include "EncryptedConnection.h"

void printMap(std::map<std::string, IPHost> nameList);

int main(void)
{
    //Variable to store users input from menu
    int menuInput=0;

    //instantiate the map containing Host names and addresses
     std::map< std::string, IPHost> hostsAndNames;

     //add objects to map
     hostsAndNames["uiowa.edu"]= IPHost(128, 255, 67, 14);
     hostsAndNames["google.com"]=IPHost(74,125,225,20);
     hostsAndNames["twitter.com"]=IPHost(199,16,156,43);
     hostsAndNames["news.slashdot.org"]=IPHost(216,34,181,48);
     hostsAndNames["www.engineering.uiowa.edu"]=IPHost(128,255,17,182);
     hostsAndNames["sports.yahoo.com"]=IPHost(98,139,199,204);
     hostsAndNames["m.twitter.com"]=IPHost(199,16,156,43);
     hostsAndNames["x.org"]=IPHost(18,7,25,161);

    //instantiate a Connection - will be empty
    Connection myConnection;

    //while loop with exit option 6
    while (menuInput != 6)
    {
                std::map< std::string, IPHost>::iterator myIter;//Iterator through a map of strings and IPHosts
                std::map< std::string, IPHost>::iterator myIter2;//Iterator 2 through a map of strings and IPHosts
                std::string inputSource;//string variable to hold a Source name
                std::string inputDest;//string variable to hold a Destination name
                std::string inputMessage;//string variable to hold an input message
                int found;//integer variable to indicate whether or not the inputted source name is a key in the map
                int foundDest;//int variable to indicate whether or not the inputted destination is a key

        //menu implementation
        std::cout << "\nMenu Options" << "\n---------------------------------" <<
                     "\n1: Show all known hosts" <<
                     "\n2: Set Source and destination hosts" <<
                     "\n3: Set Message to send" <<
                     "\n4: Send Message packets" <<
                     "\n5: Send encrypted message packets" <<
                     "\n6: Quit" << std::endl;
        std::cin >> menuInput;

        while(menuInput <1 || menuInput >6)
        {
            std::cout << "Input not valid: Please choose options 1-6" << std::endl;
            std::cin >> menuInput;
        }

        //switch statement for menuInput
        switch (menuInput)
        {
        case 1:
            //Show all known hosts
            printMap(hostsAndNames);
            break;
        case 2:
            //set found and foundDest to 0 to ensure while loops are entered
            found=0;
            foundDest =0;
            //while input source is not matched with a map key
            while(found==0)
            {
                std::cout << "\nEnter Source: ";
                std::cin >> inputSource;

                //iterate through map looking for a map to the inputted source
                for(myIter = hostsAndNames.begin(); myIter != hostsAndNames.end(); myIter++)
                {
                    if(myIter->first == inputSource)//if the host name matches the inputted source...
                    {
                        found=1; // change found to true
                        myConnection.setSource(hostsAndNames.at(inputSource));//set the inputted source to the IPHost at key
                        std::cout << "\n\nSource Set. " << std::endl;
                        break;
                    }
                }

                if(found==0)//if, after for loop, found still ==0, no key was found to match the inputted source
                {
                    std::cout << "Input not a valid source." << std::endl;
                }
            }

            while(foundDest==0)//while the inputted destination does not match a key
            {
                std::cout << "Enter Destination: ";
                std::cin >> inputDest;

                //set iterators to each key matching the inputted source and destination
                myIter2= hostsAndNames.find(inputSource);
                //std::cout << "afterinput source" << std::endl;
                myIter = hostsAndNames.find(inputDest);
                //std::cout << "after input dest find" << std::endl;
                while(myIter == hostsAndNames.end())
                {
                    std::cout << "Destination does not exist. Please enter a destination: " << std::endl;
                    std::cin >> inputDest;
                    myIter = hostsAndNames.find(inputDest);
                }
                //blocking while loop to ensure IP Addresses of source and Dest are not the same
                while((myIter->second).toString() == (myIter2->second).toString())
                {
                    std::cout << "\nDestination cannot be the same as the source.  Enter Destination: " << std::endl;
                    std::cin >> inputDest;
                    myIter = hostsAndNames.find(inputDest);

                    while(myIter == hostsAndNames.end())
                    {
                        std::cout << "Destination does not exist. Please enter a destination: " << std::endl;
                        std::cin >> inputDest;
                        myIter = hostsAndNames.find(inputDest);
                    }
                }

                //iterate through the hosts and names map to find a match for the inputted destination
                for(myIter = hostsAndNames.begin(); myIter != hostsAndNames.end(); myIter++)
                {
                    //std::cout << "Iterating" << std::endl;
                    if(((myIter->first) == inputDest))
                    {
                        foundDest=1;
                        myConnection.setDestination(hostsAndNames.at(inputDest));
                        break;
                    }
                }
                //set the iterator myIter to the location of the inputted Destination
                myIter = hostsAndNames.find(inputDest);



                //if the key for the inputted destination is still not found then it's not a valid dest
                if(foundDest==0)
                {
                    std::cout << "Input not a valid Destination." << std::endl;
                }
            }

            myConnection.setMessageString("");

            break;

        case 3:
            if(myConnection.getSource().toString() == "0.0.0.0" || myConnection.getDest().toString() == "0.0.0.0")
            {
                std::cout << "Please set source and destination before setting message" << std::endl;
                break;
            }
            //Prompt user for a message to send; input will terminate when they input a \n
            std::cout << "\nEnter the message to send: " << std::endl;
            std::cin.ignore();
            std::getline(std::cin, inputMessage);

            //set message in connection
            myConnection.setMessageString(inputMessage);
            std::cout << "\nMessage Set.  " << std::endl;
            break;

        case 4:
            //send message packets
            //convert inputted message to packets of lenght packetSize
            myConnection.convertToPackets();
            std::cout << "\nMessage Packets\n" << std::endl;
            //if the message string is empty, notify user
            if(myConnection.packets.empty() == 1)
            {
                std::cout << "Message string is empty. No packets exist" << std::endl;
            }
            else//iterate through the packets vector and print them out
            {
                for(unsigned int i=0; i<(myConnection.packets.size());i++)
                {
                    std::cout << "Packet" << (i+1) << ":   " ;
                    myConnection.packets.at(i).transmitPacket();
                }
            }
            break;

        case 5:
            //send encrypted message packets
            if(1)
            {   //created object
                EncryptedConnection myEncryption(myConnection.getSource(), myConnection.getDest(), myConnection.getMessage());

                    unsigned int i;
                    std::string initialMessage = myConnection.getMessage();
                    char toAdd;
                    std::string finalMessage;

                    myEncryption.createMap();
                    //std::map<char, char> encryptionCode;


                    for(i=0; i<(myConnection.getMessage()).length(); i++)//for i=0; i<(length of initial message); i++
                    {
                        //append each newly encrypted letter to the final message

                        toAdd = myEncryption.encryptionCode.find(initialMessage.at(i))->second;

                        finalMessage.insert(finalMessage.end(), 1, toAdd);
                    }
                    myConnection.setMessageString(finalMessage);
                    //myEncryption.setEncryptedMessage(finalMessage);
                    //std::cout << finalMessage << std::endl;

                    myConnection.convertToPackets();
                    std::cout << "\nMessage Packets\n" << std::endl;
                    //if the message string is empty, notify user
                    if(myConnection.packets.empty() == 1)
                    {
                        std::cout << "Message string is empty. No packets exist" << std::endl;
                    }
                    else//iterate through the packets vector and print them out
                    {
                        for(unsigned int i=0; i<(myConnection.packets.size());i++)
                        {
                            std::cout << "Packet" << (i+1) << ":   " ;
                            myConnection.packets.at(i).transmitPacket();
                        }
                    }
            }
            break;
        case 6:
            //quit
            break;
        }
    }
    return 0;
}
/*********************************************************
/Function: printMap
/Input: a map consisting of std::string's and IPHosts
/Output: void
/Purpose: to print the IP addresses and their associated
         host names to the screen (option 1)
*********************************************************/
void printMap(std::map<std::string, IPHost> nameList)
{
    std::map<std::string, IPHost>::iterator myIter;

    for(myIter = nameList.begin(); myIter != nameList.end(); myIter++)
            {
                std::string hostName = myIter->first;
                IPHost IPAddress = myIter->second;
                std::cout << "Host Name " << hostName << " has IP Address " << IPAddress.toString() << std::endl;
            }
}
