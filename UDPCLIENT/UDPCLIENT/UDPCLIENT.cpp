#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#pragma comment (lib,"WS2_32.lib")


int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2,0);
	::WSAStartup(w,&data);
	SOCKET s,s2;

	//Create a udp socket
	s = ::socket(AF_INET,SOCK_DGRAM,0);
	s2 = ::socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in server_addr, client_addr, server_addr2;
	int num = sizeof(client_addr);
	char buff[255] = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(80);
	server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.4");

	//Bind the client socket with its own ip and port
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(80);
	client_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.12");
	bind(s2,(sockaddr*)&client_addr,sizeof(client_addr));

	printf("UDP-CLIENT START...\r\n");
	char sztext[] = "hello,here is client end\r\n";
	//Send msg

	//Here needs a while
	while (true)
	{
		::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&server_addr, num);
			
		if (::recvfrom(s, buff, 255, 0, (sockaddr*)&server_addr2, &num) == 0)
		{
			printf("failed to recv from udp server... ...\n");
		}
		printf("UDP server say:%s\r\n", buff);
		::Sleep(1000);
	}


	::closesocket(s);
	::WSACleanup();
	

	if(getchar())
	{
		return 0;
	}
	else
	{
		::Sleep(100);
	}


}