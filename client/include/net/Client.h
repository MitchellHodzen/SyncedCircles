#pragma once
#include <iostream>
#include <winsock2.h>
#include <string>
#include "UdpSocket.h"

class Client
{
public:
	~Client()
	{
		delete udpSocket;
	};
	bool ConnectToServer(unsigned int& networkId, std::string listenPortString, std::string addressAndPortString);
	void SendMessage(unsigned int networkId, std::string message);
private:
	UdpSocket* udpSocket;

	unsigned int serverAddress;
	unsigned int serverPort;
	static const unsigned int dataBufferSize = 255;
	unsigned char dataBuffer[dataBufferSize];
};

