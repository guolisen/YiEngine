#ifndef YIENGINE_COMMON_C_SIX_YAO_FACTORY_H
#define YIENGINE_COMMON_C_SIX_YAO_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <YiEngine/SixYao/ISixYaoFactory.h>
#include "SixYao.h"

namespace yiEngine
{
namespace sixYao
{
class SixYaoFactory : public ISixYaoFactory
{
public:
    virtual SixYaoPtr CreateObject()
    {
        return boost::make_shared<SixYao>();
    }
};

}  // namespace sixYao
}  // namespace YiEngine
#endif
