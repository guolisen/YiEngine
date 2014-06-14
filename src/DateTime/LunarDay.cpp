
#include <string>
#include <YiEngine/DateTime/DataTranslator.hpp>
#include <YiEngine/DateTime/DateTimeCommonDef.h>
#include "LunarDay.h"


namespace yiEngine
{
namespace dateTime
{

template<>
bool GetBuilder<LunarDayObject>(boost::shared_ptr<IDayBuilder<LunarDayObject> >& obj)
{
    obj = boost::make_shared<LunarDayBuilder>();
    return true;
}

template<>
bool GetBuilder<JieQiObject>(boost::shared_ptr<IDayBuilder<JieQiObject> >& obj)
{
    obj = boost::make_shared<LunarJieqiDayBuilder>();
    return true;
}

template<>
bool GetBuilder<FestivalObject>(boost::shared_ptr<IDayBuilder<FestivalObject> >& obj)
{
    obj = boost::make_shared<FestivalDayBuilder>();
    return true;
}

template<>
bool GetBuilder<BaziObject>(boost::shared_ptr<IDayBuilder<BaziObject> >& obj)
{
    obj = boost::make_shared<BaZiBuilder>();
    return true;
}

bool LunarDay::DayCalculate(LunarDayObject& obj)
{
    JulianDay todayJd(julianDay_.GetYear(), julianDay_.GetMonth(), julianDay_.GetDay(), 
        12.0, 0.0, 0.0);
    double Bd0 = floor(todayJd.GregorianDayToJulianDay() - commonDef::J2000);
    double d0 = Bd0; ///?

    if(moonCalculate_.ZQ.lunarInfoList_.empty() || d0 < moonCalculate_.ZQ.lunarInfoList_[0] || d0 >= moonCalculate_.ZQ.lunarInfoList_[24])
        moonCalculate_.calcY(d0);

    int mk = (int)floor((d0 - moonCalculate_.HS[0]) / 30); 
    if (mk < 13 && moonCalculate_.HS[mk + 1] <= d0) 
        mk++; // ũ�������µ�����

    obj.Ldi = (int)(d0 - moonCalculate_.HS[mk]);   // ��ũ�����׵ı�����,0��Ӧ��һ
    obj.Ldc = commonDef::CHINESE_MONTH_DAY_TABLE[(int)(obj.Ldi)];      // ũ��������
    obj.cur_dz = d0 - moonCalculate_.ZQ.lunarInfoList_[0];     // �ඬ��������
    obj.cur_xz = d0 - moonCalculate_.ZQ.lunarInfoList_[12];    // ������������
    obj.cur_lq = d0 - moonCalculate_.ZQ.lunarInfoList_[15];    // �����������
    obj.cur_mz = d0 - moonCalculate_.ZQ.lunarInfoList_[11];    // ��â�ֵ�����
    obj.cur_xs = d0 - moonCalculate_.ZQ.lunarInfoList_[13];    // ��С�������

    if (commonDef::EQ_DOUBLE(d0, moonCalculate_.HS[mk]) || commonDef::EQ_DOUBLE(d0, Bd0))
    {   
        // �µ���Ϣ
        obj.Lmc = moonCalculate_.ym[mk];  // ������
        obj.Ldn = moonCalculate_.dx[mk];  // �´�С
        obj.Lleap = (moonCalculate_.leap != 0 && moonCalculate_.leap == mk) ? true : false;   // ��״��
        if(mk < 13)
            obj.Lmc2 = moonCalculate_.ym[mk + 1]; // �¸�������,�жϳ�ϦʱҪ�õ�
        else
            obj.Lmc2 = moonCalculate_.ym[(mk + 1) % 12];
    }
    else
    {
        //ob2 = (this.lun[i - 1]);
        //obj.Lmc = ob2.Lmc; obj.Ldn = ob2.Ldn;
        //obj.Lleap = ob2.Lleap; obj.Lmc2 = ob2.Lmc2;
    }

    int qk = (int)floor((d0 - moonCalculate_.ZQ.lunarInfoList_[0] - 7) / 15.2184); 
    if (qk < 23 && d0 >= moonCalculate_.ZQ.lunarInfoList_[qk + 1]) 
        qk++; //������ȡֵ��Χ��0-23
                
    if (commonDef::EQ_DOUBLE(d0, moonCalculate_.ZQ.lunarInfoList_[qk])) 
        obj.Ljq = commonDef::JIEQI_TABLE[qk];

    // ��֧���괦��
    // ������Ϊ�綨����
    double D = moonCalculate_.ZQ.lunarInfoList_[3] + (d0 < moonCalculate_.ZQ.lunarInfoList_[3] ? -365 : 0) + 365.25 * 16 - 35; //������Ϊ�綨����
    obj.Lyear = floor(D / 365.2422 + 0.5); //ũ������(10����,1984������)

    // ���¼��������³�һ������
    D = moonCalculate_.HS[2];     // һ���3����Ϊ����
    for (int j = 0; j < 14; j++)
    { 
        // �Ҵ���
        if (moonCalculate_.ym[j] != chineseNum::ZHENG_VAL) 
            continue;
        D = moonCalculate_.HS[j];
        if (d0 < D) 
        { 
            D -= 365; 
            break;  // ����������һ������
        }   
    }

    D = D + 5810;    // ������괺����1984��ƽ������(��������)�����������
    obj.Lyear0 = floor(D / 365.2422 + 0.5);   // ũ������(10����,1984������)

    D = obj.Lyear + 9000; 

    obj.Lyear2.gan = commonDef::GAN_TABLE[(int)fmod(D, 10)];  // ��֧����(����)
    obj.Lyear2.zhi = commonDef::ZHI_TABLE[(int)fmod(D, 12)];    
            
    D = obj.Lyear0 + 9000;
    obj.Lyear3.gan = commonDef::GAN_TABLE[(int)fmod(D, 10)];  // ��֧����(����)
    obj.Lyear3.zhi = commonDef::ZHI_TABLE[(int)fmod(D, 12)];  
    obj.Lyear4 = obj.Lyear0 + 1984 + 2698;    // �Ƶۼ���

    // ���´���,1998��12��7(��ѩ)��ʼ�������н�������,0Ϊ����
    mk = (int)floor((d0 - moonCalculate_.ZQ.lunarInfoList_[0]) / 30.43685); 
    if (mk < 12 && d0 >= moonCalculate_.ZQ.lunarInfoList_[2 * mk + 1]) 
        mk++;  //��Դ�ѩ����������,mk��ȡֵ��Χ0-12

    D = mk + floor((moonCalculate_.ZQ.lunarInfoList_[12] + 390) / 365.2422) * 12 + 900000; //�����1998��12��7(��ѩ)������,900000Ϊ��������
    obj.Lmonth = fmod(D, 12);
   
    obj.Lmonth2.gan = commonDef::GAN_TABLE[(int)fmod(D, 10)];  // ��֧����(����)
    obj.Lmonth2.zhi = commonDef::ZHI_TABLE[(int)fmod(D, 12)];

    // ����,2000��1��7������
    D = d0 - 6 + 9000000;
    obj.Lday2.gan = commonDef::GAN_TABLE[(int)fmod(D, 10)];  // ��֧����(����)
    obj.Lday2.zhi = commonDef::ZHI_TABLE[(int)fmod(D, 12)];

    if((bool)obj.Ljq)
    {
        std::vector<JieQiInfo>::iterator iter;
        for(iter = jieqiTab_.begin(); iter != jieqiTab_.end(); ++iter)
        {
            if(obj.Ljq == iter->Name)
            {
                obj.jieQi = *iter;
                break;
            }
        }
    }

    // ����
    //mk = (int)floor((d0 - moonCalculate_.ZQ.lunarInfoList_[0] - 15) / 30.43685); if (mk < 11 && d0 >= moonCalculate_.ZQ.lunarInfoList_[2 * mk + 2]) mk++; //���������µ�����,(���j=13,d0���ᳬ����14������)
    //obj.XiZ = obb.XiZ[(int)((mk + 12) % 12)] + "��";

    // ����
    //oba.getHuiLi(d0, ob);

    // ����
    //obj.A = obj.B = obj.C = ""; obj.Fjia = 0;
    //oba.getDayName(ob, ob);   //����
    //obb.getDayName(ob, ob);   //ũ��

    return true;
}

void LunarDay::CalcJieQiTab()
{
    double y = julianDay_.GetYear();
    int j, thisJie = -1, jieQiPos = 0;
    JieQiInfo jieqiInfo;

    double v, qi = 0;
    commonDef::LunarInfo zq;
    int num = moonCalculate_.calcJieQi(floor((y - 2000) * 365.2422 + 180), zq, true);    // �������, ��"˪��"��ʼ

    for (j = 0; j < num; j++)    // ����
    {
        qi = zq.lunarInfoList_[j];
        v = qi_accurate2(qi);

        jieQiPos = (j + 24) % 24 + 20;      // �� obb.jqmc ��Ӧ, "˪��"����λ"����"�ľ���Ϊ 20
        if(jieQiPos >= 24)
            jieQiPos -= 24;

        if (((j + 24) % 24) % 2 == 1)           // ��
            jieqiInfo.JieOrQi = true;
        else
            jieqiInfo.JieOrQi = false;
       
        jieqiInfo.Name = commonDef::JIEQI_TABLE[jieQiPos];
        jieqiInfo.YueJian = commonDef::JIEQI_MAP_TABLE[jieQiPos];
        jieqiInfo.JDTime = JulianDay(v + commonDef::J2000).CreateDayInfo();

        jieqiInfo.HistoricalJDTime = JulianDay(qi + commonDef::J2000).CreateDayInfo();
        jieqiInfo.DifferentTime = (floor(v + 0.5) != qi ? true : false);
        jieqiInfo.DayDifference = (int)(floor(v + 0.5) - qi);

        jieqiTab_.push_back(jieqiInfo);
    }
}

/// <summary>
/// ָ��ĳ��, ���������������(��), ��һ��(��), ��һ��(��)��Ϣ, ���Ѽ������������ն�����
/// </summary>
/// <param name="ob"></param>
/// <returns>����ɹ����� true, ���򷵻� false </returns>
bool LunarDay::CalcJieQiInfo(JieQiObject& obj)
{            
    double y = julianDay_.GetYear();
    double m = julianDay_.GetMonth();
    double d = julianDay_.GetDay();
    unsigned int j = 0; 
    int thisJie = -1;
    JieQiInfo jieqiInfo;

    if (y >= 0)
    {
        double ymd = y * 10000.0 + m * 100.0 + d;     // ת����Ϊ��ֵ��ʾ������: �� 20090422
        for (j = jieqiTab_.size() - 1; j >= 0; j--)    // ������(���еĽ���������������С�������е�)
        {
            JulianDay jieqiJdTime(jieqiTab_[j].JDTime);
            double jieqiYear    = jieqiJdTime.GetYear();
            double jieqiMonth   = jieqiJdTime.GetMonth();
            double jieqiDay     = jieqiJdTime.GetDay();
            if (jieqiYear * 10000.0 + jieqiMonth * 100.0 + jieqiDay <= ymd)    // �ҵ������Ľ���
            {
                thisJie = j;
                break;
            }
        }
    }
    else
    {
        double ymd = y * 10000.0 - (99.0 - m) * 100.0 - (99.0 - d);
        for (j = 0; j < jieqiTab_.size(); j++)    // ˳����(���еĽ���������������С�������е�, ����Ϊ��ֵʱҲҪ�ϸ����)
        {
            JulianDay jieqiJdTime(jieqiTab_[j].JDTime);
            double jieqiYear = jieqiJdTime.GetYear();
            double jieqiMonth = jieqiJdTime.GetMonth();
            double jieqiDay = jieqiJdTime.GetDay();
            double jieqiYmd = jieqiYear * 10000.0 - (99.0 - jieqiMonth) * 100.0 - (99.0 - jieqiDay);
            if (jieqiYmd >= ymd)
            {
                if (jieqiYmd > ymd)
                    thisJie = j - 1;
                else
                    thisJie = j;
                break;
            }
        }
    }

    if (thisJie <= 0 && thisJie >= (int)jieqiTab_.size())
    {
        return false;
    }

    obj.ThisJieQi.JieOrQi = jieqiTab_[thisJie].JieOrQi;
    obj.ThisJieQi.Name = jieqiTab_[thisJie].Name;
    obj.ThisJieQi.YueJian = jieqiTab_[thisJie].YueJian;
    obj.ThisJieQi.JDTime = jieqiTab_[thisJie].JDTime;
    obj.ThisJieQi.HistoricalJDTime = jieqiTab_[thisJie].HistoricalJDTime;
    obj.ThisJieQi.DifferentTime = jieqiTab_[thisJie].DifferentTime;
    obj.ThisJieQi.DayDifference = jieqiTab_[thisJie].DayDifference;

    obj.PreviousJieQi.JieOrQi = jieqiTab_[thisJie - 1].JieOrQi;
    obj.PreviousJieQi.Name = jieqiTab_[thisJie - 1].Name;
    obj.PreviousJieQi.YueJian = jieqiTab_[thisJie - 1].YueJian;
    obj.PreviousJieQi.JDTime = jieqiTab_[thisJie - 1].JDTime;
    obj.PreviousJieQi.HistoricalJDTime = jieqiTab_[thisJie - 1].HistoricalJDTime;
    obj.PreviousJieQi.DifferentTime = jieqiTab_[thisJie - 1].DifferentTime;
    obj.PreviousJieQi.DayDifference = jieqiTab_[thisJie - 1].DayDifference;
   
    obj.NextJieQi.JieOrQi = jieqiTab_[thisJie + 1].JieOrQi;
    obj.NextJieQi.Name = jieqiTab_[thisJie + 1].Name;
    obj.NextJieQi.YueJian = jieqiTab_[thisJie + 1].YueJian;
    obj.NextJieQi.JDTime = jieqiTab_[thisJie + 1].JDTime;
    obj.NextJieQi.HistoricalJDTime = jieqiTab_[thisJie + 1].HistoricalJDTime;
    obj.NextJieQi.DifferentTime = jieqiTab_[thisJie + 1].DifferentTime;
    obj.NextJieQi.DayDifference = jieqiTab_[thisJie + 1].DayDifference;
    return true;
}

/// <summary>
/// ��������
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double LunarDay::qi_accurate(double W)
{
    double t = starCalendar_.S_aLon_t(W) * 36525;
    return t - julianDay_.deltatT2(t) + 8.0 / 24.0;    // ����
}

/// <summary>
/// ��˷����
/// </summary>
/// <param name="W"></param>
/// <returns></returns>
double LunarDay::so_accurate(double W)
{
    double t = starCalendar_.MS_aLon_t(W) * 36525;
    return t - julianDay_.deltatT2(t) + 8.0 / 24.0;    // ��˷
}

/// <summary>
/// �������㷨 2: 
/// </summary>
/// <param name="jd"></param>
/// <returns></returns>
double LunarDay::qi_accurate2(double jd)
{
    return qi_accurate(floor((jd + 293) / 365.2422 * 24) * M_PI / 12);     //����
}

/// <summary>
/// ��˷���㷨 2: 
/// </summary>
/// <param name="jd"></param>
/// <returns></returns>
double LunarDay::so_accurate2(double jd)
{
    return so_accurate(floor((jd + 8) / 29.5306) * M_PI * 2);     // ��˷
}

/// <summary>
/// ����ũ������
/// </summary>
bool LunarDay::FestivalInfo(FestivalObject& obj, const LunarDayObject& lunarDay)
{
    // ��ũ�����ڲ����ص�ڼ���
    chineseNum::CNUM_TYPE month = lunarDay.Lmc;
    chineseNum::CNUM_TYPE day   = lunarDay.Ldc;
    if (lunarDay.Lleap != true)
    {
#if 0
        for (i = 0; i < obb.LunarFeasts.Length; i++)     // C#: ���, ����ũ���ڼ���
        {
            if (d == obb.LunarFeasts[i].Lmc)
            {
                obj.A += obb.LunarFeasts[i].A;
                obj.B += obb.LunarFeasts[i].B;
                obj.C += obb.LunarFeasts[i].C;
                obj.Fjia = obb.LunarFeasts[i].Fjia;
            }
        }
#endif
    }

    if (lunarDay.Lmc2 == chineseNum::ZHENG_VAL)
    { 
        // ���һ��
        if (month == chineseNum::TWELVE_VAL && day == chineseNum::THIRTY_VAL && lunarDay.Ldn == 30) 
        { 
            obj.A.push_back(festival::CHU_XI_VAL); 
            obj.Fjia = 1; 
        }
        if (month == chineseNum::TWELVE_VAL && day == chineseNum::TWENTY_NINE_VAL && lunarDay.Ldn == 29) 
        { 
            obj.A.push_back(festival::CHU_XI_VAL); 
            obj.Fjia = 1; 
        }
        if (month == chineseNum::TWELVE_VAL && day == chineseNum::TWENTY_THREE_VAL) 
        { 
            obj.A.push_back(festival::XIAO_NIAN_VAL); 
        }
    }

#if 0
    if (lunarDay.Ljq)
    {
        for (i = 0; i < obb.JieQiFeasts.Length; i++)    // C#: �����Ƿ��зżٵĽ���
        {
            if (lunarDay.Ljq == obb.JieQiFeasts[i])               // C#: ƥ��
                break;
        }
        if (i < obb.JieQiFeasts.Length) { obj.A += lunarDay.Ljq + " "; obj.Fjia = 1; }
        else obj.B += lunarDay.Ljq + " ";
    }
#endif

    // ũ���ӽ�
    int w;
    if (lunarDay.cur_dz >= 0 && lunarDay.cur_dz < 81)
    { // ����
        w = (int)floor(lunarDay.cur_dz / 9) + 1;
        if (fmod(lunarDay.cur_dz, 9) == 0) 
            obj.B.push_back(commonDef::SHU_JIU[w]);
       // else 
       //     obj.C.push_back(commonDef::CNUM_TABLE[(int)(fmod(lunarDay.cur_dz, 9) + 1)]);
    }

    if (lunarDay.cur_xz > 20 && lunarDay.cur_xz <= 30 && lunarDay.Lday2.gan == gan::GENG_VAL) 
        obj.B.push_back(festival::CHU_FU_VAL);
    if (lunarDay.cur_xz > 30 && lunarDay.cur_xz <= 40 && lunarDay.Lday2.gan == gan::GENG_VAL) 
        obj.B.push_back(festival::ZHONG_FU_VAL);
    if (lunarDay.cur_lq > 0 && lunarDay.cur_lq <= 10 && lunarDay.Lday2.gan == gan::GENG_VAL) 
       obj.B.push_back(festival::MUO_FU_VAL);
    if (lunarDay.cur_mz > 0 && lunarDay.cur_mz <= 10 && lunarDay.Lday2.gan == gan::BING_VAL) 
       obj.B.push_back(festival::RU_MEI_VAL);
    if (lunarDay.cur_xs > 0 && lunarDay.cur_xs <= 12 && lunarDay.Lday2.zhi == zhi::WEI_VAL) 
       obj.B.push_back(festival::CHU_MEI_VAL);
    return true;
}


/// <summary>
/// ������ּ���, �����浽�ն��� ob ��
/// </summary>
/// <param name="jd">��������UT(J2000����)</param>
/// <param name="J">���ؾ���</param>
/// <param name="ob">�ն���</param>
/// <param name="southernHemisphere">�ϰ���ı�־</param>
bool LunarDay::BaZi(double J, double curTZ, BaziObject& obj, BaZiTypeS baziTypeS)
{
    int i = 0;
    double v = 0;
    double tmp = julianDay_.GregorianDayToJulianDay();
    double jd = tmp + curTZ / 24.0 - commonDef::J2000;
    double jd2 = jd + julianDay_.deltatT2(jd);      // ��ѧʱ
    double w = starCalendar_.S_aLon(jd2 / 36525.0, -1.0);  // �˿�̫���ӻƾ�
    double k = floor((w / commonDef::pi2 * 360.0 + 45.0 + 15.0 * 360.0) / 30.0);   // 1984����������Ľ�����(��������)
    jd += starCalendar_.shiCha2(jd2 / 36525.0) - J / M_PI / 2.0;        // ������̫��ʱ(ʹ�õ;����㷨����ʱ��)
    JulianDay zTime(jd + commonDef::J2000);
    obj.bz_zty = zTime.CreateDayInfo();

    jd += 13.0 / 24.0;   // תΪǰһ��23������(ԭjdΪ��������12������)   // C#: ע����������
    double D = floor(jd), SC = floor((jd - D) * 12.0);   // ������ʱ��

    v = floor(k / 12.0 + 6000000.0); 
    obj.bazi.year_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);
    
    v = k + 2.0 + 60000000.0; 
    obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);

    // C#: �����Ĵ����, �����ϰ������(�����²�ͬ)
    switch (baziTypeS)
    {
        case TianChongDiChong:
            obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 4), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        case TianKeDiChong:
            obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 6), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        case TianTongDiChong:
            obj.bazi.month_ =  commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 0), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        default:
            break;
    }

    v = D - 6.0 + 9000000.0; 
    obj.bazi.day_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);

    v = (D - 1.0) * 12.0 + 90000000.0 + SC; 
    obj.bazi.time_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);

    v -= SC;
    obj.bz_JS.clear();    // ȫ���ʱ��
    commonDef::GANZHI c;
    for (i = 0; i < 13; i++)
    { 
        // һ���а�����13����ʱ
        c = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + i), 10)], commonDef::ZHI_TABLE[(int)fmod((v + i), 12)]); // ��ʱ���İ���
            
        if (SC == i)
        {
            obj.bazi.time_ = c;
        } 
        obj.bz_JS.push_back(c);
    }

    return true;
}

/// <summary>
/// ������ּ���(��ͨ����, ��ת��Ϊ������̫��ʱ), �����浽�ն��� ob ��
/// </summary>
/// <param name="jd">��������UT(J2000����)</param>
/// <param name="J">���ؾ���</param>
/// <param name="obj">�ն���</param>
/// <param name="southernHemisphere">�ϰ���ı�־</param>
bool LunarDay::BaZiNormal(double J, double curTZ, BaziObject& obj, BaZiTypeS baziTypeS)
{
    int i = 0;;
    double v = 0.0;
    double tmp = julianDay_.GregorianDayToJulianDay();
    double jd = tmp + curTZ / 24.0 - commonDef::J2000;
    double jd2 = jd + julianDay_.deltatT2(jd);      // ��ѧʱ
    double w = starCalendar_.S_aLon(jd2 / 36525, -1);  // �˿�̫���ӻƾ�
    double k = floor((w / commonDef::pi2 * 360 + 45 + 15 * 360) / 30);   // 1984����������Ľ�����(��������)

    //----------------------------------------------------------------------------------------------
    // C#: ע: �������д������ mingLiBaZi �����еĴ��벻ͬ, ���ಿ�ֶ�����ͬ��
    //----------------------------------------------------------------------------------------------
    jd += 0 - J / M_PI / 2;     // ����������UT(J2000����), ת��Ϊ����ʱ��, ���ؿ�����̫����ƽ̫��ʱ֮���ʱ��
    JulianDay zTime(jd + commonDef::J2000);
    obj.bz_pty = zTime.CreateDayInfo();   // ����ƽ̫��ʱ

    jd += 13.0 / 24.0;   // תΪǰһ��23������(ԭjdΪ��������12������)   // C#: ע����������
    double D = floor(jd), SC = floor((jd - D) * 12);   // ������ʱ��

    v = floor(k / 12.0 + 6000000.0); 
    obj.bazi.year_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);
    
    v = k + 2.0 + 60000000.0; 
    obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);


    // C#: �����Ĵ����, �����ϰ������(�����²�ͬ)
    switch (baziTypeS)
    {
        case TianChongDiChong:
            obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 4), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        case TianKeDiChong:
            obj.bazi.month_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 6), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        case TianTongDiChong:
            obj.bazi.month_ =  commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + 0), 10)], commonDef::ZHI_TABLE[(int)fmod((v + 6), 12)]);
            break;
        default:
            break;
    }

    v = D - 6.0 + 9000000.0; 
    obj.bazi.day_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);

    v = (D - 1.0) * 12.0 + 90000000.0 + SC; 
    obj.bazi.time_ = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod(v, 10)], commonDef::ZHI_TABLE[(int)fmod(v, 12)]);

    v -= SC;
    obj.bz_JS.clear();    // ȫ���ʱ��
    commonDef::GANZHI c;
    for (i = 0; i < 13; i++)
    { 
        // һ���а�����13����ʱ
        c = commonDef::GANZHI(commonDef::GAN_TABLE[(int)fmod((v + i), 10)], commonDef::ZHI_TABLE[(int)fmod((v + i), 12)]); // ��ʱ���İ���
            
        if (SC == i)
        {
            obj.bazi.time_ = c;
        } 
        obj.bz_JS.push_back(c);
    }

    return true;
}

bool LunarDayBuilder::Build(LunarDayObject& obj, double year, double month, double day,
                            double hour, double minute, double second)
{
    LunarDay lunarDay(year, month, day, hour, minute, second);
    return lunarDay.DayCalculate(obj);
}
bool LunarJieqiDayBuilder::Build(JieQiObject& obj, double year, double month, double day,
                            double hour, double minute, double second)
{
    LunarDay lunarDay(year, month, day, hour, minute, second);
    return lunarDay.CalcJieQiInfo(obj);
}

bool FestivalDayBuilder::Build(FestivalObject& obj, double year, double month, double day,
                            double hour, double minute, double second)
{
    LunarDay lunarDay(year, month, day, hour, minute, second);
    LunarDayObject tmpLunarDay;
    lunarDay.DayCalculate(tmpLunarDay);
    return lunarDay.FestivalInfo(obj, tmpLunarDay);
}

bool BaZiBuilder::Build(BaziObject& obj, double year, double month, double day,
                            double hour, double minute, double second)
{
    LunarDay lunarDay(year, month, day, hour, minute, second);
    lunarDay.BaZi(commonDef::Angle2Rad(-116, 28, 0), -8, obj, Normal);
    return true;
}



}  // namespace dateTime
}  // namespace YiEngine
