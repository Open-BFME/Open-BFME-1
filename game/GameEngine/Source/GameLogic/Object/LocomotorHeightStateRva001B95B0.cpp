// cl: /O2 /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWMath
// Retail 0x001B95B0, 603B: three-argument thiscall returning an x87 float.
// Called by the behavior-Z handler at 0x001BA1C0. Semantic class identity is
// deliberately address-qualified. The state chooses height44/height48 using
// weapon readiness, an AI virtual predicate, planar distance and current height.
// Callee 0x00150340 is independently decoded: thiscall, no stack arguments,
// returns the pointed-to override, following +4 with 0x000022BB when present.
// All three caller sites pass this+4 through the ILT at 0x00026E95.
// Object+38/+344 and template+60 names are layout/name-oracle witnesses.
#include "coord3d.h"
inline Coord3D::Coord3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
inline Coord3D::~Coord3D() {}
#include <math.h>
#pragma intrinsic(sqrt)
inline Coord2D::Coord2D(float a, float b) { x=a; y=b; }
inline Coord2D::~Coord2D() {}
inline Coord2D &Coord2D::Sub(const Coord3DBase &p) { x-=p.x; y-=p.y; return *this; }
inline float Coord2D::length() const { return (float)sqrt(x*x+y*y); }
inline Coord3D &Coord3D::Sub(const Coord3DBase &p) { x-=p.x; y-=p.y; z-=p.z; return *this; }
inline float Coord3D::GetLength2D() const { return (float)sqrt(x*x+y*y); }
struct Rva001B95B0Flags {
    unsigned m_bits[10];
    unsigned test(unsigned i) const { return m_bits[i>>5] & (1u<<(i&31)); }
    void set(unsigned i) { m_bits[i>>5] |= (1u<<(i&31)); }
};
class Weapon;
enum WeaponSlotType { SLOT_ZERO };
enum WeaponStatus { READY_ZERO };
class Weapon { public: WeaponStatus getStatus() const; };
class Rva001B95B0AI {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual bool check001B95B0();
};
class Object {
public:
    char before38[0x38];
    Coord3D m_cachedPos;
    char before110[0x110-0x44];
    Rva001B95B0Flags m_modelConditionFlags;
    char before204[0x204-0x138];
    Rva001B95B0AI *m_ai;
    char before344[0x344-0x208];
    unsigned char m_privateStatus;
    Weapon *getCurrentWeapon(WeaponSlotType*);
    void notifyModelConditionChanged();
    const Coord3D *getPosition() const { return &m_cachedPos; }
};
class Overridable {
public:
    void *vtable;
    Overridable *m_nextOverride;
    Overridable *getFinalOverride();
};
struct Rva001B95B0Template : Overridable {
    char before60[0x60-8];
    float m_circlingRadius;
};
struct Rva00150340Override {
    Rva001B95B0Template *m_template;
    const Rva001B95B0Template *getResolved() const;
};
template<class T> inline const T &minimum001B95B0(const T &a,const T &b) { return b<a ? b:a; }
struct Rva001B95B0HeightState {
    void *vtable;
    Rva00150340Override m_template;
    char before40[0x40-8];
    unsigned int m_flags;
    float height44;
    float height48;
    char before98[0x98-0x4c];
    int state98;
    bool getFlag(unsigned mask) const { return (m_flags&mask)!=0; }
    float update(Object *object,const Coord3D *goal,float surfaceHeight);
};
float Rva001B95B0HeightState::update(Object *object,const Coord3D *goal,float surfaceHeight)
{
    if(height48>0.0f) {
        Rva001B95B0AI *ai=object->m_ai;
        if(ai) {
            Coord3D diff=*goal;
            Coord3D pos=*object->getPosition();
            diff.Sub(pos);
            float distance=diff.GetLength2D();
            float currentHeight=pos.z-surfaceHeight;
            Weapon *weapon=object->getCurrentWeapon(0);
            if(object->m_privateStatus&1) {
                if(currentHeight<=0.0f) {
                    if(!object->m_modelConditionFlags.test(115)) {
                        object->m_modelConditionFlags.set(115);
                        object->notifyModelConditionChanged();
                    }
                }
                return 0.0f;
            }
            if(weapon) {
                Rva001B95B0Template *resolved=m_template.m_template;
                if(resolved && resolved->m_nextOverride) resolved=(Rva001B95B0Template*)resolved->m_nextOverride->getFinalOverride();
                if(resolved->m_circlingRadius>0.0f) {
                    switch(state98) {
                    case 2: {
                        float delta=height44-height48;
                        float distanceScale=distance/m_template.getResolved()->m_circlingRadius*2.0f;
                        float result=delta*minimum001B95B0(distanceScale,1.0f)+height48;
                        if(currentHeight>=height44) state98=0;
                        return result;
                    }
                    case 1: {
                        float delta=height44-height48;
                        float distanceScale=distance/m_template.getResolved()->m_circlingRadius;
                        float result=delta*minimum001B95B0(distanceScale,1.0f)+height48;
                        if(weapon->getStatus()!=READY_ZERO || !ai->check001B95B0()) state98=2;
                        return result;
                    }
                    case 0:
                        if(!getFlag(4) && distance<m_template.getResolved()->m_circlingRadius && ai->check001B95B0()) {
                            state98=1;
                            return height44;
                        }
                        break;
                    }
                    return height44;
                }
            }
            state98=0;
        }
    }
    return height44;
}
