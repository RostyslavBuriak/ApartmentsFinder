#pragma once
#include <vector>
#include"webpage.h"

class olxparser
{
public:
	olxparser() :olx("www.olx.pl") {};

	olxparser(const olxparser&) = delete;
	olxparser(olxparser&&) = delete;

	olxparser& operator=(const olxparser&) = delete;
	olxparser& operator=(olxparser&&) = delete;

	void start();
private:
	webpage olx;
	std::vector<std::string> adv_links;
	std::vector<std::string> apps_links;

	void GetAdvLinks();
	void GetAppsLinks();
};

