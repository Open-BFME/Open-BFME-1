// cl: /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
#include "fx_particle_system.h"

class Sub005C92F0
{
public:
    Sub005C92F0 &operator=(const Sub005C92F0 &source);
};

namespace FXParticleSystem
{

class Y3Clonable
{
public:
    virtual ~Y3Clonable();
    virtual Y3Clonable *clone();
};

class Y3AssignTail_005CBEE0Prefix
{
public:
    Y3AssignTail_005CBEE0Prefix();

    Y3Clonable *m_first;
    Y3Clonable *m_second;
};

class Y3AssignTail_005CBEE0 : public Y3AssignTail_005CBEE0Prefix, public Sub005C92F0
{
public:
    Y3AssignTail_005CBEE0 &operator=(const Y3AssignTail_005CBEE0 &that);
};

// ??4Y3AssignTail_005CBEE0@FXParticleSystem@@QAEAAV01@ABV01@@Z
Y3AssignTail_005CBEE0 &Y3AssignTail_005CBEE0::operator=(const Y3AssignTail_005CBEE0 &that)
{
    Y3Clonable *sourceFirst = that.m_first;
    Y3Clonable *copyFirst = sourceFirst ? sourceFirst->clone() : 0;
    delete m_first;
    m_first = copyFirst;
    Y3Clonable *sourceSecond = that.m_second;
    Y3Clonable *copySecond = sourceSecond ? sourceSecond->clone() : 0;
    delete m_second;
    m_second = copySecond;
    const Sub005C92F0 &sourceTail = static_cast<const Sub005C92F0 &>(that);
    static_cast<Sub005C92F0 &>(*this) = sourceTail;
    return *this;
}

}
