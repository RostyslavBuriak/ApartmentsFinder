#include <iostream>
#include "olxparser.h"
#include <assert.h>
#include <thread>

void StartWSA() {
	WSADATA wsaData;
	assert(WSAStartup(0x202, &wsaData) == 0, "WSAStartup failed!"); //Specify WSA for the programm; returns 0 if failed
}


int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	std::cout << "Insert the date DD MM YY : ";
	unsigned day = 10, month = 8, year = 2020;
	//std::cin >> day >> month >> year;
	olxparser olx({ day,month,year });;

	try
	{
		while (true) {
			olx.start();
			olx.SetDate(date());
			std::this_thread::sleep_for(std::chrono::minutes(15));
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << "The error is: " << GetLastError() << std::endl;
	}
	WSACleanup();
}
