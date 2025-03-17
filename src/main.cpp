#include "utility/Constant.h"
#include <format>

#include "utility/XMLParser.h"

using namespace std;



int main(int argc, char* argv[])
{
    mConstantIns = new CConstant();

    CXMLParser mXMLParserIns("result.xml", "rss");
    vector<CRSSItems> result;

    mXMLParserIns.get_muliple_tag("channel.item", result);
    mXMLParserIns.print(result);

    //////////////////////////////////////////////////

    return 0;
}
