#ifndef YIENGINE_COMMON_I_DATE_TIME_H
#define YIENGINE_COMMON_I_DATE_TIME_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>

#include <YiEngine/DateTime/DataTranslator.hpp>
#include <YiEngine/DateTime/DateTimeCommonDef.h>
#include <YiEngine/DateTime/DayInfoDef.h>

namespace yiEngine
{
namespace dateTime
{
class IDateTime
{
public:
    virtual ~IDateTime() {}
public:
    virtual void TestFun() = 0;
    virtual Day GetDay(double year, double month, double day, 
            double hour, double minute, double second) = 0;

    virtual bool GetDayBaziInfo(BaziObject& obj, double year, double month, double day, 
            double hour, double minute, double second) = 0;
    virtual bool GetDayLunarInfo(LunarDayObject& obj, double year, double month, double day, 
            double hour, double minute, double second) = 0;
    virtual bool GetDayPublicInfo(PublicDayObject& obj, double year, double month, double day, 
            double hour, double minute, double second) = 0;
    virtual bool GetDayJieqiInfo(JieQiObject& obj, double year, double month, double day, 
            double hour, double minute, double second) = 0;
    virtual bool GetDayFestivalInfo(FestivalObject& obj, double year, double month, double day, 
            double hour, double minute, double second) = 0;

    virtual JulianDayInfo GetJulianDay(double year, double month, double day, 
        double hour, double minute, double second) = 0;
    virtual JulianDayInfo GetJulianDay(double julianDay) = 0;
};

typedef boost::shared_ptr<IDateTime> DateTimePtr;
}  // namespace DateTime
}  // namespace YiEngine
#endif
