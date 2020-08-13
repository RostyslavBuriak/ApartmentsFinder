/*Class for parsing POLISH olx html webpages*/

#pragma once
#include <vector>
#include"webpage.h"
#include "date.h"
#include <map>

class olxparser
{
public:
	olxparser(date _nd) :olx("www.olx.pl"),enddate(_nd){};

	olxparser(const olxparser&) = delete;
	olxparser(olxparser&&) = delete;

	olxparser& operator=(const olxparser&) = delete;
	olxparser& operator=(olxparser&&) = delete;

	void SetDate(date);
	void start();
private:
	bool datefound = false; //indicates if choosen date stamp was found

	webpage olx;
	date enddate;

	struct ad {
		ad() :price(0), czynsz(0), id(0) {}

		unsigned price;
		unsigned czynsz;
		unsigned long id;

		std::string link;
		std::string name;

		date d;

		void clear() {
			price = 0;
			czynsz = 0;
			id = 0;
			link = "";
			name = "";
		}
	};

	std::map<std::string, unsigned> months{ 
		{"stycznia",1},{"lutego",2},{"marca",3},
		{"kwietnia",4},{"maja",5},{"czerwca",6},
		{"lipca",7},{"sierpnia",8},{u8"września",9},
		{u8"października",10},{"listopada",11},{"grudnia",12}};

	std::vector<std::string> adv_links;
	std::vector<ad> ads_olx;
	std::vector<ad> ads_oto;

	void GetAdvLinks();
	void GetAppsLinks();
	void SendNotifs();

	//unsigned GetMonth(const std::string&); //converts polish month name to number
};

