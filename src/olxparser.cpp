#include "olxparser.h"
#include <sstream>

void olxparser::GetAdvLinks() {
	olx.SendRequest("/nieruchomosci/mieszkania/wynajem/warszawa/q-2-pokoje/?search%5Bfilter_float_price%3Ato%5D=2000");
	std::istringstream html(olx.GetResponse()); //html code of page with ads
	std::string sentence;
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


void olxparser::GetAppsLinks() {
	for (auto x : adv_links) {
		olx.SendRequest(x);
		std::istringstream html(olx.GetResponse()); //html code of page with ads
		std::string sentence;
		unsigned price = 0;
		unsigned czynsz = 0;
		while (html >> sentence) {
			if (sentence.find("ad_price\":\"") != std::string::npos) {
				std::string str = sentence.substr(
					sentence.find("ad_price\":\"") + 11,
					sentence.find("\",\"price_currency\"") - (sentence.find("ad_price\":\"") + 11)
				);
				price =
					std::stoi(
						sentence.substr(
							sentence.find("ad_price\":\"") + 11,
							sentence.find("\",\"price_currency\"") - (sentence.find("ad_price\":\"") + 11)
						));
			}
			else if (sentence == "class=\"offer-details__name\">Czynsz"){
				while (html >> sentence) {
					if (sentence.find("class=\"offer-details__value\">") != std::string::npos) {
						czynsz = std::stoi(
							sentence.substr(
								sentence.find(">") + 1
							)
						);
						break;
					}
				}
				break;
			}
		}
		if ((price + czynsz) <= 2000) {
			apps_links.push_back(x);
			price = 0;
			czynsz = 0;
		}
	}
}


void olxparser::start() {
	GetAdvLinks();
	GetAppsLinks();
}