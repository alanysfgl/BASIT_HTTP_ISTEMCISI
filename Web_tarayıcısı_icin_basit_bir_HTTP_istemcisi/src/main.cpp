#include<iostream>
#include"function.h"



int main()
	{
	
	intializingWinsock();

	std::string url;
	std::cout << "lutfen URL giriniz:";
	std::cin >> url;
	SOCKET sock=CreateSocket(url);

	sendHTTPrequest(sock,url);
	receiveResponse(sock);
	


	closesocket(sock);
	cleanupWinsock();
	return 0;
	}