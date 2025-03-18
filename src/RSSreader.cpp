#include "network/RSSreader.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* buffer);

CRSSreader::CRSSreader()
{
    load_urls();
    get_rss_data();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CRSSreader::~CRSSreader()
{
    curl_global_cleanup();
}

void CRSSreader::load_urls()
{
    CXMLParser mXMLParserIns("config/urls.xml", "list");
    mXMLParserIns.get_muliple_tag("url", urlVect);
    if (urlVect.size() <= 0)
    {
        mLoggerIns->elog("CRSSreader::load_urls", "no url found in url.xml");
    }
}

/////////////////////////////////////////////////////////////////////////////////////

void CRSSreader::get_rss_data()
{
    mRSSDataContainerVector.clear();
    for (string url : urlVect)
    {
        try
        {
            vector<CRSSItems> th_mRSSItemsVector;

            ////////////////////////////////////
            //TODO: change this later
            int th_offset = 0;
            auto loc_www = url.find(":/", th_offset);
            loc_www += 3;
            th_offset = loc_www + 1;
            auto loc_com = url.find("/", th_offset);
            auto th_site_name = url.substr(loc_www, loc_com - loc_www);
            ////////////////////////////////////

            string th_rss_buffer;
            if (!get_rss(url, th_rss_buffer))
                continue;

            mRSSDataContainerVector.push_back(CRSSDataContainer(th_site_name));

            CXMLParser mXMLParserIns((char*)th_rss_buffer.c_str(), "rss");
            if (!mXMLParserIns.get_muliple_tag("channel.item", mRSSDataContainerVector[mRSSDataContainerVector.size() - 1].mRSSItemsVector))
            {
                mLoggerIns->elog("mXMLParserIns.get_muliple_tag", "rss error.");
            }
           
            if (!mXMLParserIns.save("rss/" + th_site_name + ".xml"))
            {
                mLoggerIns->wlog("CXMLParser.save", (string)"cant save " + "rss/" + th_site_name + ".xml");
            }
           
            mLoggerIns->ilog("CRSSreader::get_rss_data", url + " loaded " + to_string(mRSSDataContainerVector[mRSSDataContainerVector.size() - 1].mRSSItemsVector.size()) + " items");
        }
        catch (const std::exception& e)
        {
            mLoggerIns->wlog("CRSSreader::get_rss_data", url + " not loaded.");
        }
    }
}

bool CRSSreader::get_rss(string _url, string& _rss)
{
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (!curl)
    {
        mLoggerIns->wlog("CRSSreader::get_rss", "can't init curl.");
        _rss = "";
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_rss);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        mLoggerIns->wlog("CRSSreader::get_rss", "cant get data from site.");
        _rss = "";
        return false;
    }

    curl_easy_cleanup(curl);

    return true;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* buffer)
{
    size_t totalSize = size * nmemb;
    buffer->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
