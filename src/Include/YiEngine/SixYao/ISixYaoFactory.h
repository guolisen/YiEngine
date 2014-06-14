#ifndef YIENGINE_COMMON_I_SIX_YAO_FACTORY_H
#define YIENGINE_COMMON_I_SIX_YAO_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

#include <YiEngine/SixYao/ISixYao.h>

namespace yiEngine
{
namespace sixYao
{
class ISixYaoFactory
{
public:
    virtual ~ISixYaoFactory() {}
public:
    virtual SixYaoPtr CreateObject() = 0;
};

typedef boost::shared_ptr<ISixYaoFactory> SixYaoFactoryPtr;

}  // namespace SixYao
}  // namespace YiEngine
#endif
