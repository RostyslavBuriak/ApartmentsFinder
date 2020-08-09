#include "webpage.h"
#include <iostream>

void webpage::SendRequest(const std::string& _location) {
	if (!hrequest) {
		SetupSession();
		SetupConnection();
	}
	if (location != _location) {
		location = std::move(_location);
		InternetCloseHandle(hrequest);
		OpenRequest();
	}
	if (!HttpSendRequestA(hrequest, 0, 0, 0, 0)) {
		throw webexcept("Send Request error!");
	}
	ReadResponse();
}


void webpage::OpenRequest() {
	hrequest = HttpOpenRequestA(
		hconnection,
		"GET", // METHOD
		location.c_str(),// URL
		NULL,
		NULL,
		NULL,
		INTERNET_FLAG_SECURE, //This flag is needed fo httpS
		0);
	if (!hrequest) {
		throw webexcept("HttpOpenRequest error!");
	}
}


void webpage::SetupConnection() {
	if ((hconnection = InternetConnectA(hsession,
		server.c_str(),
		INTERNET_DEFAULT_HTTPS_PORT, // THIS
		"",
		"",
		INTERNET_SERVICE_HTTP,
		0,
		0)) == NULL)
	{
		throw webexcept("InternetConnect error");
	}
}


void webpage::SetupSession() {
	if ((hsession = InternetOpen(L"Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)", //Initializes an application's use of the WinINet functions
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0)) == NULL) //checks if it has successfully worked
	{
		throw webexcept("InternetOpen error");
	}
}


void webpage::ReadResponse() {
	response.clear();
	const size_t sz = 512;
	char buffer[sz + 1];
	while (true) {
		DWORD dwBytesRead;
		BOOL bRead;


		bRead = InternetReadFile(
			hrequest,
			buffer,
			sz,
			&dwBytesRead);

		if (!bRead)
		{
			throw webexcept("InternetReadFile error!");
			break;
		}
		buffer[dwBytesRead] = 0;
		response += buffer;

		if (dwBytesRead == 0)
			break;
	}
}


std::string webpage::GetResponse() {
	return response;
}