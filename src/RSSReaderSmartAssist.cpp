#include <iostream>
#include <Windows.h>
#include <curl/curl.h>
#include "RSSReaderSmartAssistConfig"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		// report version
		cout << argv[0] << " Version " << RSSReaderSmartAssist_VERSION_MAJOR
			<< "." << RSSReaderSmartAssist_VERSION_MINOR << endl;
	}

	CURL* curl;
	curl = curl_easy_init();
	if (curl == nullptr)
	{
		cout << "error in curl_easy_init" << endl;
		Sleep(3000);
		exit(EXIT_FAILURE);
	}


	cout << "Hello CMake." << endl;
	return 0;
}
