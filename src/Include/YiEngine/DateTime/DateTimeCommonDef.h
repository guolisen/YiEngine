#ifndef YIENGINE_DATETIME_COMMONDEF_H
#define YIENGINE_DATETIME_COMMONDEF_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>

#include <YiEngine/DateTime/DataTranslator.hpp>

namespace yiEngine
{
namespace dateTime
{
namespace commonDef
{
/// <summary>
/// 地球赤道半径(千米)
/// </summary>
const double cs_rEar = 6378.1366;              // 地球赤道半径(千米)

/// <summary>
/// 平均半径
/// </summary>
const double cs_rEarA = 0.99834 * cs_rEar;     // 平均半径

/// <summary>
/// 天文单位长度(千米)
/// </summary>
const double cs_AU = 1.49597870691e8;          // 天文单位长度(千米)

/// <summary>
/// Sin(太阳视差)
/// </summary>
const double cs_sinP = cs_rEar / cs_AU;        // sin(太阳视差)

/// <summary>
/// 太阳视差
/// </summary>
const double cs_PI = 0.0000426352097959108;    // 太阳视差, 即 Math.Asin(cs_sinP)

/// <summary>
/// 每弧度的角秒数
/// </summary>
const double RAD = 180 * 3600 / M_PI;    // 每弧度的角秒数

/// <summary>
/// 圆周率的2倍
/// </summary>
const double pi2 = M_PI * 2;             // 圆周率的2倍,即2*3.14159...

/// <summary>
/// 2000年1月1日 12:00:00 的儒略日数
/// </summary>
const double J2000 = 2451545;               // 2000年1月1日 12:00:00 的儒略日数

struct LunarInfo
{
    LunarInfo(): lunarInfoList_(31, 0.0) {}

    /// <summary>
    /// 升(时间串)
    /// </summary>
    std::string s;    // = "";

    /// <summary>
    /// 中(时间串)
    /// </summary>
    std::string z;    // = "";

    /// <summary>
    /// 降(时间串)
    /// </summary>
    std::string j;    // = "";

    /// <summary>
    /// 晨(时间串)
    /// </summary>
    std::string c;    // = "";

    /// <summary>
    /// 昏(时间串)
    /// </summary>
    std::string h;    // = "";

    /// <summary>
    /// 日照时间(串)
    /// </summary>
    std::string ch;    // = "";

    /// <summary>
    /// 昼长(时间串)
    /// </summary>
    std::string sj;    // = "";
        
    /// <summary>
    /// 月出时间(串)
    /// </summary>
    std::string Ms;    // = "";

    /// <summary>
    /// 月亮中天时间(串)
    /// </summary>
    std::string Mz;    // = "";

    /// <summary>
    /// 月落时间(串)
    /// </summary>
    std::string Mj;    // = "";

    /// <summary>
    /// 本属性(字段)有不同的含义： 
    /// (1) 用于月对象 LunarInfoListT<OB> lun 的属性(字段) dn: 该月的总天数； 
    /// (2) 用于多天的升中降容器 LunarInfoListT<LunarInfoListT<double>> rts 的属性(字段) dn: 要求计算升中降信息的天数
    /// </summary>
    double dn;    // = 0;

    /// <summary>
    /// 指定时刻的天体时角
    /// </summary>
    double H;    // = 0;

    /// <summary>
    /// 本属性(字段)有不同的含义： 升起对应的时角(月亮?), 或地平以下50分的时角(太阳?)
    /// </summary>
    double H0;    // = 0;

    /// <summary>
    /// 地平以下6度的时角(太阳?)
    /// </summary>
    double H1;    // = 0;

    /// <summary>
    /// 节气的儒略日
    /// </summary>
    double pe1;    // = 0;

    /// <summary>
    /// 节气的儒略日
    /// </summary>
    double pe2;    // = 0;

    std::vector<double> lunarInfoList_;
};

struct GANZHI
{
public:
    gan::GAN_TYPE gan;
    zhi::ZHI_TYPE zhi;

    GANZHI():gan(gan::JIA_VAL), zhi(zhi::ZI_VAL) {}
    GANZHI(const gan::GAN_TYPE& ganParam, const zhi::ZHI_TYPE& zhiParam): 
        gan(ganParam), zhi(zhiParam) {}

    GANZHI(const GANZHI& other)
    {
        gan = other.gan;
        zhi = other.zhi;
    }

    GANZHI& operator=(const GANZHI& r)
    {
        gan = r.gan;
        zhi = r.zhi;
        return *this;
    }

    operator std::string() 
    {
        return gan + zhi;
    }
};

struct Bazi{
    GANZHI year_;
    GANZHI month_;
    GANZHI day_;
    GANZHI time_;

    Bazi() {}

    Bazi(const Bazi& other)
    {
        year_ = other.year_;
        month_ = other.month_;
        day_ = other.day_;
        time_ = other.time_;
    }

    operator std::string() 
    {
        return (std::string)year_ + " " + (std::string)month_ + " " + (std::string)day_ + " " + (std::string)time_;
    }
};

// 干
const gan::GAN_TYPE GAN_TABLE[10] = { gan::JIA_VAL, gan::YI_VAL, gan::BING_VAL, gan::DING_VAL, gan::WU_VAL, 
    gan::JI_VAL, gan::GENG_VAL, gan::XIN_VAL, gan::REN_VAL, gan::GUI_VAL};
// 支
const zhi::ZHI_TYPE ZHI_TABLE[12] = { zhi::ZI_VAL, zhi::CHOU_VAL, zhi::YIN_VAL, zhi::MAO_VAL, zhi::CHEN_VAL,
    zhi::SI_VAL, zhi::WU_VAL, zhi::WEI_VAL, zhi::SHEN_VAL, zhi::YOU_VAL, zhi::XU_VAL, zhi::HAI_VAL};

//中文数字
const chineseNum::CNUM_TYPE CNUM_TABLE[11] = 
{ 
    chineseNum::ZERO_VAL, chineseNum::ONE_VAL, chineseNum::TWO_VAL, chineseNum::THREE_VAL, chineseNum::FOUR_VAL, chineseNum::FIVE_VAL,
    chineseNum::SIX_VAL, chineseNum::SEVEN_VAL, chineseNum::EIGHT_VAL, chineseNum::NINE_VAL, chineseNum::TEN_VAL
};

// 属相
const shuXiang::SHUXIANG_TYPE SHUXIANG_TABLE[12] = 
{ 
    shuXiang::MOUSE_VAL, shuXiang::CATTLE_VAL, shuXiang::TIGER_VAL, shuXiang::RABBIT_VAL, shuXiang::DRAGON_VAL,
    shuXiang::SNAKE_VAL, shuXiang::HORSE_VAL, shuXiang::SHEEP_VAL, shuXiang::MONKEY_VAL, shuXiang::CHIKEN_VAL,
    shuXiang::DOG_VAL, shuXiang::PIG_VAL
};

// 月相
const lunarPhases::LUNARPHASES_TYPE LUNARPHASES_TABLE[4] = 
{ 
        lunarPhases::SHUO_VAL,
        lunarPhases::SHANGXIAN_VAL,
        lunarPhases::WANG_VAL,
        lunarPhases::XIAXIAN_VAL
};

// 节气
const jieqi::JIEQI_TYPE JIEQI_TABLE[24] = 
{ 
    jieqi::DONGZHI_VAL,
    jieqi::XIAOHAN_VAL,
    jieqi::DAHAN_VAL,
    jieqi::LICHUN_VAL,
    jieqi::YUSHUI_VAL,
    jieqi::JINGZHE_VAL,
    jieqi::CHUNFEN_VAL,
    jieqi::QINGMING_VAL,
    jieqi::GUYU_VAL,
    jieqi::LIXIA_VAL,
    jieqi::XIAO_MAN_VAL,
    jieqi::MANGZHONG_VAL,
    jieqi::XIAZHI_VAL,
    jieqi::XIAOSHU_VAL,
    jieqi::DASHU_VAL,
    jieqi::LIQIU_VAL,
    jieqi::CHUSHU_VAL,
    jieqi::BAILU_VAL,
    jieqi::QIUFEN_VAL,
    jieqi::HANLU_VAL,
    jieqi::SHUANGJIANG_VAL,
    jieqi::LIDONG_VAL,
    jieqi::XIAOXUE_VAL,
    jieqi::DAXUE_VAL
};

// 中国月
const chineseNum::CNUM_TYPE CHINESE_MONTH_TABLE[12] = 
{ 
    chineseNum::ELEVEN_VAL,
    chineseNum::TWELVE_VAL,
    chineseNum::ZHENG_VAL,
    chineseNum::TWO_VAL,
    chineseNum::THREE_VAL,
    chineseNum::FOUR_VAL,
    chineseNum::FIVE_VAL,
    chineseNum::SIX_VAL,
    chineseNum::SEVEN_VAL,
    chineseNum::EIGHT_VAL,
    chineseNum::NINE_VAL,
    chineseNum::TEN_VAL,
};

//中国日
const chineseNum::CNUM_TYPE CHINESE_MONTH_DAY_TABLE[31] = 
{ 
    chineseNum::CHU_YI_VAL,
    chineseNum::CHU_ER_VAL,
    chineseNum::CHU_SAN_VAL,
    chineseNum::CHU_SI_VAL,
    chineseNum::CHU_WU_VAL,
    chineseNum::CHU_LIU_VAL,
    chineseNum::CHU_QI_VAL,
    chineseNum::CHU_BA_VAL,
    chineseNum::CHU_JIU_VAL,
    chineseNum::CHU_SHI_VAL,
    chineseNum::ELEVEN_VAL,
    chineseNum::TWELVE_VAL,
    chineseNum::THIRTEEN_VAL,
    chineseNum::FOURTEEN_VAL,
    chineseNum::FIFTEEN_VAL,
    chineseNum::SIXTEEN_VAL,
    chineseNum::SEVENTEEN_VAL,
    chineseNum::EIGHTEEN_VAL,
    chineseNum::NINETEEN_VAL,
    chineseNum::TWENTY_VAL,
    chineseNum::TWENTY_ONE_VAL,
    chineseNum::TWENTY_TWO_VAL,
    chineseNum::TWENTY_THREE_VAL,
    chineseNum::TWENTY_FOUR_VAL,
    chineseNum::TWENTY_FIVE_VAL,
    chineseNum::TWENTY_SIX_VAL,
    chineseNum::TWENTY_SEVEN_VAL,
    chineseNum::TWENTY_EIGHT_VAL,
    chineseNum::TWENTY_NINE_VAL,
    chineseNum::THIRTY_VAL,
    chineseNum::THIRTY_ONE_VAL,
};

// 节气对应月
const zhi::ZHI_TYPE JIEQI_MAP_TABLE[24] = 
{ 
    zhi::ZI_VAL, 
    zhi::CHOU_VAL, 
    zhi::CHOU_VAL, 
    zhi::YIN_VAL, 
    zhi::YIN_VAL, 
    zhi::MAO_VAL,
    zhi::MAO_VAL,
    zhi::CHEN_VAL,
    zhi::CHEN_VAL,
    zhi::SI_VAL, 
    zhi::SI_VAL, 
    zhi::WU_VAL, 
    zhi::WU_VAL,
    zhi::WEI_VAL, 
    zhi::WEI_VAL,
    zhi::SHEN_VAL,
    zhi::SHEN_VAL,
    zhi::YOU_VAL, 
    zhi::YOU_VAL, 
    zhi::XU_VAL, 
    zhi::XU_VAL, 
    zhi::HAI_VAL,
    zhi::HAI_VAL,
    zhi::ZI_VAL
};

const festival::FESTIVAL_TYPE SHU_JIU[9] = 
{
    festival::YI_JIU_VAL,
    festival::ER_JIU_VAL,
    festival::SAN_JIU_VAL,
    festival::SI_JIU_VAL,
    festival::WU_JIU_VAL,
    festival::LIU_JIU_VAL,
    festival::QI_JIU_VAL,
    festival::BA_JIU_VAL,
    festival::JIU_JIU_VAL
};

const constellation::CONSTELLATION_TYPE Constellation_Tab[12] =
{
    constellation::CAPRICORN_VAL,
    constellation::AQUARIUS_VAL,
    constellation::PISCES_VAL,
    constellation::ARIES_VAL,
    constellation::TAURUS_VAL,
    constellation::GEMINI_VAL,
    constellation::CANCER_VAL,
    constellation::LEO_VAL,
    constellation::VIRGO_VAL,
    constellation::LIBRA_VAL,
    constellation::SCORPIO_VAL,
    constellation::SAGITTARIUS_VAL
};

/// <summary>
/// 对超过0-2PI的角度转为0-2PI
/// </summary>
/// <param name="v">要转换的角度</param>
/// <returns></returns>
inline double rad2mrad(double v)
{
    v = fmod(v, (2 * M_PI));
    if (v < 0) 
        v += 2 * M_PI;
    return v;
}

/// <summary>
/// 对超过-PI到PI的角度转为-PI到PI
/// </summary>
/// <param name="v">要转换的角度</param>
/// <returns></returns>
inline double rad2rrad(double v)
{
    v = fmod(v, (2 * M_PI));
    if (v <= -M_PI) return v + 2 * M_PI;
    if (v > M_PI) return v - 2 * M_PI;
    return v;
}

/// <summary>
/// double 比较
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
inline bool EQ_DOUBLE(double left, double right)
{
    const double EPS = 1e-5;
    return (fabs(left - right) < EPS)? true: false;
}

inline double Angle2Rad(double d, double m, double s)
{
    double a = 0, b = 0, c = 0;
    a = d / 180 * M_PI;                     // 1°= 1/180*PI ≈ 0.017453292519943 弧度
    b = m / 60 / 180 * M_PI;            // 1' = (1/60)°≈ 0.000290888208666 弧度
    c = s / 60 / 180 / 60 * M_PI;   // 1" = (1/60)' ≈ 0.000004848136811 弧度

    double result = 0.0;
    if (a > 0)
        result = a + b + c;
    else
        result = a - b - c;

    return result;
}

}  // namespace commonDef
}  // namespace dateTime
}  // namespace YiEngine
#endif