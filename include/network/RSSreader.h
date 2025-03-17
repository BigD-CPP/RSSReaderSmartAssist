#ifndef _RSS_READER_H_
#define _RSS_READER_H_

#include "utility/Constant.h"
#include "utility/XMLParser.h"
#include <curl/curl.h>

class CRSSreader
{
private:
	CURL* curl;
	vector<string> urlVect;

	void load_urls();

public:
	CRSSreader();
	~CRSSreader();

};
#endif