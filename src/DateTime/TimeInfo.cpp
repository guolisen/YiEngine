

#include "TimeInfo.h"


namespace yiEngine
{
namespace dateTime
{




/// <summary>
/// 计算 sun_moon 类的成员。参数：T是力学时,站点经度longitude,纬度latitude,海拔high(千米)
/// </summary>
/// <param name="T">力学时</param>
/// <param name="longitude">站点经度</param>
/// <param name="latitude">站点纬度</param>
/// <param name="high">海拔</param>
TimeInfo TimeCalculator::Calculator(double rawTimeTick, double longitude, double latitude, double high)
{
    double T =  (rawTimeTick * 1000.0) / 86400000.0 - 10957.5;
    T += julianDay_.deltatT2(T);

    //基本参数计算
    timeInfo_.T = T; 
    timeInfo_.longitude = longitude; 
    timeInfo_.latitude  = latitude;
    timeInfo_.dt = julianDay_.deltatT2(T); //TD-UT
    timeInfo_.jd = T - timeInfo_.dt;    //UT
    T /= 36525; coordinate_.nutation(T);
    timeInfo_.dL = coordinate_.dL;   //黄经章
    timeInfo_.dE = coordinate_.dE;   //交角章动
    timeInfo_.E = coordinate_.hcjj(T) + timeInfo_.dE; //真黄赤交角
    timeInfo_.gst = coordinate_.gst(timeInfo_.jd, timeInfo_.dt) + timeInfo_.dL * cos(timeInfo_.E); //真恒星时(不考虑非多项式部分)
    double z[4] = {0};

    //=======月亮========
    //月亮黄道坐标
    starCalendar_.M_coord(T, z, -1.0, -1.0, -1.0); //月球坐标
    z[0] = commonDef::rad2mrad(z[0] + coordinate_.gxc_moonLon(T) + timeInfo_.dL); z[1] += coordinate_.gxc_moonLat(T);  //补上月球光行差及章动
    timeInfo_.mHJ = z[0]; timeInfo_.mHW = z[1]; timeInfo_.mR = z[2]; //月球视黄经,视黄纬,地月质心距

    //月球赤道坐标
    coordinate_.llrConv(z, timeInfo_.E); //转为赤道坐标
    timeInfo_.mCJ = z[0]; timeInfo_.mCW = z[1]; //月球视赤经,月球赤纬

    //月亮时角计算
    timeInfo_.mShiJ = commonDef::rad2mrad(timeInfo_.gst - longitude - z[0]); //得到此刻天体时角
    if (timeInfo_.mShiJ > M_PI) timeInfo_.mShiJ -= commonDef::pi2;

    //修正了视差的赤道坐标
    coordinate_.parallax(z, timeInfo_.mShiJ, latitude, high); //视差修正
    timeInfo_.mCJ2 = z[0]; timeInfo_.mCW2 = z[1]; timeInfo_.mR2 = z[2];

    //月亮时角坐标
    z[0] += M_PI / 2.0 - timeInfo_.gst + longitude;  //转到相对于地平赤道分点的赤道坐标(时角坐标)

    //月亮地平坐标
    coordinate_.llrConv(z, M_PI / 2.0 - latitude);    //转到地平坐标(只改经纬度)
    z[0] = commonDef::rad2mrad(M_PI / 2.0 - z[0]);
    timeInfo_.mDJ = z[0]; timeInfo_.mDW = z[1]; //方位角,高度角
    if (z[1] > 0) z[1] += coordinate_.AR2(z[1]); //大气折射修正
    timeInfo_.mPJ = z[0]; timeInfo_.mPW = z[1]; //方位角,高度角

    //=======太阳========
    //太阳黄道坐标
    starCalendar_.E_coord(T, z, -1, -1, -1);   //地球坐标
    z[0] = commonDef::rad2mrad(z[0] + M_PI + coordinate_.gxc_sunLon(T) + timeInfo_.dL);  //补上太阳光行差及章动
    z[1] = -z[1] + coordinate_.gxc_sunLat(T); //z数组为太阳地心黄道视坐标
    timeInfo_.sHJ = z[0]; timeInfo_.sHW = z[1]; timeInfo_.sR = z[2]; //太阳视黄经,视黄纬,日地质心距

    //太阳赤道坐标
    coordinate_.llrConv(z, timeInfo_.E); //转为赤道坐标
    timeInfo_.sCJ = z[0]; timeInfo_.sCW = z[1]; //太阳视赤经,视赤纬

    //太阳时角计算
    timeInfo_.sShiJ = commonDef::rad2mrad(timeInfo_.gst - longitude - z[0]); //得到此刻天体时角
    if (timeInfo_.sShiJ > M_PI) timeInfo_.sShiJ -= commonDef::pi2;

    //修正了视差的赤道坐标
    coordinate_.parallax(z, timeInfo_.sShiJ, latitude, high); //视差修正
    timeInfo_.sCJ2 = z[0]; timeInfo_.sCW2 = z[1]; timeInfo_.sR2 = z[2];

    //太阳时角坐标
    z[0] += M_PI / 2.0 - timeInfo_.gst + longitude;  //转到相对于地平赤道分点的赤道坐标

    //太阳地平坐标
    coordinate_.llrConv(z, M_PI / 2.0 - latitude);
    z[0] = commonDef::rad2mrad(M_PI / 2.0 - z[0]);
    //z[1] -= 8.794/rad/z[2]*Math.cos(z[1]); //直接在地平坐标中视差修正(这里把地球看为球形,精度比coordinate_.parallax()稍差一些)
    timeInfo_.sDJ = z[0]; timeInfo_.sDW = z[1]; //方位角,高度角

    if (z[1] > 0) z[1] += coordinate_.AR2(z[1]); //大气折射修正
    timeInfo_.sPJ = z[0]; timeInfo_.sPW = z[1]; //方位角,高度角

    //=======其它========
    //时差计算
    double t = T / 10; double t2 = t * t, t3 = t2 * t, t4 = t3 * t, t5 = t4 * t;
    double Lon = (1753469512.0 + 6283319653318.0 * t + 529674.0 * t2 + 432.0 * t3 - 1124.0 * t4 - 9.0 * t5 + 630.0 * cos(6.0 + 3.0 * t)) / 1000000000.0 + M_PI - 20.5 / commonDef::RAD; //修正了光行差的太阳平黄经
    Lon = commonDef::rad2mrad(Lon - (timeInfo_.sCJ - timeInfo_.dL * cos(timeInfo_.E))); //(修正了光行差的平黄经)-(不含dL*cos(E)的视赤经)
    if (Lon > M_PI) Lon -= commonDef::pi2; //得到时差,单位是弧度
    timeInfo_.sc = Lon / commonDef::pi2;   //时差(单位:日)

    //真太阳与平太阳
    timeInfo_.pty = timeInfo_.jd - longitude / commonDef::pi2;  //平太阳时
    timeInfo_.zty = timeInfo_.jd - longitude / commonDef::pi2 + timeInfo_.sc; //真太阳时

    //视半径
    //timeInfo_.mRad = starCalendar_.moonRad(timeInfo_.mR,timeInfo_.mDW);  //月亮视半径(角秒)
    timeInfo_.mRad = 358473400.0 / timeInfo_.mR2; //月亮视半径(角秒)
    timeInfo_.sRad = 959.63 / timeInfo_.sR2; //太阳视半径(角秒)
    timeInfo_.e_mRad = 358473400.0 / timeInfo_.mR; //月亮地心视半径(角秒)
    timeInfo_.eShadow = (commonDef::cs_rEarA / timeInfo_.mR * commonDef::RAD - (959.63 - 8.794) / timeInfo_.sR) * 51.0 / 50.0; //地本影在月球向径处的半径(角秒),式中51/50是大气厚度补偿
    timeInfo_.eShadow2 = (commonDef::cs_rEarA / timeInfo_.mR * commonDef::RAD + (959.63 + 8.794) / timeInfo_.sR) * 51.0 / 50.0; //地半影在月球向径处的半径(角秒),式中51/50是大气厚度补偿
    timeInfo_.mIll = starCalendar_.moonIll(T); //月亮被照面比例

    //中心食计算
    if (abs(commonDef::rad2rrad(timeInfo_.mCJ - timeInfo_.sCJ)) < 50 / 180 * M_PI)
    {
        coordinate_.line_earth(timeInfo_.mCJ, timeInfo_.mCW, timeInfo_.mR, timeInfo_.sCJ, timeInfo_.sCW, timeInfo_.sR * commonDef::cs_AU);
        timeInfo_.zx_J = commonDef::rad2rrad(timeInfo_.gst - coordinate_.le_J);
        timeInfo_.zx_W = coordinate_.le_W; //无解返回值是100
    }
    else 
        timeInfo_.zx_J = timeInfo_.zx_W = 100;

    return timeInfo_;
}


}  // namespace dateTime
}  // namespace YiEngine
