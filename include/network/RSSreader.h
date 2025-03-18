#ifndef _RSS_READER_H_
#define _RSS_READER_H_

#include "utility/Constant.h"
#include "utility/XMLParser.h"
#include <curl/curl.h>

class CRSSDataContainer
{
public:
	string site_name;
	vector<CRSSItems> mRSSItemsVector;

	CRSSDataContainer(string _site_name)
	{
		reset();
		site_name = _site_name;
	};

	~CRSSDataContainer()
	{
		reset();
	};

private:
	void reset()
	{
		mRSSItemsVector.clear();
		site_name = "";
	}
};

class CRSSreader
{
private:
	CURL* curl;
	vector<string> urlVect;
	vector<CRSSDataContainer> mRSSDataContainerVector;
	void load_urls();
	void get_rss_data();
	bool get_rss(string _url, string& _rss);

public:
	CRSSreader();
	~CRSSreader();

};
#endif