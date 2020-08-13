#include "date.h"


bool date::operator<(const date& _date) {
	if (_date.year > this->year) 
		return true;

	if (_date.year == this->year && _date.month > this->month) 
		return true;

	if (_date.month == this->month && _date.day > this->day)
		return true;

	if (_date.day == this->day && _date.hour > this->hour)
		return true;

	if (_date.hour == this->hour && _date.minute > this->minute)
		return true;

	return false;
}


bool date::operator>(const date& _date) {
	if (_date.year < this->year)
		return true;

	if (_date.year == this->year && _date.month < this->month)
		return true;

	if (_date.month == this->month && _date.day < this->day)
		return true;

	if (_date.day == this->day && _date.hour < this->hour)
		return true;

	if (_date.hour == this->hour && _date.minute < this->minute)
		return true;

	return false;
}


bool date::operator==(const date& _date) {
	if (_date.year == this->year) {
		if (_date.month == this->month) {
			if (_date.day == this->day) {
				if (_date.hour == this->hour) {
					if (_date.minute == this->minute) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
