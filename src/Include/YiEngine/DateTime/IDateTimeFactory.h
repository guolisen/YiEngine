#ifndef YIENGINE_COMMON_I_DATE_TIME_FACTORY_H
#define YIENGINE_COMMON_I_DATE_TIME_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <YiEngine/DateTime/IDateTime.h>

namespace yiEngine
{
namespace dateTime
{
class IDateTimeFactory
{
public:
    virtual ~IDateTimeFactory() {}
public:
    virtual DateTimePtr CreateObject() = 0;
};

typedef boost::shared_ptr<IDateTimeFactory> DateTimeFactoryPtr;

}  // namespace DateTime
}  // namespace YiEngine
#endif
