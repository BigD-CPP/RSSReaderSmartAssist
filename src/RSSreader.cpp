#include "network/RSSreader.h"

CRSSreader::CRSSreader()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CRSSreader::~CRSSreader()
{
    curl_global_cleanup();
}

void CRSSreader::load_urls()
{
    CXMLParser mXMLParserIns("config/urls.xml", "rss");
    //mXMLParserIns.get_muliple_tag("config/urls.xml", "" , "url", R);
}

/////////////////////////////////////////////////////////////////////////////////////

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* buffer)
{
    size_t totalSize = size * nmemb;
    buffer->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void m()
{
    CURL* curl;
    CURLcode res = CURLE_OK;
    string url = "https://www.tasnimnews.com/fa/rss/feed/0/7/0/all-stories";
    string buffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            exit(EXIT_FAILURE);
        }

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError error = doc.Parse(buffer.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            cerr << "Error parsing XML: " << doc.ErrorStr() << endl;
            exit(EXIT_FAILURE);
        }

        error = doc.SaveFile("result.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            cerr << "Error saving XML: " << doc.ErrorStr() << endl;
            exit(EXIT_FAILURE);
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("rss");

        if (root)
        {
            tinyxml2::XMLElement* message = root->FirstChildElement("channel");
            if (message)
            {
                tinyxml2::XMLElement* title = message->FirstChildElement("link");
                if (title)
                    cout << "title: " << title->GetText() << endl;
                else {
                    cerr << "No title element found!" << endl;
                }
            }
            else {
                cerr << "No channel element found!" << endl;
            }
        }
        else
        {
            cerr << "No root element found!" << endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}