#ifndef YIENGINE_COMMON_JULIANDAY_H
#define YIENGINE_COMMON_JULIANDAY_H

#include <iostream>
#include <vector>

#include <YiEngine/DateTime/IDateTime.h>

namespace yiEngine
{
namespace dateTime
{
class JulianDay
{
public:
    JulianDay(void);
    JulianDay(double jd);
    JulianDay(double year, double month, double day, 
               double hour, double minute, double second);
    JulianDay(DayInfo dayInfo): year_(dayInfo.GetYear()), month_(dayInfo.GetMonth()), day_(dayInfo.GetDay()), 
        hour_(dayInfo.GetHour()), minute_(dayInfo.GetMinute()), second_(dayInfo.GetSecond()) {}
    virtual ~JulianDay(void) {};

public:
    virtual DayInfo CreateDayInfo()
    {
        double jd = GregorianDayToJulianDay();
        return DayInfo(year_, month_, day_, 
            hour_, minute_, second_, jd);
    }
    virtual double GetYear() const
    {
        return year_;
    }
    virtual double GetMonth() const
    {
        return month_;
    }
    virtual double GetDay() const
    {
        return day_;
    }
    virtual double GetHour() const
    {
        return hour_;
    }
    virtual double GetMinute() const
    {
        return minute_;
    }
    virtual double GetSecond() const
    {
        return second_;
    }
    /// 公历转儒略日
    virtual double GregorianDayToJulianDay();
    /// 儒略日数转公历
    virtual void SetFromJD(double jd);
    static double J2000()
    {
        return 2451545;  
    };
public:
    /// 二次曲线外推
    virtual double deltatExt(double y, double jsd);
    /// 计算世界时与原子时之差,传入年
    virtual double deltatT(double y);
    /// 传入儒略日(J2000起算),计算TD-UT(单位:日)
    virtual double deltatT2(double t);
    /// 求y年m月的第n个星期w的儒略日数
    virtual double nnweek(double y, double m, double n, double w);
    /// 星期计算
    virtual double getWeek(double jd);
protected:
    /// 公历转儒略日
    virtual double GD_To_JD(double y, double m, double d);

private:
    double year_;
    double month_;
    double day_;
    double hour_;
    double minute_;
    double second_;
};

}  // namespace dateTime
}  // namespace YiEngine


#endif