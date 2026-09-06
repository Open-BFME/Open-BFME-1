// ??4Y3AssignTail_005CBEE0@FXParticleSystem@@QAEAAV01@ABV01@@Z
// partial score=0.85 date=2026-09-05
// cl: /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
//
// Near-twin of ParticleSystemTemplateTailAssignShim::operator= (twin
// 0x005CF100, fx_particle_system_bulk.cpp): same clone-two-pointers-then-
// assign-tail shape, but the tail here is a different type
// (U1Tail_005CD380, pinned in reverse/symbols.csv at this same address as
// ??4U1Tail_005CD380@@QAEAAV0@ABV0@@Z and again as
// ??4Y3AssignTail_005CBEE0@@QAEAAV0@ABV0@@Z), and its call site uses `lea`
// to form the pointer to the source tail instead of `add`: materializing the
// tail-source address before the clone/delete pairs (instead of deriving it
// from the parameter register at the tail line) keeps the parameter pointer
// alive in its own register through the whole body.
#include "fx_particle_system.h"

class U1Tail_005CD380 {
public:
    void assign(const void *source);
};

namespace FXParticleSystem {

class Y3AssignTail_005CBEE0 {
public:
    Y3AssignTail_005CBEE0 &operator=(const Y3AssignTail_005CBEE0 &that);

private:
    class Clonable {
    public:
        virtual ~Clonable();
        virtual Clonable *clone();
    };

    Clonable *m_first;
    Clonable *m_second;
    unsigned char m_tail[1];
};

// @??4Y3AssignTail_005CBEE0@FXParticleSystem@@QAEAAV01@ABV01@@Z 0x005CBEE0
Y3AssignTail_005CBEE0 &Y3AssignTail_005CBEE0::operator=(const Y3AssignTail_005CBEE0 &that)
{
    Clonable *sourceFirst = that.m_first;
    Clonable *copyFirst = sourceFirst ? sourceFirst->clone() : 0;
    delete m_first;
    m_first = copyFirst;
    Clonable *sourceSecond = that.m_second;
    Clonable *copySecond = sourceSecond ? sourceSecond->clone() : 0;
    delete m_second;
    m_second = copySecond;
    ((U1Tail_005CD380 *)(m_tail))->assign(that.m_tail);
    return *this;
}

}
