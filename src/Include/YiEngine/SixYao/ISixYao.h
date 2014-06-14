#ifndef YIENGINE_COMMON_I_SIX_YAO_H
#define YIENGINE_COMMON_I_SIX_YAO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>

namespace yiEngine
{
namespace sixYao
{
class ISixYao
{
public:
    virtual ~ISixYao() {}
public:
    virtual void TestFun() = 0;
};

typedef boost::shared_ptr<ISixYao> SixYaoPtr;

}  // namespace SixYao
}  // namespace YiEngine
#endif
