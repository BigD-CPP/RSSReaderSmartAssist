#include "utility/XMLParser.h"

CXMLParser* mXMLParserIns;

CXMLParser::CXMLParser()
{
}

CXMLParser::~CXMLParser()
{
}

template<typename T>
T CXMLParser::get_tag(string filepath, string tag_stream)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error;

    error = doc.LoadFile(CONFIG_XML_PATH);
    if (error != tinyxml2::XML_SUCCESS)
    {
        mLoggerIns->elog("CConstant::load_params", doc.ErrorStr());
        exit(EXIT_FAILURE);
    }

    doc.Clear();
	return T();
}

template<typename T>
T CXMLParser::set_tag(string filepath, string tag_stream)
{
	return T();
}