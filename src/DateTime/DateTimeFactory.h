#ifndef YIENGINE_COMMON_C_DATE_TIME_FACTORY_H
#define YIENGINE_COMMON_C_DATE_TIME_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <YiEngine/DateTime/IDateTimeFactory.h>
#include "DateTime.h"

namespace yiEngine
{
namespace dateTime
{
class DateTimeFactory : public IDateTimeFactory
{
public:
    virtual ~DateTimeFactory() {}

public:
    virtual DateTimePtr CreateObject()
    {
        return boost::make_shared<DateTime>();
    }
};

}  // namespace Common
}  // namespace YiEngine
#endif
