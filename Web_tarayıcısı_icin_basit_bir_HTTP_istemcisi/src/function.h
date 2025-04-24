#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<fstream>
#include<string>
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

void sendHTTPrequest(SOCKET connet ,const std::string& URL,std::string method,const std::string postData)
{
	//-----------------------URL PARÇALAMA KISMI-----------------------------------

	std::string fullURL = URL;
	if (fullURL.find("http://") == std::string::npos && fullURL.find("https://") == std::string::npos) {
		fullURL = "http://" + fullURL;
	}

	// URL'yi doðru þekilde iþleyin, sadece path kýsmýný almak gerekebilir
	size_t pos = fullURL.find("://");
	if (pos != std::string::npos) {
		fullURL = fullURL.substr(pos + 3); // "http://" ya da "https://" kýsmýný kaldýr
	}

	// Host ve path ayýrma
	std::string host;
	std::string path = "/";
	size_t pathPos = fullURL.find("/");
	if (pathPos != std::string::npos) {
		host = fullURL.substr(0, pathPos);
		path = fullURL.substr(pathPos);
	}
	else {
		host = fullURL;
	}

	//-----------------------GETKISMI-------------------------------------

	std::string request;
	if (method == "POST") {
		request = "POST " + path + " HTTP/1.1\r\n";
	}
	else {
		request = "GET " + path + " HTTP/1.1\r\n";
	}
	request += "Host: " + host + "\r\n";
	request += "User-Agent: MySimpleHttpClient/1.0\r\n";
	request += "Connection: close\r\n";
	//-----------------POST KISMI----------------------------

	if (method == "POST") {
		request += "Content-Type: application/x-www-form-urlencoded\r\n";
		request += "Content-Length: " + std::to_string(postData.length()) + "\r\n";
		request += "\r\n"; // Header ve Body arasýndaki boþluk
		request += postData;
	}
	else {
		request += "\r\n"; // GET isteði için sadece header bitimi
	}
	


	
	send(connet, request.c_str(), request.length(), 0);
}

void receiveResponse(SOCKET connet) {
	const int bufferSize = 1024;
	char buffer[bufferSize];
	std::string response;

	int bytesReceived = 0;

	std::string bodyPart;

	do
	{
		bytesReceived = recv(connet, buffer, bufferSize, 0);
		if (bytesReceived > 0)
		{
			response.append(buffer, bytesReceived);
		}
	} while (bytesReceived > 0);

	std::string::size_type pos = response.find("\r\n\r\n");

	if (pos != std::string::npos) {
		std::string headers = response.substr(0, pos);
		std::string body = response.substr(pos + 4); // +4 çünkü "\r\n\r\n" 4 karakterdir

		std::cout << "[Header]:\n" << headers << "\n";	
		std::cout << "[Body]:\n" << body << "\n";
		bodyPart += body;
		
		while ((bytesReceived = recv(connet, buffer, bufferSize, 0)) > 0) {
			bodyPart.append(buffer, bytesReceived);
		}
	}

	else {
		std::cerr << "HTTP yanýtý geçersiz veya eksik!\n";
	}
  
	std::ofstream out("txt.html");
	if (out.is_open()) {
		out << bodyPart;
	}
	else {
		std::cerr << "Dosya oluþturulamadý!\n";
	}

}

void PostHttpRequest(SOCKET connet,const std::string postData)
{





}