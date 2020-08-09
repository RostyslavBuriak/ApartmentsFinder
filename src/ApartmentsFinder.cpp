#include <iostream>
#include "olxparser.h"
#include <assert.h>


void StartWSA() {
	WSADATA wsaData;
	assert(WSAStartup(0x202, &wsaData) == 0, "WSAStartup failed!"); //Specify WSA for the programm; returns 0 if failed
}


int main()
{
	olxparser olx;

	try
	{
		olx.start();
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << "The error is: " << GetLastError() << std::endl;
	}
	WSACleanup();
}
