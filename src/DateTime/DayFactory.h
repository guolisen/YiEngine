#ifndef YIENGINE_COMMON_DAY_FACTORY_H
#define YIENGINE_COMMON_DAY_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>

#include <YiEngine/DateTime/IDateTime.h>
#include "IDayBuilder.h"
#include "LunarDay.h"
#include "PublicDay.h"

namespace yiEngine
{
namespace dateTime
{
class DayFactory
{
public:
    Day GetDay(double year, double month, double day,
        double hour, double minute, double second);

    template<typename T>
    bool GetDayTypeData(T& obj, double year, double month, double day,
        double hour, double minute, double second)
    {
        boost::shared_ptr<IDayBuilder<T> > builderPtr;
        getDayBuilder(builderPtr);
        BOOST_ASSERT(builderPtr);
        return builderPtr->Build(obj, year, month, day,
            hour, minute, second);
    }

protected:
    template<typename T>
    bool getDayBuilder(boost::shared_ptr<IDayBuilder<T> >& obj)
    {
        return GetBuilder<T>(obj);
    }
};

}  // namespace dateTime
}  // namespace YiEngine
#endif
