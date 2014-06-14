#ifndef YIENGINE_COMMON_C_SIX_YAO_H
#define YIENGINE_COMMON_C_SIX_YAO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <YiEngine/SixYao/ISixYao.h>

namespace yiEngine
{
namespace sixYao
{
class SixYao : public ISixYao
{
public:
    virtual void TestFun()
    {
        std::cout << "Hello!!!!" << std::endl;        
    }
};

}  // namespace sixYao
}  // namespace YiEngine
#endif
