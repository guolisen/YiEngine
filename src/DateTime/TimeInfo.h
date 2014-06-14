#ifndef YIENGINE_COMMON_TIMEINFO_H
#define YIENGINE_COMMON_TIMEINFO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <boost/shared_ptr.hpp>

#include "JulianDay.h"
#include "MoonCalculate.h"
#include "StarCalendar.h"
#include "Coordinate.h"

namespace yiEngine
{
namespace dateTime
{

struct TimeInfo
{
//��������

/// <summary>
/// ��ѧʱ
/// </summary>
double T;

/// <summary>
/// վ�㾭��
/// </summary>
double longitude;

/// <summary>
/// վ��γ��
/// </summary>
double latitude;

/// <summary>
/// TD-UT
/// </summary>
double dt;

/// <summary>
/// UT
/// </summary>
double jd;

/// <summary>
/// �ƾ���
/// </summary>
double dL;

/// <summary>
/// �����¶�
/// </summary>
double dE;

/// <summary>
/// ��Ƴཻ��
/// </summary>
double E;

/// <summary>
/// �����ʱ(�����ǷǶ���ʽ����)
/// </summary>
double gst;


//�������

/// <summary>
/// �����ӻƾ�
/// </summary>
double mHJ;

/// <summary>
/// �����ӻ�γ
/// </summary>
double mHW;

/// <summary>
/// �������ľ�
/// </summary>
double mR;

/// <summary>
/// �����ӳྭ
/// </summary>
double mCJ;

/// <summary>
/// �����γ
/// </summary>
double mCW;

/// <summary>
/// ��ʱ������ʱ��
/// </summary>
double mShiJ;

/// <summary>
/// �������Ӳ�ĳ������: �����ӳྭ
/// </summary>
double mCJ2;

/// <summary>
/// �������Ӳ�ĳ������: �����γ
/// </summary>
double mCW2;

/// <summary>
/// �������Ӳ�ĳ������: �������ľ�
/// </summary>
double mR2;

/// <summary>
/// ��λ��
/// </summary>
double mDJ;

/// <summary>
/// �߶Ƚ�
/// </summary>
double mDW;

/// <summary>
/// ��λ��(��������������)
/// </summary>
double mPJ;

/// <summary>
/// �߶Ƚ�(��������������)
/// </summary>
double mPW;


///̫������

/// <summary>
/// ̫���ӻƾ�
/// </summary>
double sHJ;

/// <summary>
/// ̫���ӻ�γ
/// </summary>
double sHW;

/// <summary>
/// �յ����ľ�
/// </summary>
double sR;

/// <summary>
/// ̫���ӳྭ
/// </summary>
double sCJ;

/// <summary>
/// ̫���ӳ�γ
/// </summary>
double sCW;

/// <summary>
/// ̫��ʱ��
/// </summary>
double sShiJ;

/// <summary>
/// �������Ӳ�ĳ������: ̫���ӳྭ
/// </summary>
double sCJ2;

/// <summary>
/// �������Ӳ�ĳ������: ̫���ӳ�γ
/// </summary>
double sCW2;

/// <summary>
/// �������Ӳ�ĳ������: �յ����ľ�
/// </summary>
double sR2;

/// <summary>
/// ��λ��
/// </summary>
double sDJ;

/// <summary>
/// �߶Ƚ�
/// </summary>
double sDW;

/// <summary>
/// ��λ��(��������������)
/// </summary>
double sPJ;

/// <summary>
/// �߶Ƚ�(��������������)
/// </summary>
double sPW;



///��������

/// <summary>
/// ʱ��(��λ:��)
/// </summary>
double sc;

/// <summary>
/// ƽ̫��ʱ
/// </summary>
double pty;

/// <summary>
/// ��̫��ʱ
/// </summary>
double zty;

/// <summary>
/// �����Ӱ뾶(����)
/// </summary>
double mRad;

/// <summary>
/// ̫���Ӱ뾶(����)
/// </summary>
double sRad;

/// <summary>
/// ���������Ӱ뾶(����)
/// </summary>
double e_mRad;

/// <summary>
/// �ر�Ӱ�������򾶴��İ뾶(����)
/// </summary>
double eShadow;

/// <summary>
/// �ر�Ӱ�������򾶴��İ뾶(����)
/// </summary>
double eShadow2;

/// <summary>
/// �������������
/// </summary>
double mIll;

/// <summary>
/// ����ʳ����: ��
/// </summary>
double zx_J;

/// <summary>
/// ����ʳ����: γ
/// </summary>
double zx_W;
};

class TimeCalculator
{
public:
    TimeInfo Calculator(double rawTimeTick, double longitude, double latitude, double high);

protected:
    TimeInfo  timeInfo_;
    JulianDay julianDay_;
    MoonCalculate moonCalculate_;
    StarCalendar  starCalendar_;
    Coordinate    coordinate_;
};


}  // namespace dateTime
}  // namespace YiEngine


#endif