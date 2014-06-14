#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <YiEngine/YiEngine.h>
#include "../DateTime/DateTimeFactory.h"
#include "../SixYao/SixYaoFactory.h"

namespace yiEngine
{
namespace common
{

YiEngine::YiEngine(): iDateTimeFactory(boost::make_shared<dateTime::DateTimeFactory>()), 
    iSixYaoFactory(boost::make_shared<sixYao::SixYaoFactory>()) 
{
}
dateTime::DateTimePtr YiEngine::GetDateTimeObject()
{
	return iDateTimeFactory->CreateObject();
}
sixYao::SixYaoPtr YiEngine::GetSixYaoObject()
{
    return iSixYaoFactory->CreateObject();
}

}  // namespace Common
}  // namespace YiEngine
