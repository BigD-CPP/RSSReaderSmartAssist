#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <tinyxml2.h>

#include "utility/Logger.h"

using namespace std;
using namespace std::chrono;

///////////////////////////////////////////////////////////
#define CONFIG_XML_PATH "config/config.xml"


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

#endif
