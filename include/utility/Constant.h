#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

#include "utility/Logger.h"

using namespace std;
using namespace std::chrono;

///////////////////////////////////////////////////////////
#define CONFIG_XML_PATH "config/config.xml"
#define ROOT_ELEMENT_DEFAULT "rss"

///////////////////////////////////////////////////////////

class CConstant
{
private:
	void load_params();

public:
	vector<string> mRSSURLVector;
	
	CConstant();
	~CConstant();
};

extern CConstant * mConstantIns;

///////////////////////////////////////////////////////////

enum RSSItemsEnum
{
	RSS_Title = 0,
	RSS_Link,
	RSS_Description,
	RSS_Category,
	RSS_PubDate,

	RSSItemsEnum_count //count
};

class CRSSItems
{
public:
	vector<vector<string>> rss_data;
	string RSSItemsEnum_str[RSSItemsEnum_count];

	CRSSItems()
	{
		set();

		//TODO: optimize later
		RSSItemsEnum_str[RSS_Title] = "title";
		RSSItemsEnum_str[RSS_Link] = "link";
		RSSItemsEnum_str[RSS_Description] = "description";
		RSSItemsEnum_str[RSS_Category] = "category";
		RSSItemsEnum_str[RSS_PubDate] = "pubDate";
	};

	~CRSSItems()
	{
		reset();
	};

private:
	void set()
	{
		rss_data.clear();
		rss_data.resize(RSSItemsEnum_count);
	}
	void reset()
	{
		rss_data.clear();
		RSSItemsEnum_str->clear();
	}
};

#endif
