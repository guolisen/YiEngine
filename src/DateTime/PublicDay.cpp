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

    // ���������ʼ��
    JulianDay jd(tmpYear, tmpMonth, 1, 12.0, 0.0, 0.0);
    m0 = floor(jd.GregorianDayToJulianDay()) - commonDef::J2000;  // ����ĳ�������,����

    if(moonCalculate_.ZQ.lunarInfoList_.empty() || m0 < moonCalculate_.ZQ.lunarInfoList_[0] || m0 >= moonCalculate_.ZQ.lunarInfoList_[24])
        moonCalculate_.calcY(m0);

    double nextMonth = tmpMonth + 1;
    if (nextMonth > 12) 
    { 
        tmpYear++; 
        tmpMonth = 1; 
    }     // C#: ����·ݴ��� 12, ������ + 1, ����ȡ 1

    JulianDay jdNext(tmpYear, nextMonth, 1, 12.0, 0.0, 0.0);

    mn = jdNext.GregorianDayToJulianDay() - commonDef::J2000 - m0; // ��������(����)

    double w0 = fmod((m0 + commonDef::J2000 + 1), 7); //���µ�һ�������

    obj.d0 = julianDay_.GregorianDayToJulianDay() - commonDef::J2000;   // ������,����ʱ12:00
    obj.di = julianDay_.GetDay();         // ��������������
    obj.y = (int)julianDay_.GetYear();         // ������
    obj.m = (int)julianDay_.GetMonth();         // ������
    obj.dn = mn;       // ����������
    obj.week0 = w0;     // ���׵�����
    obj.week = fmod((w0 + obj.di), 7);     // ��ǰ�յ�����
    obj.weeki = floor((w0 + obj.di) / 7);    // �������ڵ������
    obj.weekN = floor((w0 + mn - 1) / 7) + 1;    // ���µ�������
    obj.d = (int)julianDay_.GetDay();   //����������

    double mk = (int)floor((obj.d0 - moonCalculate_.ZQ.lunarInfoList_[0] - 15) / 30.43685); 
    if (mk < 11 && obj.d0 >= moonCalculate_.ZQ.lunarInfoList_[2 * (unsigned int)mk + 2]) 
        mk++; //���������µ�����,(���j=13,ob.d0���ᳬ����14������)
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
