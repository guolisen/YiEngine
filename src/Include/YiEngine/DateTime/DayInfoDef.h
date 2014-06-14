#ifndef YIENGINE_COMMON_DAYINFO_H
#define YIENGINE_COMMON_DAYINFO_H

#include <iostream>
#include <vector>
#include <boost/smart_ptr.hpp>

#include <YiEngine/DateTime/DataTranslator.hpp>
#include <YiEngine/DateTime/DateTimeCommonDef.h>

namespace yiEngine
{
namespace dateTime
{

class DayInfo
{
public:
    DayInfo(): year_(0), month_(0), day_(0), 
        hour_(0), minute_(0), second_(0), 
        julianDay_(0), julianDayJ2k_(0) {}

    DayInfo(double year, double month, double day, 
            double hour, double minute, double second, double julianDay): 
            year_(year), month_(month), day_(day), 
            hour_(hour), minute_(minute), second_(second), 
            julianDay_(julianDay), julianDayJ2k_(julianDay - commonDef::J2000) {}

    DayInfo(const DayInfo& other)
    {
        year_   = other.year_;
        month_  = other.month_;
        day_    = other.day_;
        hour_   = other.hour_;
        minute_ = other.minute_;
        second_ = other.second_;
        julianDay_    = other.julianDay_;
        julianDayJ2k_ = other.julianDayJ2k_;
    }

public:
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
    virtual double GetJulianDay() const
    {
        return julianDay_;
    }
    virtual double GetJulianDayJ2k() const
    {
        return julianDayJ2k_;
    }
    
private:
    double year_;
    double month_;
    double day_;
    double hour_;
    double minute_;
    double second_;
    double julianDay_;
    double julianDayJ2k_;
};

typedef DayInfo JulianDayInfo;

/// <summary>
/// 节气信息(转换时新增的类)
/// </summary>
struct JieQiInfo
{
    /// <summary>
    /// 节气名称
    /// </summary>
    jieqi::JIEQI_TYPE Name;

    /// <summary>
    /// 交节时间(儒历日)
    /// </summary>
    DayInfo JDTime;

    /// <summary>
    /// 实历交节时间(儒历日, 精度仅至年月日)
    /// </summary>
    DayInfo HistoricalJDTime;

    /// <summary>
    /// 交节时间与实历交节时间是否存在差异的标记
    /// </summary>
    bool DifferentTime;

    /// <summary>
    /// 节气标志:  True - 节, False - 气
    /// </summary>
    bool JieOrQi;

    /// <summary>
    /// 月建(地支), 仅对节论月建(气不论月建)
    /// </summary>
    zhi::ZHI_TYPE YueJian;

    /// <summary>
    /// 实历月建(地支), 仅对节论月建(气不论月建)
    /// </summary>
    int DayDifference;
};

struct LunarDayObject
{
    // 日的农历信息

    /// <summary>
    /// 距农历月首的编移量,0对应初一
    /// </summary>
    double Ldi;       // 距农历月首的编移量,0对应初一

    /// <summary>
    /// 日名称(农历),即'初一,初二等'
    /// </summary>
    chineseNum::CNUM_TYPE Ldc;       // 日名称(农历),即'初一,初二等'

    /// <summary>
    /// 距冬至的天数
    /// </summary>
    double cur_dz;       // 距冬至的天数

    /// <summary>
    /// 距夏至的天数
    /// </summary>
    double cur_xz;       // 距夏至的天数

    /// <summary>
    /// 距立秋的天数
    /// </summary>
    double cur_lq;       // 距立秋的天数

    /// <summary>
    /// 距芒种的天数
    /// </summary>
    double cur_mz;       // 距芒种的天数

    /// <summary>
    /// 距小暑的天数
    /// </summary>
    double cur_xs;       // 距小暑的天数

    /// <summary>
    /// 闰状况(值为'闰'或空串)
    /// </summary>
    bool Lleap;    // 闰状况(值为'闰'或空串)

    /// <summary>
    /// 月名称
    /// </summary>
    chineseNum::CNUM_TYPE Lmc;       // 月名称

    /// <summary>
    /// 下个月名称,判断除夕时要用到
    /// </summary>
    chineseNum::CNUM_TYPE Lmc2;        // 下个月名称,判断除夕时要用到

    /// <summary>
    /// 月大小
    /// </summary>
    double Ldn;       // 月大小

    //日的农历纪年、月、日、时及星座

    /// <summary>
    /// 农历纪年(10进制,1984年起算,分界点可以是立春也可以是春节,在程序中选择一个)
    /// </summary>
    double Lyear;       // 农历纪年(10进制,1984年起算,分界点可以是立春也可以是春节,在程序中选择一个)

    /// <summary>
    /// 干支纪年(立春)
    /// </summary>
    commonDef::GANZHI Lyear2;       // 干支纪年(立春)

    /// <summary>
    /// 纪月处理,1998年12月7日(大雪)开始连续进行节气计数,0为甲子
    /// </summary>
    double Lmonth;       // 纪月处理,1998年12月7日(大雪)开始连续进行节气计数,0为甲子

    /// <summary>
    /// 干支纪月
    /// </summary>
    commonDef::GANZHI Lmonth2;        // 干支纪月

    /// <summary>
    /// 干支纪日
    /// </summary>
    commonDef::GANZHI Lday2;        // 纪日

    /// <summary>
    /// 干支纪时
    /// </summary>
    double Ltime2;       // 纪时

    /// <summary>
    /// 农历纪年(10进制,1984年起算)
    /// </summary>
    double Lyear0;        // 农历纪年(10进制,1984年起算)

    /// <summary>
    /// 干支纪年(正月)
    /// </summary>
    commonDef::GANZHI Lyear3;        // 干支纪年(正月)

    /// <summary>
    /// 黄帝纪年
    /// </summary>
    double Lyear4;         // 黄帝纪年

        /// <summary>
    /// 节气名称
    /// </summary>
    JieQiInfo jieQi;        // 节气名称

    /// <summary>
    /// 节气名称(实历?)
    /// </summary>
    jieqi::JIEQI_TYPE Ljq;  
};

struct PublicDayObject
{
    // 日的公历信息

    /// <summary>
    /// 2000.0起算儒略日,北京时12:00
    /// </summary>
    double d0;       // 2000.0起算儒略日,北京时12:00

    /// <summary>
    /// 所在公历月内日序数
    /// </summary>
    double di;       // 所在公历月内日序数

    /// <summary>
    /// 所在公历年,同lun.y
    /// </summary>
    int y;       // 所在公历年,同lun.y

    /// <summary>
    /// 所在公历月,同lun.m
    /// </summary>
    int m;       // 所在公历月,同lun.m

    /// <summary>
    /// 日名称(公历)
    /// </summary>
    int d;       // 日名称(公历)

    /// <summary>
    /// 所在公历月的总天数,同lun.d0
    /// </summary>
    double dn;       // 所在公历月的总天数,同lun.d0

    /// <summary>
    /// 所在月的月首的星期,同lun.w0
    /// </summary>
    double week0;       // 所在月的月首的星期,同lun.w0

    /// <summary>
    /// 星期
    /// </summary>
    double week;        // 星期

    /// <summary>
    /// 在本月中的周序号
    /// </summary>
    double weeki;       // 在本月中的周序号

    /// <summary>
    /// 本月的总周数
    /// </summary>
    double weekN;       // 本月的总周数

    /// <summary>
    /// 星座
    /// </summary>
    constellation::CONSTELLATION_TYPE XiZ;        // 星座
};

struct HuiDayObject
{
    //日的回历信息
        
    /// <summary>
    /// 年(回历)
    /// </summary>
    double Hyear;       // 年(回历)

    /// <summary>
    /// 月(回历)
    /// </summary>
    double Hmonth;       // 月(回历)

    /// <summary>
    /// 日(回历)
    /// </summary>
    double Hday;       // 日(回历)
};

struct FestivalObject
{
    FestivalObject(): Fjia(0) {}
    /// <summary>
    /// A 类节日纪念日(重要喜庆日子名称(可将日子名称置红))
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> A;    

    /// <summary>
    /// B 类节日纪念日(重要日子名称)
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> B;    

    /// <summary>
    /// C 类节日纪念日(各种日子名称(连成一大串, 以空格符分隔))
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> C;    

    /// <summary>
    /// 放假的标志
    /// </summary>
    double Fjia;    // = 0;

#if 0
    /// <summary>
    /// 每日的十二建信息, 即: {建, 除, 满, 平, 定, 执, 破, 危, 成, 收, 开, 闭} 其中之一
    /// </summary>
    std::string Ri12Jian;
#endif
};

struct JieQiObject
{
    /// <summary>
    /// 所属节令
    /// </summary>
    JieQiInfo ThisJieQi;

    /// <summary>
    /// 上一节令
    /// </summary>
    JieQiInfo PreviousJieQi;

    /// <summary>
    /// 下一节令
    /// </summary>
    JieQiInfo NextJieQi;
};

struct MoonObject
{
    /// <summary>
    /// 月相名称
    /// </summary>
    lunarPhases::LUNARPHASES_TYPE yxmc;        // 月相名称

    /// <summary>
    /// 月相时刻(儒略日)
    /// </summary>
    double yxjd;         // 月相时刻(儒略日)

    /// <summary>
    /// 月相时间串
    /// </summary>
    std::string yxsj;        // 月相时间串
};

struct BaziObject
{
    /// <summary>
    /// 八字信息: 真太阳时间
    /// </summary>
    DayInfo bz_zty;    

    /// <summary>
    /// 八字信息: 平太阳时间
    /// </summary>
    DayInfo bz_pty;  

    /// <summary>
    /// 八字信息
    /// </summary>
    commonDef::Bazi bazi;

    /// <summary>
    /// 八字信息: 干支纪时(从子时至亥时共 12 个时辰的干支集合, 以空格分隔
    /// </summary>
    std::vector<commonDef::GANZHI> bz_JS;      
};

struct Day
{     
    PublicDayObject publicDay;
    LunarDayObject  lunarDay;
    JieQiObject     jieqiObj;
    HuiDayObject    huiliDay;
    FestivalObject  festivalDay;
    MoonObject      moonObj;
    BaziObject      bazi;
};

}  // namespace dateTime
}  // namespace YiEngine

#endif