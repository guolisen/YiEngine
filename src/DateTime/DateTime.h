#ifndef YIENGINE_COMMON_C_DATE_TIME_H
#define YIENGINE_COMMON_C_DATE_TIME_H

#include <cstdlib>
#include <stdio.h>
#include <time.h>  
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <boost/format.hpp>

#include <YiEngine/DateTime/IDateTime.h>
#include "MoonCalculate.h"
#include "JulianDay.h"
#include "LunarDay.h"
#include "PublicDay.h"
#include "DayFactory.h"
#include "TimeInfo.h"


namespace yiEngine
{
namespace dateTime
{
class DateTime : public IDateTime
{
public:
    virtual Day GetDay(double year, double month, double day, 
            double hour, double minute, double second);

    virtual JulianDayInfo GetJulianDay(double year, double month, double day, 
            double hour, double minute, double second);
    virtual JulianDayInfo GetJulianDay(double julianDay);

    virtual bool GetDayBaziInfo(BaziObject& obj, double year, double month, double day, 
            double hour, double minute, double second);
    virtual bool GetDayLunarInfo(LunarDayObject& obj, double year, double month, double day, 
            double hour, double minute, double second);
    virtual bool GetDayPublicInfo(PublicDayObject& obj, double year, double month, double day, 
            double hour, double minute, double second);
    virtual bool GetDayJieqiInfo(JieQiObject& obj, double year, double month, double day, 
            double hour, double minute, double second);
    virtual bool GetDayFestivalInfo(FestivalObject& obj, double year, double month, double day, 
            double hour, double minute, double second);

    virtual void TestFun()
    { 
        JulianDay jd;
        jd.SetFromJD(2444147.5);
        std::cout << "JD: " << jd.GetYear() << " " << jd.GetMonth() << " " << jd.GetDay() << " " 
            << jd.GetHour() << " " << jd.GetMinute() << " " << jd.GetSecond() << std::endl;  

        JulianDay jd2(1979, 10, 1, 0, 0, 0);
        double tm = jd2.GregorianDayToJulianDay();
        std::cout << "JD: " << jd2.GregorianDayToJulianDay() << std::endl;  

        MoonCalculate mc;
        JulianDay jd3(2014, 4, 5, 12, 0, 0);
        double jieqiJD = jd3.GregorianDayToJulianDay() - commonDef::J2000;
        mc.calcY(5173.0);

        commonDef::GANZHI gz;
        gz.gan = gan::JIA_VAL;
        gz.zhi = zhi::WU_VAL;

        std::cout << "Hello!!!! " << (std::string)gz << std::endl;   

        LunarDayBuilder lDay;
        LunarDayObject tmpLObj;

        lDay.Build(tmpLObj, 2014, 3, 30, 0, 0, 0);

        LunarJieqiDayBuilder jieQi;
        JieQiObject tmpJieQi;
        jieQi.Build(tmpJieQi, 2014, 4, 4, 0, 0, 0);

        FestivalDayBuilder festivalDay;
        FestivalObject fesObj;
        festivalDay.Build(fesObj, 2014, 1, 9, 0, 0, 0);

        BaZiBuilder bazi;
        BaziObject  baziObj;
        bazi.Build(baziObj, 2014, 3, 30, 16, 0, 21);

        PublicDayBuilder publicDay;
        PublicDayObject  publicObj;
        publicDay.Build(publicObj, 2014, 3, 30, 16, 0, 21);

        DayFactory factory;
        Day day = factory.GetDay(2014, 4, 5, 16, 0, 21);

        PublicDayObject publicObj2;
        factory.GetDayTypeData(publicObj2, 2014, 4, 5, 16, 0, 21);

        BaziObject bazi2;
        factory.GetDayTypeData(bazi2, 2014, 4, 6, 18, 47, 21);

        time_t rawtime = time(NULL);
        TimeCalculator tc;
        TimeInfo tmInfo = tc.Calculator(rawtime, commonDef::Angle2Rad(-116, 28, 0), commonDef::Angle2Rad(39, 55, 0), 0);
        JulianDay zty(tmInfo.zty + commonDef::J2000);
        JulianDay pty(tmInfo.pty + commonDef::J2000);

        std::cout << boost::format("PTY: %f:%f:%f ZTY: %f:%f:%f") % pty.GetHour() % pty.GetMinute() % pty.GetSecond() %
            zty.GetHour() % zty.GetMinute() % zty.GetSecond() << std::endl;
        std::cout << "Hello22!!!! " << (std::string)gz << std::endl;  
    }

protected:
    DayFactory dayFactory_;
};

}  // namespace dateTime
}  // namespace YiEngine
#endif
