#ifndef YIENGINE_COMMON_COORDINATE_H
#define YIENGINE_COMMON_COORDINATE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <YiEngine/DateTime/IDateTime.h>
#include "MoonCalculate.h"
#include "JulianDay.h"
#include <YiEngine/DateTime/DataTranslator.hpp>
#include <YiEngine/DateTime/DateTimeCommonDef.h>
//#include "LunarDay.h"

namespace yiEngine
{
namespace dateTime
{

/// <summary>
/// 天文单位长度(千米)
/// </summary>
const double cs_AU = 1.49597870691e8;          // 天文单位长度(千米)

/// <summary>
/// 地球赤道半径(千米)
/// </summary>
const double cs_rEar = 6378.1366;              // 地球赤道半径(千米)

class Coordinate
{
public:
    void llrConv(double JW[], double E);
    void llr2xyz(double J, double W, double R, double z[]);
    void xyz2llr(double x, double y, double z, double q[]);
    void nutation(double t);
    double nutationLon(double t);
    double hcjj(double t);
    double j1_j2(double J1, double W1, double J2, double W2);
    double gst(double T, double dt);
    double gxc_sunLon(double t);
    double gxc_sunLat(double t);
    double gxc_moonLon(double t);
    double gxc_moonLat(double t);
    double AR(double ho);
    double AR2(double h);
    void parallax(double z[], double H, double fa, double high);
    void line_earth(double J1, double W1, double R1, double J2, double W2, double R2);
public:
        /// <summary>
        /// 黄经章动
        /// </summary>
        double dL;

        /// <summary>
        /// 交角章动
        /// </summary>
        double dE;

        /// <summary>
        /// 保存空间两点连线与地球的交点: 经(?)
        /// </summary>
        double le_J;

        /// <summary>
        /// 保存空间两点连线与地球的交点: 纬(?)
        /// </summary>
        double le_W;

        /// <summary>
        /// (?)
        /// </summary>
        double le_R1;
};

}  // namespace dateTime
}  // namespace YiEngine
#endif
