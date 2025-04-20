#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>

#pragma comment(lib,"ws2_32.lib")// winsock kütüphanesini projeye baðlar




void intializingWinsock()
{

	WSAData WsData;
	int result = WSAStartup(MAKEWORD(2, 2), &WsData);

	if (result != 0)
	{
		std::cerr << "WSAstartup is failed";
		exit(1);
	}

	std::cout << "winsock baslatildi" << std::endl;

}


void cleanupWinsock() {
	WSACleanup();
}

SOCKET CreateSocket(const std::string& host)
{



	SOCKET connet = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (connet == INVALID_SOCKET)
	{
		std::cerr << "Socket creation failed.error cod:" << WSAGetLastError() << std::endl;

		exit(1);
	}





	hostent* server = gethostbyname(host.c_str());
	if (server == nullptr)
	{
		std::cerr << "sunucu adý cozumlenmedi" << std::endl;
		exit(1);

	}

	sockaddr_in serveradrr;
	serveradrr.sin_family = AF_INET;
	serveradrr.sin_port = htons(80); // HTTP portu
	serveradrr.sin_addr = *((in_addr*)server->h_addr_list[0]);


	if (connect(connet,(const struct sockaddr*)&serveradrr,sizeof(serveradrr))<0)
	{
		std::cerr << "connection is failed" << std::endl;
		exit(1);
	}
	return connet;
}

void sendHTTPrequest(SOCKET connet ,const std::string& URL)
{

	std::string fullURL = URL;
	if (fullURL.find("http://") == std::string::npos && fullURL.find("https://") == std::string::npos) {
		fullURL = "http://" + fullURL;
	}

	// URL'yi doðru þekilde iþleyin, sadece path kýsmýný almak gerekebilir
	size_t pos = fullURL.find("://");
	if (pos != std::string::npos) {
		fullURL = fullURL.substr(pos + 3); // "http://" ya da "https://" kýsmýný kaldýr
	}

	size_t pathPos = fullURL.find("/");
	if (pathPos == std::string::npos) {
		fullURL += "/"; // Eðer URL'de bir yol yoksa, ekleyin
	}



	std::string request = "GET /" + fullURL.substr(fullURL.find("/")) + " HTTP/1.1\r\n";
	request += "Host: " + fullURL.substr(0, fullURL.find("/")) + "\r\n";  // Host sadece domain kýsmý
	request += "User-Agent: MySimpleHttpClient/1.0\r\n";
	request += "Connection: close\r\n";
	request += "\r\n"; // Son boþ satýr

	// Ýstek gönder
	send(connet, request.c_str(), request.size(), 0);
}

void receiveResponse(SOCKET connet) {
	const int bufferSize = 1024;
	char buffer[bufferSize];
	std::string response;

	int bytesReceived = 0;

	do
	{
		bytesReceived = recv(connet, buffer, bufferSize, 0);
		if (bytesReceived > 0)
		{
			response.append(buffer, bytesReceived);
		}
	} while (bytesReceived > 0);

	std::string::size_type pos = response.find("\r\n\r\n");

	if (pos != std::string::npos)
	{
		std::string htmlContent = response.substr(pos + 4); // 4 çünkü "\r\n\r\n" 4 karakter
		std::cout << "=== HTML ÝÇERÝÐÝ ===" << std::endl;
		std::cout << htmlContent << std::endl;
	}
	else
	{
		std::cerr << "HTML içeriði ayrýþtýrýlamadý." << std::endl;
	}



}
