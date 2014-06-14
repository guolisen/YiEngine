#ifndef YIENGINE_DATETIME_STAR_CALEN_H
#define YIENGINE_DATETIME_STAR_CALEN_H
#include <vector>
#include "Coordinate.h"

namespace yiEngine
{
namespace dateTime
{

namespace XL{
enum E_TYPE 
{
    EL_TYPE,
    EB_TYPE,
    ER_TYPE
};
}
namespace XL{
enum M_TYPE 
{
    ML_TYPE,
    MB_TYPE,
    MR_TYPE
};
}

class StarCalendar
{
public:
    StarCalendar(void);
    virtual ~StarCalendar(void);
public:
    void E_coord(double t, double re[4], double n1, double n2, double n3);
    void M_coord(double t, double re[4], double n1, double n2, double n3);
    double E_Lon(double t, double n);
    double M_Lon(double t, double n);
    double E_v(double t);
    double M_v(double t);
    double MS_aLon(double t, double Mn, double Sn);
    double S_aLon(double t, double n);
    double E_Lon_t(double W);
    double M_Lon_t(double W);
    double MS_aLon_t(double W);
    double S_aLon_t(double W);
    double MS_aLon_t2(double W);
    double S_aLon_t2(double W);

    double moonIll(double t);
    double moonRad(double r, double h);

    double shiCha(double t);
    double shiCha2(double t);
protected:
    double Enn(std::vector<double> ob[], int lineNum, XL::E_TYPE type, double t, double n);
    double Mnn(std::vector<double> ob[], int lineNum, XL::M_TYPE type, double t, double n);

protected:
    std::vector<double> EL_[6];
    std::vector<double> EB_[3];
    std::vector<double> ER_[6];

    std::vector<double> ML_[3];
    std::vector<double> MB_[2];
    std::vector<double> MR_[3];

    Coordinate coordinate_;
};

}  // namespace Common
}  // namespace YiEngine

#endif