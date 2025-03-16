#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <tinyxml2.h>

using namespace std;

class CXMLParser
{
public:
	CXMLParser();
	~CXMLParser();

	template<typename T>
	T get_tag(string filepath, string tag_stream);

	template<typename T>
	T set_tag(string filepath, string tag_stream);

private:

};

extern CXMLParser* mXMLParserIns;
#endif
