#include "utility/Constant.h"

CConstant* mConstantIns;

CConstant::CConstant()
{
    mLoggerIns = new CLogger();

    load_params();
}

CConstant::~CConstant()
{
}

void CConstant::load_params()
{
    

}