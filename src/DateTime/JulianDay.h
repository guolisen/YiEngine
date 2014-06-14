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
    /// ����ת������
    virtual double GregorianDayToJulianDay();
    /// ��������ת����
    virtual void SetFromJD(double jd);
    static double J2000()
    {
        return 2451545;  
    };
public:
    /// ������������
    virtual double deltatExt(double y, double jsd);
    /// ��������ʱ��ԭ��ʱ֮��,������
    virtual double deltatT(double y);
    /// ����������(J2000����),����TD-UT(��λ:��)
    virtual double deltatT2(double t);
    /// ��y��m�µĵ�n������w����������
    virtual double nnweek(double y, double m, double n, double w);
    /// ���ڼ���
    virtual double getWeek(double jd);
protected:
    /// ����ת������
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