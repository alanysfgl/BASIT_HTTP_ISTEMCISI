#include<iostream>
#include"function.h"



int main()
	{
	
	intializingWinsock();

	std::string url;
	std::string postData;

	std::cout << "lutfen URL giriniz:";
	std::cin >> url;
	std::cout << "\n";
	std::cout << "eklemek istdeiðiniz veriyi giriniz";
	std::cin >> postData;

	SOCKET sock=CreateSocket(url);

	sendHTTPrequest(sock,url,"POST", postData);
	
	receiveResponse(sock);
	


	closesocket(sock);
	cleanupWinsock();
	return 0;
	}