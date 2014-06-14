#ifndef YIENGINE_COMMON_PUBLICDAY_H
#define YIENGINE_COMMON_PUBLICDAY_H

#include <YiEngine/DateTime/IDateTime.h>
#include "JulianDay.h"
#include "IDayBuilder.h"
#include "MoonCalculate.h"
#include "StarCalendar.h"

namespace yiEngine
{
namespace dateTime
{

class PublicDay
{
public:
    PublicDay(double year, double month, double day, 
            double hour, double minute, double second): 
            julianDay_(year, month, day, hour, minute, second) {}
    PublicDay(double jd): julianDay_(jd) {}

    bool PublicDayCalculate(PublicDayObject& obj);
protected:
    JulianDay julianDay_;
    MoonCalculate moonCalculate_;
    StarCalendar  starCalendar_;
};

class PublicDayBuilder: public IDayBuilder<PublicDayObject>
{
public:
    virtual bool Build(PublicDayObject& obj, double year, double month, double day,
        double hour, double minute, double second);
};

}  // namespace dateTime
}  // namespace YiEngine

#endif