#include "DayFactory.h"

namespace yiEngine
{
namespace dateTime
{

Day DayFactory::GetDay(double year, double month, double day,
        double hour, double minute, double second)
{
    Day dayObj;

    GetDayTypeData(dayObj.lunarDay, year, month, day, hour, minute, second);
    GetDayTypeData(dayObj.jieqiObj, year, month, day, hour, minute, second);
    GetDayTypeData(dayObj.festivalDay, year, month, day, hour, minute, second);
    GetDayTypeData(dayObj.bazi, year, month, day, hour, minute, second);
    GetDayTypeData(dayObj.publicDay, year, month, day, hour, minute, second);

    return dayObj;
}

}  // namespace dateTime
}  // namespace YiEngine