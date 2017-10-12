// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;
int main()
{

	// initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wSOk = WSAStartup(ver, &wsData);

	if (wSOk != 0) {
		cout << "Cannot initialize winsock" << endl;
		return;
	}

	// create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET) {
		cout << "Can't create socket" << endl;
		return;
	}


	// Bind socket to and ip address and port

	sockaddr_in Addr;
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(300000);
	Addr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	bind(listening, (sockaddr*)&Addr, sizeof(Addr));


	// Tell winsock the socket is for lsitening
	listen(listening, SOMAXCONN);
	

	// wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];     // clients remote name
	char service[NI_MAXHOST];  // port client is connected on 

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);


	if (clientSocket == INVALID_SOCKET) {

		cout << "CANNOT CONNECT" << endl;

	}


	// cose listening socket
	
	closesocket(listening);

	// while loop: accept and echo message back to client 

	while (true) {
		char buf[4096];
		ZeroMemory(buf, 4096);

			// wait for client to send data

		int dataRecieved = recv(clientSocket, buf, 4096, 0);

		if (dataRecieved == SOCKET_ERROR) {
			cout << "Error recieving data" << endl;
			break;
		}
		else if (dataRecieved == 0) {
			cout << "client disconnected" << endl;
			break;
		}
		

			
			
		send(clientSocket, buf, dataRecieved + 1, 0);

	}

	// close the sock

	closesocket(clientSocket);

	// shutdown sock
	WSACleanup();




    return 0;
}

