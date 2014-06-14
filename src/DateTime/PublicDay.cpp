#include "PublicDay.h"



namespace yiEngine
{
namespace dateTime
{

bool PublicDay::PublicDayCalculate(PublicDayObject& obj)
{
    double m0 = 0;
    double mn = 0;
    double tmpYear  = julianDay_.GetYear();
    double tmpMonth = julianDay_.GetMonth();

    // 日历物件初始化
    JulianDay jd(tmpYear, tmpMonth, 1, 12.0, 0.0, 0.0);
    m0 = floor(jd.GregorianDayToJulianDay()) - commonDef::J2000;  // 公历某年的月首,中午

    if(moonCalculate_.ZQ.lunarInfoList_.empty() || m0 < moonCalculate_.ZQ.lunarInfoList_[0] || m0 >= moonCalculate_.ZQ.lunarInfoList_[24])
        moonCalculate_.calcY(m0);

    double nextMonth = tmpMonth + 1;
    if (nextMonth > 12) 
    { 
        tmpYear++; 
        tmpMonth = 1; 
    }     // C#: 如果月份大于 12, 则年数 + 1, 月数取 1

    JulianDay jdNext(tmpYear, nextMonth, 1, 12.0, 0.0, 0.0);

    mn = jdNext.GregorianDayToJulianDay() - commonDef::J2000 - m0; // 本月天数(公历)

    double w0 = fmod((m0 + commonDef::J2000 + 1), 7); //本月第一天的星期

    obj.d0 = julianDay_.GregorianDayToJulianDay() - commonDef::J2000;   // 儒略日,北京时12:00
    obj.di = julianDay_.GetDay();         // 公历月内日序数
    obj.y = (int)julianDay_.GetYear();         // 公历年
    obj.m = (int)julianDay_.GetMonth();         // 公历月
    obj.dn = mn;       // 公历月天数
    obj.week0 = w0;     // 月首的星期
    obj.week = fmod((w0 + obj.di), 7);     // 当前日的星期
    obj.weeki = floor((w0 + obj.di) / 7);    // 本日所在的周序号
    obj.weekN = floor((w0 + mn - 1) / 7) + 1;    // 本月的总周数
    obj.d = (int)julianDay_.GetDay();   //公历日名称

    double mk = (int)floor((obj.d0 - moonCalculate_.ZQ.lunarInfoList_[0] - 15) / 30.43685); 
    if (mk < 11 && obj.d0 >= moonCalculate_.ZQ.lunarInfoList_[2 * (unsigned int)mk + 2]) 
        mk++; //星座所在月的序数,(如果j=13,ob.d0不会超过第14号中气)
    obj.XiZ = commonDef::Constellation_Tab[(int)fmod((mk + 12), 12)];

    return true;
}

bool PublicDayBuilder::Build(PublicDayObject& obj, double year, double month, double day,
                            double hour, double minute, double second)
{
    PublicDay publicDay(year, month, day, hour, minute, second);
    publicDay.PublicDayCalculate(obj);
    return true;
}

template<>
bool GetBuilder<PublicDayObject>(boost::shared_ptr<IDayBuilder<PublicDayObject> >& obj)
{
    obj = boost::make_shared<PublicDayBuilder>();
    return true;
}

}  // namespace dateTime
}  // namespace YiEngine
