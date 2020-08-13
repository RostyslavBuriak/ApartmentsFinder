#include "olxparser.h"
#include <sstream>

void olxparser::GetAdvLinks() {
	std::string location(u8"/nieruchomosci/mieszkania/wynajem/warszawa/q-mieszkanie-2-pokoje-ochota/?search%5Bfilter_float_price%3Ato%5D=2200&search%5Bdescription%5D=1");
	unsigned page = 0; //what page we gonna parse
	while (!datefound) {
		olx.SendRequest(
			location
			+ "&page=" + std::to_string(page++)
		);
		std::istringstream html(olx.GetResponse()); //html code of page with ads
		std::string sentence;
		while (html >> sentence) {
			if (sentence == "class=\"hasPromoted") {
				while (html >> sentence) {
					if (sentence == "class=\"offer") {
						html >> sentence;
						if (sentence == "promoted" || "\">") {
							while (html >> sentence) {
								if (sentence.find("href") != std::string::npos) {
									adv_links.push_back(
										std::move(
											sentence.substr(
												sentence.find("pl") + 2,
												sentence.length() - (sentence.find("pl") + 3)
											)
										)
									);
									break;
								}
							}
						}
					}
				}
			}
		}
		GetAppsLinks();
		adv_links.clear();
	}
}


void olxparser::GetAppsLinks() {
	for (auto x : adv_links) {
		olx.SendRequest(x);
		std::istringstream html(olx.GetResponse()); //html code of page with ads
		std::string sentence;
		ad adv;
		while (html >> sentence) {
				if (sentence == "property=\"og:title\"") {
					html >> sentence;
					adv.name = sentence.substr(
						sentence.find_first_of("\"") + 1);
					while (html >> sentence && sentence.find("/>") == std::string::npos) {
						adv.name += " " + sentence;
					}
					adv.name += " " + sentence.substr(
						0,
						sentence.find_last_of("\"")
					);
					continue;
					}
				if (sentence.find("ad_id\":\"") != std::string::npos) {
					adv.id =
						std::stoi(
							sentence.substr(
								sentence.find("ad_id\":\"") + 8,
								sentence.find("\",\"ad_photo\"") - (sentence.find("ad_id\":\"") + 8)
							));
				}
				if (sentence.find("ad_price\":\"") != std::string::npos) {
					adv.price =
						std::stoi(
							sentence.substr(									
								sentence.find("ad_price\":\"") + 11,
								sentence.find("\",\"price_currency\"") - (sentence.find("ad_price\":\"") + 11)
							));
					continue;
				}
				if (sentence == "class=\"offer-details__name\">Czynsz") {
					while (html >> sentence) {
						if (sentence.find("class=\"offer-details__value\">") != std::string::npos) {
							adv.czynsz = std::stoi(									
								sentence.substr(
									sentence.find(">") + 1
								)
							);
							break;
						}
					}
					continue;
				}
				if (sentence == "Dodane") { //get the date, example : <em><strong>o 10:09, 10 sierpnia 2020</strong></em>
					html >> sentence >> sentence; //skip one sentence;
						adv.d.hour = std::stoi(
							sentence.substr(
								0, 2
							)
						);
						adv.d.minute = std::stoi(
							sentence.substr(
								3, 2
							)
						);
						html >> sentence;
						adv.d.day = std::stoi(sentence);
						html >> sentence;
						adv.d.month = months[sentence];
						html >> sentence;
						adv.d.year = std::stoi(
							sentence.substr(0, 4)
						);
						if (adv.d < enddate) {
							datefound = true;
							SendNotifs();
							return;
						}
						break;
					}
				}
		if ((adv.price + adv.czynsz) <= 2205) {
			if (!ads_olx.empty() && ads_olx[ads_olx.size() - 1].id == adv.id) {
				datefound = true;
				return;
			}
			if (x[x.length() - 1] != '?') {
				x = "olx.pl" + x;
				adv.link = std::move(x);
				ads_olx.push_back(std::move(adv));
			}
			else
			{
				x = "otodom.pl" + x;
				adv.link = std::move(x);
				ads_oto.push_back(std::move(adv));
			}
		}
	}
}


/*unsigned olxparser::GetMonth(const std::string& month) {
	if (month == "stycznia")
		return 1;
	if (month == "lutego")
		return 2;
	if (month == "marca")
		return 3;
	if (month == "kwietnia")
		return 4;
	if (month == "maja")
		return 5;
	if (month == "czerwca")
		return 6;
	if (month == "lipca")
		return 7;
	if (month == "sierpnia")
		return 8;
	if (month == u8"września")
		return 9;
	if (month == u8"października")
		return 10;
	if (month == "listopada")
		return 11;
	if (month == "grudnia")
		return 12;

	return 0;
}*/


void olxparser::SendNotifs() {
	std::string command;
	
	for (static unsigned id = 0; id < ads_olx.size();++id) {
		command =
			"py .\\appbot.py " +
			std::to_string(ads_olx[id].czynsz + ads_olx[id].price) +
			" " +
			ads_olx[id].link;

		system(command.c_str()); //run .py script
	}
}


void olxparser::SetDate(date _d) {
	enddate = _d;
}


void olxparser::start() {
	datefound = false;
	GetAdvLinks();
}