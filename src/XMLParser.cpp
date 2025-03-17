#include "utility/XMLParser.h"

CXMLParser::CXMLParser(string _file_path, string _root_name)
{
	file_path = _file_path;
	root_name = _root_name;

	if (!load(true))
		throw("xxxx CXMLParser::CXMLParser | Load xml Faild! xxxx");
	
}

CXMLParser::CXMLParser(char* _doc_buffer, string _root_name)
{
	size_t length = strlen(_doc_buffer) + 1; 
	doc_buffer = std::make_unique<char[]>(length);
	std::copy(_doc_buffer, _doc_buffer + length, doc_buffer.get());
	root_name = _root_name;

	file_path = "";

	if (!load(false))
		throw("xxxx CXMLParser::CXMLParser | Load xml Faild! xxxx");

}

CXMLParser::~CXMLParser()
{
}

bool CXMLParser::load(bool is_fileParseEnable)
{
	if (is_fileParseEnable)
	{
		tinyxml2::XMLError error = doc.LoadFile(file_path.c_str());
		if (error != tinyxml2::XML_SUCCESS)
		{
			mLoggerIns->elog("CXMLParser::CXMLParser", doc.ErrorStr());
			throw((string)"CXMLParser::CXMLParser" + doc.ErrorStr());
			return false;
		}
	}
	else
	{
		tinyxml2::XMLError error = doc.Parse(doc_buffer.get());
		if (error != tinyxml2::XML_SUCCESS)
		{
			mLoggerIns->elog("CXMLParser::CXMLParser", doc.ErrorStr());
			throw((string)"CXMLParser::CXMLParser" + doc.ErrorStr());
			return false;
		}
	}

	/////////////////////////////////////////////
	//TODO: later 
	/*error = doc.SaveFile("result.xml");
	if (error != tinyxml2::XML_SUCCESS)
	{
		cerr << "Error saving XML: " << doc.ErrorStr() << endl;
		exit(EXIT_FAILURE);
	}*/

	/////////////////////////////////////////////

	root = doc.FirstChildElement(root_name.c_str());
	if (!root)
	{
		mLoggerIns->wlog("CXMLParser::CXMLParser", root_name + " rss xml not valid.");
		throw((string)"CXMLParser::CXMLParser" + root_name + " rss xml not valid.");
		return false;
	}

	return true;
}

//TODO: merge with get_muliple_tag later 
//tag stream seperate by '.'
bool CXMLParser::get_tag(string _tags, string& _output)
{
	tinyxml2::XMLElement* element = nullptr, *result = nullptr;
	int offset = 0;
	string tag, tag_stream = _tags;
	bool no_tag_remain = false;

	element = root;
	while (!no_tag_remain)
	{
		auto loc = tag_stream.find('.', offset);
		if (loc != string::npos)
		{
			tag = tag_stream.substr(offset, loc - offset);
		}
		else
		{
			tag = tag_stream.substr(offset);
			no_tag_remain = true;
		}

		offset = loc + 1;

		result = element->FirstChildElement(tag.c_str());
		element = result;
		result = nullptr;
	}

	_output = element->GetText();

	return true;
}

bool CXMLParser::get_muliple_tag(string _tags, vector<string>& _output)
{
	tinyxml2::XMLElement* element = nullptr, * result = nullptr;
	int offset = 0;
	string tag, tag_stream = _tags;

	element = root;
	while (1)
	{
		auto loc = tag_stream.find('.', offset);
		if (loc != string::npos)
		{
			tag = tag_stream.substr(offset, loc - offset);
		}
		else
		{
			tag = tag_stream.substr(offset);
			get_same_tag(element, tag, _output);
			break;
		}

		offset = loc + 1;

		result = element->FirstChildElement(tag.c_str());
		element = result;
		result = nullptr;
	}

	return true;
}

bool CXMLParser::get_muliple_tag(string _tags, vector<CRSSItems>& _output)
{
	tinyxml2::XMLElement* element = nullptr, * result = nullptr;
	int offset = 0;
	string tag, tag_stream = _tags;
	bool no_tag_remain = false;

	element = root;
	while (!no_tag_remain)
	{
		result = nullptr;
		auto loc = tag_stream.find('.', offset);
		if (loc != string::npos)
		{
			tag = tag_stream.substr(offset, loc - offset);
		}
		else
		{
			tag = tag_stream.substr(offset);
			no_tag_remain = true;
		}

		offset = loc + 1;

		result = element->FirstChildElement(tag.c_str());
		if (!result)
			return false;

		element = result;
	}

	_output.clear();

	get_same_tag(element, tag, _output);

	return true;
}

bool CXMLParser::get_same_tag(tinyxml2::XMLElement* base_element,string _tag, vector<string> _output)
{
	tinyxml2::XMLElement* th_sub_element = nullptr;

	do
	{
		th_sub_element = base_element->FirstChildElement(_tag.c_str());
		if (th_sub_element)
		{
			_output.push_back(th_sub_element->GetText());
		}
		else
			break;

		tinyxml2::XMLElement* next_element = base_element->NextSiblingElement(_tag.c_str());
		base_element = next_element;

	} while (base_element);

	return true;
}

bool CXMLParser::get_same_tag(tinyxml2::XMLElement* base_element, string _tag, vector<CRSSItems> _output)
{
	tinyxml2::XMLElement* th_sub_element = nullptr, * copy_element = nullptr;

	do
	{
		CRSSItems th_rss_data;
		copy_element = base_element;
		for (int i = 0; i < RSSItemsEnum_count; i++)
		{
			th_sub_element = copy_element->FirstChildElement(th_rss_data.RSSItemsEnum_str[i].c_str());
			if (!th_sub_element)
				continue;

			do
			{
				th_rss_data.rss_data[i].push_back(th_sub_element->GetText());

				tinyxml2::XMLElement* next_sub_element = th_sub_element->NextSiblingElement(th_rss_data.RSSItemsEnum_str[i].c_str());
				th_sub_element = next_sub_element;

			} while (th_sub_element);
		}

		_output.push_back(th_rss_data);

		tinyxml2::XMLElement* next_element = base_element->NextSiblingElement(_tag.c_str());
		base_element = next_element;

	} while (base_element);

	return true;
}


template<typename T>
T CXMLParser::set_tag(string filepath, string tag_stream)
{
	return T();
}

void CXMLParser::print(vector<CRSSItems> _rssItemsVect)
{
	for (int i = 0; i < _rssItemsVect.size(); i++)
	{
		cout << "item " << i << ":" << endl;
		for (int j = 0; j < RSSItemsEnum_count; j++)
		{
			for (int k = 0; k < _rssItemsVect[i].rss_data[j].size(); k++)
			{
				cout << "\t" << _rssItemsVect[i].RSSItemsEnum_str[j] << " : " << _rssItemsVect[i].rss_data[j][k] << endl;
			}
		}
	}
}