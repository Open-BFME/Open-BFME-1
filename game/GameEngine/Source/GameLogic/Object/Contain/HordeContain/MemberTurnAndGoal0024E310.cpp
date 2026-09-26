// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// Retail RVA 0024E310: complete 728-byte member-order body, ret16, no EH.
// Source home and shared ABI/layout witnesses: docs/analysis/0x002417e0.md.
// Address-derived identities intentionally do not assert original method names.
// The complete body has 17 direct calls and 5 virtual calls. The matching
// source retains both flag-clear/slot1e8 return blocks using distinct zero-code
// barriers; see docs/shape_levers.md (identical return tails).
// Additional ABI witnesses beyond the analyst hub:
// 00021017 -> 001BE010: Object[204]->[1CC], zero args, pointer EAX.
// 00046AD3 -> 001B9C10: that locomotor receiver, Object* arg, ret4, AL tested.
// 00024EA6 -> 001B5860: same receiver and Object*, ret4, float ST0.
// 0002EF64 -> 0016A310: cdecl(float,float), float ST0, caller cleanup8.
// 0003D334 -> 003EE7A0: eight stack words, ret32, AL tested here.
// 0002A4F5 -> 002325F0: Object* and coordinate*, ret8, compare AL with 1.
// 000392CA -> 003E5010: Object*, mutable coordinate*, owner Object*, bool,
// ret16; 0000E200 -> 0024DA80: Object*, coordinate*, float, ret12.
// All existing ILT names are reused without new semantic pins. Float angle
// type and slot1e4's argument are independently proved by x87 dataflow.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &p) : Coord3DBase(p) {}
inline Coord3DBase& Coord3DBase::operator=(const Coord3DBase &p) {
    struct Raw { unsigned x,y,z; };
    *(Raw*)this=*(const Raw*)&p;
    return *this;
}
inline Coord3D& Coord3D::operator=(const Coord3D &p) {
    Coord3DBase *base=this;
    *base=p;
    return *this;
}


#include <math.h>
extern "C" void _ReadWriteBarrier();
extern "C" void _WriteBarrier();
#pragma intrinsic(_ReadWriteBarrier, _WriteBarrier)
class MemberCall0024E310 {};
template<class T> __forceinline T member24e310(void (*raw)()) {
    union { void (*raw)(); T m; } u; u.raw=raw; return u.m;
}
#define CALL(T,p,j) (((MemberCall0024E310*)(p))->*member24e310<T>(j))
typedef void (MemberCall0024E310::*Void0)();
typedef bool (MemberCall0024E310::*Bool0)();
typedef int (MemberCall0024E310::*Int0)();
typedef void* (MemberCall0024E310::*Ptr0)();
typedef bool (MemberCall0024E310::*BoolPtr)(void*);
typedef float (MemberCall0024E310::*FloatPtr)(void*);
typedef unsigned char (MemberCall0024E310::*Ahead)(void*,const Coord3D*);
typedef void (MemberCall0024E310::*Apply)(void*,const Coord3D*,float);
typedef void (MemberCall0024E310::*Adjust)(void*,Coord3D*,void*,bool);
typedef unsigned char (MemberCall0024E310::*Line)(void*,unsigned,int,const Coord3D*,const Coord3D*,int,bool,bool);
typedef float (__cdecl *AngleDiff)(float,float);
extern void j_00044774(); extern void j_0002191d();
extern void j_0001fb9a(); extern void j_00006dcf();
extern void j_0003a391(); extern void j_0003d334();
extern void j_00021017(); extern void j_00046ad3();
extern void j_00024ea6(); extern void j_0002ef64();
extern void j_0002a4f5(); extern void j_00004a11();
extern void j_000392ca(); extern void j_0000e200();
class MemberAI0024E310 {
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00c();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01c();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02c();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03c();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04c();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05c();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06c();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07c();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08c();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09c();
    virtual void slot0a0();
    virtual void slot0a4();
    virtual void slot0a8();
    virtual void slot0ac();
    virtual void slot0b0();
    virtual void slot0b4();
    virtual void slot0b8();
    virtual void slot0bc();
    virtual void slot0c0();
    virtual void slot0c4();
    virtual void slot0c8();
    virtual void slot0cc();
    virtual void slot0d0();
    virtual void slot0d4();
    virtual void slot0d8();
    virtual void slot0dc();
    virtual void slot0e0();
    virtual void slot0e4();
    virtual void slot0e8();
    virtual void slot0ec();
    virtual void slot0f0();
    virtual void slot0f4();
    virtual void slot0f8();
    virtual void slot0fc();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10c();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11c();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12c();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13c();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14c();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15c();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16c();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17c();
    virtual void slot180();
    virtual bool slot184();
    virtual void slot188();
    virtual void slot18c();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19c();
    virtual void slot1a0();
    virtual void slot1a4();
    virtual void slot1a8();
    virtual void slot1ac();
    virtual void slot1b0();
    virtual void slot1b4();
    virtual void slot1b8();
    virtual void slot1bc();
    virtual void slot1c0();
    virtual void slot1c4();
    virtual void slot1c8();
    virtual void slot1cc();
    virtual void slot1d0();
    virtual void slot1d4();
    virtual void slot1d8();
    virtual void slot1dc();
    virtual void slot1e0();
    virtual void slot1e4(float);
    virtual void slot1e8();
    char pad004[0x140-4]; void *m_path;
    char pad144[0x1b8-0x144]; unsigned word1b8;
    char pad1bc[0x1d8-0x1bc]; int word1d8;
};
struct MemberSub0024E310 { char pad00[0x5c]; bool flag5c; };
struct MemberObject0024E310 {
    char pad00[0x38]; Coord3D m_position; float m_orientation;
    char pad48[0x110-0x48]; unsigned m_modelConditionFlags[10];
    char pad138[0x204-0x138]; MemberAI0024E310 *m_ai; MemberSub0024E310 *ptr208;
    char pad20c[0x344-0x20c]; unsigned m_privateStatus;
    __forceinline void clear114() {
        if (m_modelConditionFlags[1]&0x10000000) {
            m_modelConditionFlags[1]&=~0x10000000;
            CALL(Void0,this,j_0002191d)();
        }
    }
};
struct MemberAIService0024E310 { char pad00[12]; void *m_pathfinder; };
extern MemberAIService0024E310 *TheAI;
class MemberTurnAndGoal0024E310 {
public:
    void *vptr; void *data04; MemberObject0024E310 *object08;
    char pad0c[0xe8-12]; bool flagE8; bool flagE9;
    char padEa[0x148-0xea]; void *ptr148;
    char pad14c[0x1fc-0x14c]; bool flag1fc;
    char pad1fd[7]; bool flag204;
    void apply(MemberObject0024E310*,const Coord3D*,float,bool);
};
void MemberTurnAndGoal0024E310::apply(MemberObject0024E310 *obj,const Coord3D *position,float orientation,bool flag)
{
    MemberAI0024E310 *ai=obj->m_ai;
    MemberObject0024E310 *owner=object08;
    MemberAI0024E310 *ownerAI=owner->m_ai;
    Coord3D dest;
    if ((obj->ptr208 && obj->ptr208->flag5c) || (obj->m_privateStatus&1) || !ownerAI || !ai) return;
    if (ai->slot184() && !CALL(Bool0,ownerAI,j_00044774)()) {
        obj->clear114();
        ai->slot1e8();
        _WriteBarrier();
        return;
    }
    if (flag1fc) {
        CALL(Apply,this,j_0001fb9a)(obj,position,orientation);
        return;
    }
    if (ai->word1d8==4 && ai->m_path) {
        if (!CALL(Bool0,ai->m_path,j_00006dcf)()) {
            unsigned surfaces=ai->word1b8;
            void *pathfinder=TheAI->m_pathfinder;
            if (CALL(Line,pathfinder,j_0003d334)(obj,surfaces,
                    CALL(Int0,obj,j_0003a391)(),&obj->m_position,position,0,true,true)) {
                ai->slot1e8();
                goto after_path;
            }
        }
        flagE8=true;
        return;
    }
after_path:
    if (!CALL(BoolPtr,CALL(Ptr0,owner,j_00021017)(),j_00046ad3)(owner)) {
        float current=obj->m_orientation;
        float maxTurn=CALL(FloatPtr,CALL(Ptr0,obj,j_00021017)(),j_00024ea6)(obj);
        float delta=((AngleDiff)j_0002ef64)(orientation,current);
        if (fabs(delta) > maxTurn*0.5f) {
            if (delta>maxTurn) delta=maxTurn;
            else if (delta < -maxTurn) delta=-maxTurn;
            ai->slot1e4(delta+current);
            return;
        }
    }
    if (!flagE9 && CALL(Ahead,this,j_0002a4f5)(obj,position)==1 && !ptr148 &&
        (CALL(Bool0,ownerAI,j_00044774)() || CALL(BoolPtr,this,j_00004a11)(obj))) {
        obj->clear114();
        ai->slot1e8();
        _ReadWriteBarrier();
        return;
    }
    if (flag204) dest=owner->m_position;
    else {
        dest=*position;
        CALL(Adjust,TheAI->m_pathfinder,j_000392ca)(obj,&dest,owner,!flag);
    }
    CALL(Apply,this,j_0000e200)(obj,&dest,orientation);
    return;
}
