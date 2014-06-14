#ifndef YIENGINE_COMMON_IDAY_BUILDER_H
#define YIENGINE_COMMON_IDAY_BUILDER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <boost/shared_ptr.hpp>

namespace yiEngine
{
namespace dateTime
{

template<typename T>
class IDayBuilder
{
public:
    virtual ~IDayBuilder() {}

    virtual bool Build(T& obj, double year, double month, double day,
        double hour, double minute, double second) = 0;

};

template<typename T>
bool GetBuilder(boost::shared_ptr<IDayBuilder<T> >& obj); 

}  // namespace dateTime
}  // namespace YiEngine


#endif