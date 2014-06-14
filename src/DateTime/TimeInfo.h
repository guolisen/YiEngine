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
//基本参数

/// <summary>
/// 力学时
/// </summary>
double T;

/// <summary>
/// 站点经度
/// </summary>
double longitude;

/// <summary>
/// 站点纬度
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
/// 黄经章
/// </summary>
double dL;

/// <summary>
/// 交角章动
/// </summary>
double dE;

/// <summary>
/// 真黄赤交角
/// </summary>
double E;

/// <summary>
/// 真恒星时(不考虑非多项式部分)
/// </summary>
double gst;


//月球参数

/// <summary>
/// 月球视黄经
/// </summary>
double mHJ;

/// <summary>
/// 月球视黄纬
/// </summary>
double mHW;

/// <summary>
/// 地月质心距
/// </summary>
double mR;

/// <summary>
/// 月球视赤经
/// </summary>
double mCJ;

/// <summary>
/// 月球赤纬
/// </summary>
double mCW;

/// <summary>
/// 此时的天体时角
/// </summary>
double mShiJ;

/// <summary>
/// 修正了视差的赤道坐标: 月球视赤经
/// </summary>
double mCJ2;

/// <summary>
/// 修正了视差的赤道坐标: 月球赤纬
/// </summary>
double mCW2;

/// <summary>
/// 修正了视差的赤道坐标: 地月质心距
/// </summary>
double mR2;

/// <summary>
/// 方位角
/// </summary>
double mDJ;

/// <summary>
/// 高度角
/// </summary>
double mDW;

/// <summary>
/// 方位角(大气折射修正后)
/// </summary>
double mPJ;

/// <summary>
/// 高度角(大气折射修正后)
/// </summary>
double mPW;


///太阳参数

/// <summary>
/// 太阳视黄经
/// </summary>
double sHJ;

/// <summary>
/// 太阳视黄纬
/// </summary>
double sHW;

/// <summary>
/// 日地质心距
/// </summary>
double sR;

/// <summary>
/// 太阳视赤经
/// </summary>
double sCJ;

/// <summary>
/// 太阳视赤纬
/// </summary>
double sCW;

/// <summary>
/// 太阳时角
/// </summary>
double sShiJ;

/// <summary>
/// 修正了视差的赤道坐标: 太阳视赤经
/// </summary>
double sCJ2;

/// <summary>
/// 修正了视差的赤道坐标: 太阳视赤纬
/// </summary>
double sCW2;

/// <summary>
/// 修正了视差的赤道坐标: 日地质心距
/// </summary>
double sR2;

/// <summary>
/// 方位角
/// </summary>
double sDJ;

/// <summary>
/// 高度角
/// </summary>
double sDW;

/// <summary>
/// 方位角(大气折射修正后)
/// </summary>
double sPJ;

/// <summary>
/// 高度角(大气折射修正后)
/// </summary>
double sPW;



///其他参数

/// <summary>
/// 时差(单位:日)
/// </summary>
double sc;

/// <summary>
/// 平太阳时
/// </summary>
double pty;

/// <summary>
/// 真太阳时
/// </summary>
double zty;

/// <summary>
/// 月亮视半径(角秒)
/// </summary>
double mRad;

/// <summary>
/// 太阳视半径(角秒)
/// </summary>
double sRad;

/// <summary>
/// 月亮地心视半径(角秒)
/// </summary>
double e_mRad;

/// <summary>
/// 地本影在月球向径处的半径(角秒)
/// </summary>
double eShadow;

/// <summary>
/// 地本影在月球向径处的半径(角秒)
/// </summary>
double eShadow2;

/// <summary>
/// 月亮被照面比例
/// </summary>
double mIll;

/// <summary>
/// 中心食计算: 经
/// </summary>
double zx_J;

/// <summary>
/// 中心食计算: 纬
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