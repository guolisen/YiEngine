#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "DateTime.h"

namespace yiEngine
{
namespace dateTime
{
Day DateTime::GetDay(double year, double month, double day, 
                     double hour, double minute, double second)
{
    return dayFactory_.GetDay(year, month, day, hour, minute, second);
}

JulianDayInfo DateTime::GetJulianDay(double year, double month, double day, 
                                     double hour, double minute, double second)
{
    JulianDay jd(year, month, day, hour, minute, second);
    return jd.CreateDayInfo();
}

JulianDayInfo DateTime::GetJulianDay(double julianDay)
{
    JulianDay jd(julianDay);
    return jd.CreateDayInfo();
}

bool DateTime::GetDayBaziInfo(BaziObject& obj, double year, double month, double day, 
        double hour, double minute, double second)
{
    return dayFactory_.GetDayTypeData(obj, year, month, day, hour, minute, second);
}

bool DateTime::GetDayLunarInfo(LunarDayObject& obj, double year, double month, double day, 
        double hour, double minute, double second)
{
    return dayFactory_.GetDayTypeData(obj, year, month, day, hour, minute, second);
}
bool DateTime::GetDayPublicInfo(PublicDayObject& obj, double year, double month, double day, 
        double hour, double minute, double second)
{
    return dayFactory_.GetDayTypeData(obj, year, month, day, hour, minute, second);
}
bool DateTime::GetDayJieqiInfo(JieQiObject& obj, double year, double month, double day, 
        double hour, double minute, double second)
{
    return dayFactory_.GetDayTypeData(obj, year, month, day, hour, minute, second);
}
bool DateTime::GetDayFestivalInfo(FestivalObject& obj, double year, double month, double day, 
        double hour, double minute, double second)
{
    return dayFactory_.GetDayTypeData(obj, year, month, day, hour, minute, second);
}

}  // namespace Common
}  // namespace YiEngine
