// HelloWorldWinClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "string.h"
#include "stdlib.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"Ws2_32.lib")
#include "WinSock2.h"


#define IP "127.0.0.1"
#define PORT 3000
#define WRITE_DATA "Hello World!"


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa;

	printf_s("initiailising Winsock\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf_s("Failed. Error Code : %d", WSAGetLastError());
		return 0;
	}

	int ret = -1;
	int clientSock;
	struct sockaddr_in serverAddr;

	if ((clientSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		goto leave;
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	serverAddr.sin_port = htons(PORT);

	if ((ret = connect(clientSock, (struct sockaddr*)&serverAddr,
		sizeof(serverAddr)))) {
		perror("connect");
		goto error;
	}

	if ((ret = send(clientSock, WRITE_DATA, sizeof(WRITE_DATA), 0)) <= 0) {
		perror("send");
		ret = -1;
	}
	else
		printf_s("Wrote '%s' (%d Bytes)\n", WRITE_DATA, ret);

error:
	closesocket(clientSock);
leave:

	getchar();
	return ret;

	
}

