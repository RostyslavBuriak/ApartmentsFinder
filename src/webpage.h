#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <wininet.h>
#include <string>

#pragma comment(lib,"WS2_32")
#pragma comment(lib, "wininet.lib")

class webpage
{
public:
	webpage(std::string _serv) :hrequest(NULL), hsession(NULL), hconnection(NULL), response(""),location(""),server(_serv){};

	webpage(const webpage&) = delete;
	webpage(webpage&&) = delete;

	webpage& operator=(const webpage&) = delete;
	webpage& operator=(webpage&&) = delete;

	~webpage() { InternetCloseHandle(hrequest); InternetCloseHandle(hsession); InternetCloseHandle(hconnection);};

	class webexcept : public std::exception{
	public:
		webexcept(std::string _er = "") :er(_er) {}

		const char* what() const throw() {
			return er.c_str();
		}
	private:
		std::string er;
	};

	void SendRequest(const std::string&); //Send request to the webpage
	std::string GetResponse(); //Get response as html code of the web page
private:
	HINTERNET hrequest,hsession,hconnection;
	std::string response, //response from web page in html
		server, //server name 
		location; //location of web page

	void ReadResponse(); //Reads an html page in to response string
	void SetupSession(); //Setups a session
	void SetupConnection(); //Setups a connection with web page
	void OpenRequest(); //Makes hrequest valid
};

