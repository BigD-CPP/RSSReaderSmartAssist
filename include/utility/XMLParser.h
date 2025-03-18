#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include "Constant.h"
#include <tinyxml2.h>

class CXMLParser
{
public:
	CXMLParser(string _file_path, string _root_name);
	CXMLParser(char* _doc_buffer, string _root_name);
	~CXMLParser();
	
	bool save(string _file_path);

	bool get_tag(string _tags, string& _output);

	bool get_muliple_tag(string _tags, vector<string>& _output);
	bool get_muliple_tag(string _tags, vector<CRSSItems>& _output);

	template<typename T>
	T set_tag(string filepath, string tag_stream);

	void print(vector<CRSSItems> _rssItemsVect);

private:
	bool load(bool is_fileParseEnable = true);
	bool get_same_tag(tinyxml2::XMLElement* base_element, string _tag, vector<string>& _output);
	bool get_same_tag(tinyxml2::XMLElement* base_element, string _tag, vector<CRSSItems>& _output);



	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;

	string file_path, root_name;
	unique_ptr<char[]> doc_buffer;

};

#endif
