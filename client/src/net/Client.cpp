#include "net/Client.h"
#include "UdpSocket.h"
#include <string>
#include "MessageStructs.h"

bool Client::ConnectToServer(unsigned int& networkId, std::string listenPortString, std::string addressAndPortString)
{
	unsigned short portToOpen = std::stoi(listenPortString);

	size_t last = 0;
	size_t next = 0;
	unsigned char partA;
	unsigned char partB;
	unsigned char partC;
	unsigned char partD;
	unsigned short port;

	//IPs have exactly 4 parts, delimited by a '.'
	size_t currentPartIndex = 0;
	size_t lastPartIndex = 0;

	currentPartIndex = addressAndPortString.find('.', lastPartIndex);
	partA = std::stoi(addressAndPortString.substr(lastPartIndex, currentPartIndex-lastPartIndex));

	lastPartIndex = currentPartIndex + 1;
	currentPartIndex = addressAndPortString.find('.', lastPartIndex);
	partB = std::stoi(addressAndPortString.substr(lastPartIndex, currentPartIndex-lastPartIndex));

	lastPartIndex = currentPartIndex + 1;
	currentPartIndex = addressAndPortString.find('.', lastPartIndex);
	partC = std::stoi(addressAndPortString.substr(lastPartIndex, currentPartIndex-lastPartIndex));

	//Last part is ended by a ':', followed by the port
	lastPartIndex = currentPartIndex + 1;
	currentPartIndex = addressAndPortString.find(':', lastPartIndex);
	partD = std::stoi(addressAndPortString.substr(lastPartIndex, currentPartIndex-lastPartIndex));

	lastPartIndex = currentPartIndex + 1;
	port = std::stoi(addressAndPortString.substr(lastPartIndex));

	udpSocket = new UdpSocket(portToOpen);

	if (udpSocket->Initialize())
	{
		//if (udpSocket.SetSendAddress(127, 0, 0, 1, 2222))
		if (udpSocket->SetSendAddress(partA, partB, partC, partD, port))
		{
			//Get a connection
			MSG_CONNECT_REQUEST connectionRequest;
			std::cout<<"Trying connection at " << addressAndPortString <<std::endl;
			if (udpSocket->Send(&connectionRequest, sizeof(MSG_CONNECT_REQUEST)))
			{
				unsigned int fromAddr;
				unsigned short fromPort;

				//try to connect to server
				while(true) //replace with timeout
				{
					if (udpSocket->RecieveMessage(dataBuffer, dataBufferSize, &fromAddr, &fromPort))
					{
						std::cout<<"Message recieved from " << fromAddr << ":" << fromPort <<std::endl;

						MSG_TYPE messageType = MESSAGE::DetermineMessageType(dataBuffer, dataBufferSize);
						std::cout<<"\tMessage type: " << messageType << std::endl;
						
						if (messageType == MSG_TYPE::CONNECT_RESPONSE)
						{
							MSG_CONNECT_RESPONSE connectResponse(dataBuffer, dataBufferSize);
							CONNECT_RESP responseType = connectResponse.response;

							if (responseType == CONNECT_RESP::ACCEPTED)
							{
								networkId = connectResponse.networkId;
								std::cout<<"Connected to server. Network ID: " << networkId << std::endl;
								return true;
							}
							else
							{
								std::cout<<"Could not connect to server" << std::endl;
								return false;
							}
						}
					}
				}
			}
			else
			{
				std::cout<<"Failed to send connection packet"<<std::endl;
				return false;
			}
		}
		else
		{
			std::cout<<"Could not set send address"<<std::endl;
			return false;
		}
	}
	else
	{
		std::cout<<"Could not initialize socket"<<std::endl;
		return false;
	}
}

void Client::SendMessage(unsigned int networkId, std::string message)
{
	//std::cout<<"Message to send: ";
	//std::string message;
	//getline(std::cin, message);
	std::cout<<"Sending message..."<<std::endl;

	MSG_TEXT messagePacket(networkId, message);
	int size = sizeof(MSG_TEXT);
	if (udpSocket->Send(&messagePacket, size))
	{
		bool receivedResponse = false;
		
		unsigned int fromAddr;
		unsigned short fromPort;

		while(!receivedResponse)
		{
			if (udpSocket->RecieveMessage(dataBuffer, dataBufferSize, &fromAddr, &fromPort))
			{
				std::cout<<"Message recieved from " << fromAddr << ":" << fromPort <<std::endl;

				MSG_TYPE messageType = MESSAGE::DetermineMessageType(dataBuffer, dataBufferSize);
				std::cout<<"\tMessage type: " << messageType << std::endl;

				switch(messageType)
				{
					case MSG_TYPE::ACK:
					{
						std::cout<<"\tMessage ACK recieved"<<std::endl;
						break;
					}
					default:
						break;
				}
				receivedResponse = true;
			}
		}
	}
	else
	{
		std::cout<<"Failed to send message packet"<<std::endl;
	}
	
}
