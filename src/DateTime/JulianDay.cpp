#include <math.h>
#include "JulianDay.h"

namespace yiEngine
{
namespace dateTime
{
/// TD - UT1 �����
static double dts[] = { 
    -4000,108371.7,-13036.80,392.000, 0.0000, -500, 17201.0,  -627.82, 16.170,-0.3413,
    -150, 12200.6,  -346.41,  5.403,-0.1593,  150,  9113.8,  -328.13, -1.647, 0.0377,
    500,  5707.5,  -391.41,  0.915, 0.3145,  900,  2203.4,  -283.45, 13.034,-0.1778,
    1300,   490.1,   -57.35,  2.085,-0.0072, 1600,   120.0,    -9.81, -1.532, 0.1403,
    1700,    10.2,    -0.91,  0.510,-0.0370, 1800,    13.4,    -0.72,  0.202,-0.0193,
    1830,     7.8,    -1.81,  0.416,-0.0247, 1860,     8.3,    -0.13, -0.406, 0.0292,
    1880,    -5.4,     0.32, -0.183, 0.0173, 1900,    -2.3,     2.06,  0.169,-0.0135,
    1920,    21.2,     1.69, -0.304, 0.0167, 1940,    24.2,     1.22, -0.064, 0.0031,
    1960,    33.2,     0.51,  0.231,-0.0109, 1980,    51.0,     1.29, -0.026, 0.0032,
    2000,    63.87,    0.1,   0,     0,      2005
};

JulianDay::JulianDay(): year_(2000), month_(1), day_(1),
    hour_(12), minute_(0), second_(0)
{

}
JulianDay::JulianDay(double jd)
{
    SetFromJD(jd);
}
JulianDay::JulianDay(double year, double month, double day, 
                       double hour, double minute, double second): 
                       year_(year), month_(month), day_(day),
                       hour_(hour), minute_(minute), second_(second)
{
                       
}

/// <summary>
/// ������������
/// </summary>
/// <param name="y"></param>
/// <param name="jsd"></param>
/// <returns></returns>
double JulianDay::deltatExt(double y, double jsd)
{
    double dy = (y - 1820) / 100;
    return -20 + jsd * dy * dy;
}

/// <summary>
/// ��������ʱ��ԭ��ʱ֮��,������
/// </summary>
/// <param name="y">��</param>
/// <returns></returns>
double JulianDay::deltatT(double y)
{ 
    if (y >= 2005)
    {
        //sd ��2005��֮���꣨һֵ��y1�꣩���ٶȹ��ơ�
        //jsd ��y1��֮��ļ��ٶȹ��ơ���ʿ������jsd=31,NASA��վjsd=32,skmap��jsd=29
        double y1 = 2014, sd = 0.4, jsd = 31;
        if (y <= y1) 
            return 64.7 + (y - 2005) * sd;    //ֱ������
        double v = deltatExt(y, jsd);        //������������
        double dv = deltatExt(y1, jsd) - (64.7 + (y1 - 2005) * sd); //y1��Ķ���������ֱ�����ƵĲ�
        if (y < y1 + 100) 
            v -= dv * (y1 + 100 - y) / 100;
        return v;
    }
    int i;
    double* d = dts;
    for (i = 0; i < 96; i += 5) 
        if (y < d[i + 5]) 
            break;
    double t1 = (y - d[i]) / (d[i + 5] - d[i]) * 10, t2 = t1 * t1, t3 = t2 * t1;
    return d[i + 1] + d[i + 2] * t1 + d[i + 3] * t2 + d[i + 4] * t3;
}

/// <summary>
/// ����������(J2000����),����TD-UT(��λ:��)
/// </summary>
/// <param name="t">J2000�����������</param>
/// <returns></returns>
double JulianDay::deltatT2(double t)
{
    return deltatT(t / 365.2425 + 2000) / 86400.0;
}

/// <summary>
/// ����ת������
/// </summary>
/// <param name="y">��</param>
/// <param name="m">��</param>
/// <param name="d">��</param>
/// <returns></returns>
double JulianDay::GD_To_JD(double y, double m, double d)
{
    double n = 0, G = 0;
    if (y * 372 + m * 31 + floor(d) >= 588829) 
        G = 1;   //�ж��Ƿ�Ϊ�����������1582*372+10*31+15
    if (m <= 2) { m += 12; y--; }
    if (G != 0)
    {
        n = floor(y / 100); 
        n = 2 - n + floor(n / 4);
    }    //�Ӱ�����
    return floor(365.25 * (y + 4716) + 0.01) + floor(30.6001 * (m + 1)) + d + n - 1524.5;
}

/// <summary>
/// ����ת������
/// </summary>
/// <returns></returns>
double JulianDay::GregorianDayToJulianDay()
{
    return GD_To_JD(year_, month_, day_ + ((second_ / 60 + minute_) / 60 + hour_) / 24);
}

/// <summary>
/// ��������ת����
/// </summary>
/// <param name="jd">������</param>
void JulianDay::SetFromJD(double jd)
{ 
    jd += 0.5;
    double A = floor(jd); 
    double F = jd - A;
    double D = 0;  //ȡ����������������A��С������F

    if (A >= 2299161)
    {
        D = floor((A - 1867216.25) / 36524.25); 
        A += 1 + D - floor(D / 4);
    }
    A += 1524;     //��ǰ��4����2����
    year_ = floor((A - 122.1) / 365.25);    //��
    D = A - floor(365.25 * year_);     //ȥ��������������������
    month_ = floor(D / 30.6001);           //����
    day_ = D - floor(month_ * 30.6001);    //ȥ��������������������
    year_ -= 4716; month_--;
    if (month_ > 12) month_ -= 12;
    if (month_ <= 2) year_++;

    //�յ�С��תΪʱ����
    F *= 24; hour_ = floor(F); F -= hour_;
    F *= 60; minute_ = floor(F); F -= minute_;
    F *= 60; second_ = F;
}

/// <summary>
/// ��y��m�µĵ�n������w����������
/// </summary>
/// <param name="y">��</param>
/// <param name="m">��</param>
/// <param name="n"></param>
/// <param name="w">����w</param>
/// <returns></returns>
double JulianDay::nnweek(double y, double m, double n, double w)
{
    double jd = GD_To_JD(y, m, 1.5); //����������
    double w0 = fmod(jd + 1.0, 7.0);       //���׵�����
    double r = jd - w0 + 7 * n + w;    //jd-w0+7*n�Ǻ�n������0,�����±��µ�һ�е�������(����������һ��)����w��Ϊ��n������w
    if (w >= w0) r -= 7; //��1������w���������ϸ���,��ɶ���1��,���Կ��Ǽ�1��
    if (n == 5)
    {
        m++; if (m > 12) { m = 1; y++; }  //�¸���
        if (r >= GD_To_JD(y, m, 1.5)) r -= 7; //r�ܵ��¸������1��
    }
    return r;
}

/// <summary>
/// ���ڼ���
/// </summary>
/// <param name="jd"></param>
/// <returns></returns>
double JulianDay::getWeek(double jd)
{
    return fmod(jd + 1.5, 7.0);
}


}  // namespace dateTime
}  // namespace YiEngine

