#ifndef YIENGINE_COMMON_LUNARDAY_H
#define YIENGINE_COMMON_LUNARDAY_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <YiEngine/DateTime/IDateTime.h>
#include "JulianDay.h"
#include "IDayBuilder.h"
#include "MoonCalculate.h"
#include "StarCalendar.h"

namespace yiEngine
{
namespace dateTime
{

/// <summary>
/// 八字类型(空间)
/// </summary>
enum BaZiTypeS
{
    /// <summary>
    /// 常规(北半球八字)
    /// </summary>
    Normal,

    /// <summary>
    /// 南半球八字: 天冲地冲(月天干地支均与北半球的取法相冲)
    /// </summary>
    TianChongDiChong,

    /// <summary>
    /// 南半球八字: 天克地冲(月地支与北半球的取法相冲, 按五虎遁月法排月天干)
    /// </summary>
    TianKeDiChong,

    /// <summary>
    /// 南半球八字: 天同地冲(月地支与北半球的取法相冲, 月天干与北半球的取法相同)
    /// </summary>
    TianTongDiChong
};

enum CalcJieQiType
{
    /// 仅计算节
    CalcJie,

    /// 仅计算气
    CalcQi, 

    /// 计算节和气
    CalcBoth
};

class LunarDay
{
public:
    LunarDay(double year, double month, double day, 
            double hour, double minute, double second): 
            julianDay_(year, month, day, hour, minute, second)
    {
        CalcJieQiTab();        
    }
    LunarDay(double jd): julianDay_(jd)
    {
        CalcJieQiTab();
    }

    bool DayCalculate(LunarDayObject& obj);
    bool CalcJieQiInfo(JieQiObject& obj);
    bool FestivalInfo(FestivalObject& obj, const LunarDayObject& lunarDay);
    bool BaZi(double J, double curTZ, BaziObject& obj, BaZiTypeS baziTypeS);
    bool BaZiNormal(double J, double curTZ, BaziObject& obj, BaZiTypeS baziTypeS);

    double qi_accurate(double W);
    double so_accurate(double W);
    double qi_accurate2(double jd);
    double so_accurate2(double jd);

protected:
    void CalcJieQiTab();
protected:
    std::vector<JieQiInfo> jieqiTab_;
    JulianDay julianDay_;
    MoonCalculate moonCalculate_;
    StarCalendar  starCalendar_;
};

class LunarDayBuilder: public IDayBuilder<LunarDayObject>
{
public:
    virtual bool Build(LunarDayObject& obj, double year, double month, double day,
        double hour, double minute, double second);
};

class LunarJieqiDayBuilder: public IDayBuilder<JieQiObject>
{
public:
    virtual bool Build(JieQiObject& obj, double year, double month, double day,
        double hour, double minute, double second);
};

class FestivalDayBuilder: public IDayBuilder<FestivalObject>
{
public:
    virtual bool Build(FestivalObject& obj, double year, double month, double day,
        double hour, double minute, double second);
};

class BaZiBuilder: public IDayBuilder<BaziObject>
{
public:
    virtual bool Build(BaziObject& obj, double year, double month, double day,
        double hour, double minute, double second);
};

}  // namespace dateTime
}  // namespace YiEngine





#endif