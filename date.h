/*Primitive date class*/
#pragma once
#include <chrono>
#include <ctime>
#include <time.h>

class date
{
public:
	date() :
		day(0), month(0),year(0),hour(0),minute(0){
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		tm tmp;
		::localtime_s(&tmp, &now_c);
		/*time_t t = time(NULL);
		tm tmp;
		gmtime_s(&tmp, &t);*/
		year = tmp.tm_year + 1900;
		month = tmp.tm_mon + 1 ;
		day = tmp.tm_mday;
		hour = tmp.tm_hour; //GMT conversation
		minute = tmp.tm_min;
	}

	date(unsigned _day,unsigned _month, unsigned _year,unsigned _hour = 0,unsigned _minute = 0):
		day(_day),month(_month),year(_year),hour(_hour),minute(_minute)
	{}

	date(const date&) = default;
	date(date&&) = default;

	date& operator=(const date&) = default;
	date& operator=(date&&) = default;

	bool operator<(const date&);
	bool operator>(const date&);
	bool operator==(const date&);

	unsigned day;
	unsigned month;
	unsigned year;
	unsigned hour;
	unsigned minute;
};

