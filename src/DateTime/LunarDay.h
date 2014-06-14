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
/// ��������(�ռ�)
/// </summary>
enum BaZiTypeS
{
    /// <summary>
    /// ����(���������)
    /// </summary>
    Normal,

    /// <summary>
    /// �ϰ������: ���س�(����ɵ�֧���뱱�����ȡ�����)
    /// </summary>
    TianChongDiChong,

    /// <summary>
    /// �ϰ������: ��˵س�(�µ�֧�뱱�����ȡ�����, ���廢���·��������)
    /// </summary>
    TianKeDiChong,

    /// <summary>
    /// �ϰ������: ��ͬ�س�(�µ�֧�뱱�����ȡ�����, ������뱱�����ȡ����ͬ)
    /// </summary>
    TianTongDiChong
};

enum CalcJieQiType
{
    /// �������
    CalcJie,

    /// ��������
    CalcQi, 

    /// ����ں���
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