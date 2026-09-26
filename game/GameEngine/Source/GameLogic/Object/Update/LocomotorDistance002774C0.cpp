// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
// Retail 002774C0, 537 executable bytes plus the five-entry switch table.
// Thiscall ST0 query. Retain the existing opaque method pin.
// 003FD7D0 has four stack arguments and RET16; output +00 distance +04 xyz
// +10 xyz +1C dword +20 dword is a 36-byte record, proved by callee writes.
// Constants read from retail: VA0107FAC4=100.0f; VA01075C74=10.0f.
// Visible noinline Gen_000E5A50 distance helper is the existing matched
// 46-byte body; independently reverified. It does not retain its argument.
// sqrt and sqrtf preserve the two separate x87 return paths.
// ZH getLocomotorDistanceToGoal is the control-flow donor, not identity proof.
// Analyst pack 00172600 proves caller and receiver; all accessed offsets below
// are checked against the whole 537-byte body. 003FD7D0 writes 36 output bytes.
#include <math.h>
#include <string.h>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &c) { x=c.x; y=c.y; z=c.z; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &c) {
    struct Words { unsigned x,y,z; };
    *(Words*)this=*(const Words*)&c; return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &c) {
    Coord3DBase *base=this; *base=c; return *this;
}
inline Coord3D &Coord3D::Sub(const Coord3DBase &c) { x-=c.x;y-=c.y;z-=c.z;return *this; }
inline float Coord3D::GetLength() const { return (float)sqrt(x*x+y*y+z*z); }
extern void j_0003251f();
extern void j_00048e4b();
extern void j_00024d1b();
extern void j_00008a9e();
extern void j_00008a26();
class BfmeVec3EJ { public: float x,y,z; };
class Gen_000E5A50 {
public:
    char pad000[0x38]; float x,y,z;
    __declspec(noinline) float bfmeDistanceSquared(const BfmeVec3EJ *p) const;
};
class DistanceObject002774C0 {
public:
    char pad000[0x38]; Coord3D at038;
bool kind(int i) const {
    typedef bool (DistanceObject002774C0::*Call)(int) const;
    union { void(*raw)(); Call method; } route={j_0003251f};
    return (this->*route.method)(i);
}
float squared(const Coord3D *p) const {
    return ((const Gen_000E5A50*)this)->bfmeDistanceSquared((const BfmeVec3EJ*)p);
}
};
struct DistanceMachine002774C0 { char pad000[0x24]; Coord3D at024; };
struct DistanceLocomotor002774C0 {
    char pad000[0x40]; unsigned at040;
    bool close3D() const { return ((at040>>10)&1)!=0; }
int value() const {
    typedef int (DistanceLocomotor002774C0::*Call)() const;
    union { void(*raw)(); Call method; } route={j_00048e4b};
    return (this->*route.method)();
}
};
struct DistanceNode002774C0 { char pad000[12]; Coord3D at00c; const Coord3D *position() const { return &at00c; } };
struct DistanceInfo002774C0 {
    float distance; Coord3D point; Coord3D at010; int at01c; int at020;
};
class DistancePath002774C0 {
public:
    char pad000[8]; DistanceNode002774C0 *at008;
float flight(const Coord3D *p,Coord3D &out) {
    typedef float (DistancePath002774C0::*Call)(const Coord3D*,Coord3D&);
    union { void(*raw)(); Call method; } route={j_00024d1b};
    return (this->*route.method)(p,out);
}
void ground(DistanceObject002774C0 *o,DistanceLocomotor002774C0 *l,DistanceInfo002774C0 &out,bool update) {
    typedef void (DistancePath002774C0::*Call)(DistanceObject002774C0*,DistanceLocomotor002774C0*,DistanceInfo002774C0&,bool);
    union { void(*raw)(); Call method; } route={j_00008a9e};
    (this->*route.method)(o,l,out,update);
}
};
template<int N> class DistanceSlots002774C0 : public DistanceSlots002774C0<N-1> {
public: virtual void slot(char (*)[N])=0;
};
template<> class DistanceSlots002774C0<0> {};
class AIUpdateInterface : public DistanceSlots002774C0<135> {
public:
    virtual bool slot21C()=0;
    char pad004[4]; DistanceObject002774C0 *m_object;
    char pad00c[0x30-12]; DistanceMachine002774C0 *m_stateMachine;
    char pad034[0x140-0x34]; DistancePath002774C0 *m_path;
    char pad144[0x1cc-0x144]; DistanceLocomotor002774C0 *m_curLocomotor;
    char pad1d0[8]; int at1d8; Coord3D at1dc;
    float rva002774c0();
};
float Gen_000E5A50::bfmeDistanceSquared(const BfmeVec3EJ *p) const {
    float dx=x-p->x; float dy=y-p->y; float dz=z-p->z;
    return dx*dx+dy*dy+dz*dz;
}
float AIUpdateInterface::rva002774c0() {
    switch(at1d8) {
    case 2:
    case 4: {
        Coord3D delta(at1dc);
        delta.Sub(m_object->at038);
        return delta.GetLength();
    }
    case 1: {
        DistancePath002774C0 *path=m_path;
        if(!path) return 100.0f;
        DistanceLocomotor002774C0 *loco=m_curLocomotor;
        if(!loco) return 0.0f;
        else if(loco->close3D() || m_object->kind(25)) {
            DistanceObject002774C0 *me=m_object;
            Coord3D dest(m_stateMachine->at024);
            if(path->at008) memcpy(&dest,&path->at008->at00c,12);
            return (float)sqrt(me->squared(&dest));
        } else {
            if(loco->value()==5) break;
            Coord3D goal;
            bool aircraft=slot21C();
            float dist;
            if(aircraft) { DistanceObject002774C0 *object=m_object; Coord3D &out=goal; dist=m_path->flight(&object->at038,out); }
            else {
                DistanceInfo002774C0 info;
                m_path->ground(m_object,m_curLocomotor,info,false);
                goal=info.point;
                dist=info.distance;
            }
            if(m_path->at008) memcpy(&goal,&m_path->at008->at00c,12);
            float dx=goal.x-m_object->at038.x;
            float dy=goal.y-m_object->at038.y;
            float square=dx*dx+dy*dy;
            if(aircraft) {
                if(dist*dist>square) return (float)sqrt(square);
                else return dist;
            }
            if(dist<10.0f || dist*dist<square) return sqrtf(square);
            else return dist;
        }
    }
    case 0:
    case 3: return 0.0f;
    }
    return 0.0f;
}
