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
/// �������뾶(ǧ��)
/// </summary>
const double cs_rEar = 6378.1366;              // �������뾶(ǧ��)

/// <summary>
/// ƽ���뾶
/// </summary>
const double cs_rEarA = 0.99834 * cs_rEar;     // ƽ���뾶

/// <summary>
/// ���ĵ�λ����(ǧ��)
/// </summary>
const double cs_AU = 1.49597870691e8;          // ���ĵ�λ����(ǧ��)

/// <summary>
/// Sin(̫���Ӳ�)
/// </summary>
const double cs_sinP = cs_rEar / cs_AU;        // sin(̫���Ӳ�)

/// <summary>
/// ̫���Ӳ�
/// </summary>
const double cs_PI = 0.0000426352097959108;    // ̫���Ӳ�, �� Math.Asin(cs_sinP)

/// <summary>
/// ÿ���ȵĽ�����
/// </summary>
const double RAD = 180 * 3600 / M_PI;    // ÿ���ȵĽ�����

/// <summary>
/// Բ���ʵ�2��
/// </summary>
const double pi2 = M_PI * 2;             // Բ���ʵ�2��,��2*3.14159...

/// <summary>
/// 2000��1��1�� 12:00:00 ����������
/// </summary>
const double J2000 = 2451545;               // 2000��1��1�� 12:00:00 ����������

struct LunarInfo
{
    LunarInfo(): lunarInfoList_(31, 0.0) {}

    /// <summary>
    /// ��(ʱ�䴮)
    /// </summary>
    std::string s;    // = "";

    /// <summary>
    /// ��(ʱ�䴮)
    /// </summary>
    std::string z;    // = "";

    /// <summary>
    /// ��(ʱ�䴮)
    /// </summary>
    std::string j;    // = "";

    /// <summary>
    /// ��(ʱ�䴮)
    /// </summary>
    std::string c;    // = "";

    /// <summary>
    /// ��(ʱ�䴮)
    /// </summary>
    std::string h;    // = "";

    /// <summary>
    /// ����ʱ��(��)
    /// </summary>
    std::string ch;    // = "";

    /// <summary>
    /// �糤(ʱ�䴮)
    /// </summary>
    std::string sj;    // = "";
        
    /// <summary>
    /// �³�ʱ��(��)
    /// </summary>
    std::string Ms;    // = "";

    /// <summary>
    /// ��������ʱ��(��)
    /// </summary>
    std::string Mz;    // = "";

    /// <summary>
    /// ����ʱ��(��)
    /// </summary>
    std::string Mj;    // = "";

    /// <summary>
    /// ������(�ֶ�)�в�ͬ�ĺ��壺 
    /// (1) �����¶��� LunarInfoListT<OB> lun ������(�ֶ�) dn: ���µ��������� 
    /// (2) ���ڶ�������н����� LunarInfoListT<LunarInfoListT<double>> rts ������(�ֶ�) dn: Ҫ��������н���Ϣ������
    /// </summary>
    double dn;    // = 0;

    /// <summary>
    /// ָ��ʱ�̵�����ʱ��
    /// </summary>
    double H;    // = 0;

    /// <summary>
    /// ������(�ֶ�)�в�ͬ�ĺ��壺 �����Ӧ��ʱ��(����?), ���ƽ����50�ֵ�ʱ��(̫��?)
    /// </summary>
    double H0;    // = 0;

    /// <summary>
    /// ��ƽ����6�ȵ�ʱ��(̫��?)
    /// </summary>
    double H1;    // = 0;

    /// <summary>
    /// ������������
    /// </summary>
    double pe1;    // = 0;

    /// <summary>
    /// ������������
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

// ��
const gan::GAN_TYPE GAN_TABLE[10] = { gan::JIA_VAL, gan::YI_VAL, gan::BING_VAL, gan::DING_VAL, gan::WU_VAL, 
    gan::JI_VAL, gan::GENG_VAL, gan::XIN_VAL, gan::REN_VAL, gan::GUI_VAL};
// ֧
const zhi::ZHI_TYPE ZHI_TABLE[12] = { zhi::ZI_VAL, zhi::CHOU_VAL, zhi::YIN_VAL, zhi::MAO_VAL, zhi::CHEN_VAL,
    zhi::SI_VAL, zhi::WU_VAL, zhi::WEI_VAL, zhi::SHEN_VAL, zhi::YOU_VAL, zhi::XU_VAL, zhi::HAI_VAL};

//��������
const chineseNum::CNUM_TYPE CNUM_TABLE[11] = 
{ 
    chineseNum::ZERO_VAL, chineseNum::ONE_VAL, chineseNum::TWO_VAL, chineseNum::THREE_VAL, chineseNum::FOUR_VAL, chineseNum::FIVE_VAL,
    chineseNum::SIX_VAL, chineseNum::SEVEN_VAL, chineseNum::EIGHT_VAL, chineseNum::NINE_VAL, chineseNum::TEN_VAL
};

// ����
const shuXiang::SHUXIANG_TYPE SHUXIANG_TABLE[12] = 
{ 
    shuXiang::MOUSE_VAL, shuXiang::CATTLE_VAL, shuXiang::TIGER_VAL, shuXiang::RABBIT_VAL, shuXiang::DRAGON_VAL,
    shuXiang::SNAKE_VAL, shuXiang::HORSE_VAL, shuXiang::SHEEP_VAL, shuXiang::MONKEY_VAL, shuXiang::CHIKEN_VAL,
    shuXiang::DOG_VAL, shuXiang::PIG_VAL
};

// ����
const lunarPhases::LUNARPHASES_TYPE LUNARPHASES_TABLE[4] = 
{ 
        lunarPhases::SHUO_VAL,
        lunarPhases::SHANGXIAN_VAL,
        lunarPhases::WANG_VAL,
        lunarPhases::XIAXIAN_VAL
};

// ����
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

// �й���
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

//�й���
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

// ������Ӧ��
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
/// �Գ���0-2PI�ĽǶ�תΪ0-2PI
/// </summary>
/// <param name="v">Ҫת���ĽǶ�</param>
/// <returns></returns>
inline double rad2mrad(double v)
{
    v = fmod(v, (2 * M_PI));
    if (v < 0) 
        v += 2 * M_PI;
    return v;
}

/// <summary>
/// �Գ���-PI��PI�ĽǶ�תΪ-PI��PI
/// </summary>
/// <param name="v">Ҫת���ĽǶ�</param>
/// <returns></returns>
inline double rad2rrad(double v)
{
    v = fmod(v, (2 * M_PI));
    if (v <= -M_PI) return v + 2 * M_PI;
    if (v > M_PI) return v - 2 * M_PI;
    return v;
}

/// <summary>
/// double �Ƚ�
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
    a = d / 180 * M_PI;                     // 1��= 1/180*PI �� 0.017453292519943 ����
    b = m / 60 / 180 * M_PI;            // 1' = (1/60)��� 0.000290888208666 ����
    c = s / 60 / 180 / 60 * M_PI;   // 1" = (1/60)' �� 0.000004848136811 ����

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