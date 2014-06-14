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
/// ������Ϣ(ת��ʱ��������)
/// </summary>
struct JieQiInfo
{
    /// <summary>
    /// ��������
    /// </summary>
    jieqi::JIEQI_TYPE Name;

    /// <summary>
    /// ����ʱ��(������)
    /// </summary>
    DayInfo JDTime;

    /// <summary>
    /// ʵ������ʱ��(������, ���Ƚ���������)
    /// </summary>
    DayInfo HistoricalJDTime;

    /// <summary>
    /// ����ʱ����ʵ������ʱ���Ƿ���ڲ���ı��
    /// </summary>
    bool DifferentTime;

    /// <summary>
    /// ������־:  True - ��, False - ��
    /// </summary>
    bool JieOrQi;

    /// <summary>
    /// �½�(��֧), ���Խ����½�(�������½�)
    /// </summary>
    zhi::ZHI_TYPE YueJian;

    /// <summary>
    /// ʵ���½�(��֧), ���Խ����½�(�������½�)
    /// </summary>
    int DayDifference;
};

struct LunarDayObject
{
    // �յ�ũ����Ϣ

    /// <summary>
    /// ��ũ�����׵ı�����,0��Ӧ��һ
    /// </summary>
    double Ldi;       // ��ũ�����׵ı�����,0��Ӧ��һ

    /// <summary>
    /// ������(ũ��),��'��һ,������'
    /// </summary>
    chineseNum::CNUM_TYPE Ldc;       // ������(ũ��),��'��һ,������'

    /// <summary>
    /// �ඬ��������
    /// </summary>
    double cur_dz;       // �ඬ��������

    /// <summary>
    /// ������������
    /// </summary>
    double cur_xz;       // ������������

    /// <summary>
    /// �����������
    /// </summary>
    double cur_lq;       // �����������

    /// <summary>
    /// ��â�ֵ�����
    /// </summary>
    double cur_mz;       // ��â�ֵ�����

    /// <summary>
    /// ��С�������
    /// </summary>
    double cur_xs;       // ��С�������

    /// <summary>
    /// ��״��(ֵΪ'��'��մ�)
    /// </summary>
    bool Lleap;    // ��״��(ֵΪ'��'��մ�)

    /// <summary>
    /// ������
    /// </summary>
    chineseNum::CNUM_TYPE Lmc;       // ������

    /// <summary>
    /// �¸�������,�жϳ�ϦʱҪ�õ�
    /// </summary>
    chineseNum::CNUM_TYPE Lmc2;        // �¸�������,�жϳ�ϦʱҪ�õ�

    /// <summary>
    /// �´�С
    /// </summary>
    double Ldn;       // �´�С

    //�յ�ũ�����ꡢ�¡��ա�ʱ������

    /// <summary>
    /// ũ������(10����,1984������,�ֽ�����������Ҳ�����Ǵ���,�ڳ�����ѡ��һ��)
    /// </summary>
    double Lyear;       // ũ������(10����,1984������,�ֽ�����������Ҳ�����Ǵ���,�ڳ�����ѡ��һ��)

    /// <summary>
    /// ��֧����(����)
    /// </summary>
    commonDef::GANZHI Lyear2;       // ��֧����(����)

    /// <summary>
    /// ���´���,1998��12��7��(��ѩ)��ʼ�������н�������,0Ϊ����
    /// </summary>
    double Lmonth;       // ���´���,1998��12��7��(��ѩ)��ʼ�������н�������,0Ϊ����

    /// <summary>
    /// ��֧����
    /// </summary>
    commonDef::GANZHI Lmonth2;        // ��֧����

    /// <summary>
    /// ��֧����
    /// </summary>
    commonDef::GANZHI Lday2;        // ����

    /// <summary>
    /// ��֧��ʱ
    /// </summary>
    double Ltime2;       // ��ʱ

    /// <summary>
    /// ũ������(10����,1984������)
    /// </summary>
    double Lyear0;        // ũ������(10����,1984������)

    /// <summary>
    /// ��֧����(����)
    /// </summary>
    commonDef::GANZHI Lyear3;        // ��֧����(����)

    /// <summary>
    /// �Ƶۼ���
    /// </summary>
    double Lyear4;         // �Ƶۼ���

        /// <summary>
    /// ��������
    /// </summary>
    JieQiInfo jieQi;        // ��������

    /// <summary>
    /// ��������(ʵ��?)
    /// </summary>
    jieqi::JIEQI_TYPE Ljq;  
};

struct PublicDayObject
{
    // �յĹ�����Ϣ

    /// <summary>
    /// 2000.0����������,����ʱ12:00
    /// </summary>
    double d0;       // 2000.0����������,����ʱ12:00

    /// <summary>
    /// ���ڹ�������������
    /// </summary>
    double di;       // ���ڹ�������������

    /// <summary>
    /// ���ڹ�����,ͬlun.y
    /// </summary>
    int y;       // ���ڹ�����,ͬlun.y

    /// <summary>
    /// ���ڹ�����,ͬlun.m
    /// </summary>
    int m;       // ���ڹ�����,ͬlun.m

    /// <summary>
    /// ������(����)
    /// </summary>
    int d;       // ������(����)

    /// <summary>
    /// ���ڹ����µ�������,ͬlun.d0
    /// </summary>
    double dn;       // ���ڹ����µ�������,ͬlun.d0

    /// <summary>
    /// �����µ����׵�����,ͬlun.w0
    /// </summary>
    double week0;       // �����µ����׵�����,ͬlun.w0

    /// <summary>
    /// ����
    /// </summary>
    double week;        // ����

    /// <summary>
    /// �ڱ����е������
    /// </summary>
    double weeki;       // �ڱ����е������

    /// <summary>
    /// ���µ�������
    /// </summary>
    double weekN;       // ���µ�������

    /// <summary>
    /// ����
    /// </summary>
    constellation::CONSTELLATION_TYPE XiZ;        // ����
};

struct HuiDayObject
{
    //�յĻ�����Ϣ
        
    /// <summary>
    /// ��(����)
    /// </summary>
    double Hyear;       // ��(����)

    /// <summary>
    /// ��(����)
    /// </summary>
    double Hmonth;       // ��(����)

    /// <summary>
    /// ��(����)
    /// </summary>
    double Hday;       // ��(����)
};

struct FestivalObject
{
    FestivalObject(): Fjia(0) {}
    /// <summary>
    /// A ����ռ�����(��Ҫϲ����������(�ɽ����������ú�))
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> A;    

    /// <summary>
    /// B ����ռ�����(��Ҫ��������)
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> B;    

    /// <summary>
    /// C ����ռ�����(������������(����һ��, �Կո���ָ�))
    /// </summary>
    std::vector<festival::FESTIVAL_TYPE> C;    

    /// <summary>
    /// �żٵı�־
    /// </summary>
    double Fjia;    // = 0;

#if 0
    /// <summary>
    /// ÿ�յ�ʮ������Ϣ, ��: {��, ��, ��, ƽ, ��, ִ, ��, Σ, ��, ��, ��, ��} ����֮һ
    /// </summary>
    std::string Ri12Jian;
#endif
};

struct JieQiObject
{
    /// <summary>
    /// ��������
    /// </summary>
    JieQiInfo ThisJieQi;

    /// <summary>
    /// ��һ����
    /// </summary>
    JieQiInfo PreviousJieQi;

    /// <summary>
    /// ��һ����
    /// </summary>
    JieQiInfo NextJieQi;
};

struct MoonObject
{
    /// <summary>
    /// ��������
    /// </summary>
    lunarPhases::LUNARPHASES_TYPE yxmc;        // ��������

    /// <summary>
    /// ����ʱ��(������)
    /// </summary>
    double yxjd;         // ����ʱ��(������)

    /// <summary>
    /// ����ʱ�䴮
    /// </summary>
    std::string yxsj;        // ����ʱ�䴮
};

struct BaziObject
{
    /// <summary>
    /// ������Ϣ: ��̫��ʱ��
    /// </summary>
    DayInfo bz_zty;    

    /// <summary>
    /// ������Ϣ: ƽ̫��ʱ��
    /// </summary>
    DayInfo bz_pty;  

    /// <summary>
    /// ������Ϣ
    /// </summary>
    commonDef::Bazi bazi;

    /// <summary>
    /// ������Ϣ: ��֧��ʱ(����ʱ����ʱ�� 12 ��ʱ���ĸ�֧����, �Կո�ָ�
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