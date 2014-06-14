#ifndef YIENGINE_DATETIME_MOONCALC_H
#define YIENGINE_DATETIME_MOONCALC_H
#include <string>
#include <map>
#include <YiEngine/DateTime/DateTimeCommonDef.h>
//#include "LunarDay.h"

namespace yiEngine
{
namespace dateTime
{

namespace calc
{
    enum Calc_Type
    {
        Qi,
        Shuo
    };
};

typedef std::map<char, std::string> CompressDicType;
class QiShuoDataUnCompress
{
public:
    QiShuoDataUnCompress(const std::string& data): data_(data) 
    {
        std::string o  = "0000000000";
        std::string o2 = o + o;
        dictionary_.insert(std::make_pair('J', "00"));
        dictionary_.insert(std::make_pair('I', "000"));
        dictionary_.insert(std::make_pair('H', "0000"));
        dictionary_.insert(std::make_pair('G', "00000"));
        dictionary_.insert(std::make_pair('t', "02"));
        dictionary_.insert(std::make_pair('s', "002"));
        dictionary_.insert(std::make_pair('r', "0002"));
        dictionary_.insert(std::make_pair('q', "00002"));
        dictionary_.insert(std::make_pair('p', "000002"));
        dictionary_.insert(std::make_pair('o', "0000002"));
        dictionary_.insert(std::make_pair('n', "00000002"));
        dictionary_.insert(std::make_pair('m', "000000002"));
        dictionary_.insert(std::make_pair('l', "0000000002"));
        dictionary_.insert(std::make_pair('k', "01"));
        dictionary_.insert(std::make_pair('j', "0101"));
        dictionary_.insert(std::make_pair('i', "001"));
        dictionary_.insert(std::make_pair('h', "001001"));
        dictionary_.insert(std::make_pair('g', "0001"));
        dictionary_.insert(std::make_pair('f', "00001"));
        dictionary_.insert(std::make_pair('e', "000001"));
        dictionary_.insert(std::make_pair('d', "0000001"));
        dictionary_.insert(std::make_pair('c', "00000001"));
        dictionary_.insert(std::make_pair('b', "000000001"));
        dictionary_.insert(std::make_pair('a', "0000000001"));
        dictionary_.insert(std::make_pair('A', o2 + o2 + o2));
        dictionary_.insert(std::make_pair('B', o2 + o2 + o));
        dictionary_.insert(std::make_pair('C', o2 + o2));
        dictionary_.insert(std::make_pair('D', o2 + o));
        dictionary_.insert(std::make_pair('E', o2));
        dictionary_.insert(std::make_pair('F', o));
    }

    std::string UnCompress()
    {
        std::string::size_type pos;
        int step = 1;
        for(pos = 0; pos < data_.length(); pos = pos + step)
        {
            step = 1;
            CompressDicType::iterator iter = dictionary_.find(data_[pos]);
            if(iter != dictionary_.end())
            {
                data_.replace(pos, 1, iter->second);
                step = iter->second.length();
            }
        }
        return data_;
    }

private:
    std::string data_;
    CompressDicType dictionary_;
};


class MoonCalculate
{
public:
    MoonCalculate();

    double calc(double jd, calc::Calc_Type qs);
    void   calcY(double jd);
    int    calcJieQi(double jd, commonDef::LunarInfo& zq, bool calcMultiPeriod);
protected:
    std::string init(int type);
    double so_low(double W);
    double qi_low(double W);

    double so_high(double W);
    double qi_high(double W);

    // follow the C# code, but it is not OO
public:
    int leap; // 闰月位置
    std::string SB;    // 朔修正表
    std::string QB;    // 气修正表

    std::vector<double> suoKB;
    std::vector<double> qiKB;
    std::vector<double> HS; // 合朔表
    std::vector<double> dx; // 各月大小
    std::vector<double> Yn; // 年计数
    commonDef::LunarInfo ZQ; // 中气表, 功能与 doulbe[] 类似, 但它有自定义属性的 

    std::vector<chineseNum::CNUM_TYPE> ym;
};


}  // namespace dateTime
}  // namespace YiEngine
#endif



