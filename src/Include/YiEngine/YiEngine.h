#ifndef YIENGINE_COMMON_YI_ENGINE_H
#define YIENGINE_COMMON_YI_ENGINE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <YiEngine/DateTime/IDateTimeFactory.h>
#include <YiEngine/DateTime/IDateTime.h>
#include <YiEngine/SixYao/ISixYaoFactory.h>
#include <YiEngine/SixYao/ISixYao.h>

namespace yiEngine
{
namespace common
{
class YiEngine
{
public:
    YiEngine();
	dateTime::DateTimePtr GetDateTimeObject();
	sixYao::SixYaoPtr GetSixYaoObject();

private:
	dateTime::DateTimeFactoryPtr iDateTimeFactory;
	sixYao::SixYaoFactoryPtr iSixYaoFactory;
};

typedef boost::shared_ptr<YiEngine> YiEnginePtr;

}  // namespace Common
}  // namespace YiEngine
#endif
