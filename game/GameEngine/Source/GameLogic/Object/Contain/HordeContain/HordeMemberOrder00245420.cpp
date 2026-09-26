// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// Retail RVA 00245420, 931 bytes; ECX owner and four stack arguments, ret 16.
// Opaque owner and fields follow the complete retail instructions. Hub ABI:
// docs/analysis/0x003e9720.md. The source-file literal proves the home directory.
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

// Method-only ABI declaration; Thing::setOrientation is independently landed at
// 00132E40 with the existing 000399A5 ILT pin. No Thing storage is instantiated.
class Thing { public: void setOrientation(float); };
class MemberCall00245420 {};
template<class T> __forceinline T member245420(void (*raw)()) {
    union { void (*raw)(); T m; } u; u.raw=raw; return u.m;
}
#define CALL(T,p,j) (((MemberCall00245420*)(p))->*member245420<T>(j))
typedef void (MemberCall00245420::*Void0)();
typedef bool (MemberCall00245420::*Bool0)();
typedef int (MemberCall00245420::*Int0)();
typedef float (MemberCall00245420::*Float0)();
typedef float (MemberCall00245420::*FloatPtr)(void*);
typedef void (MemberCall00245420::*VoidPtr)(const void*);
typedef void (MemberCall00245420::*VoidFloat)(float);
typedef bool (MemberCall00245420::*BoolPtr)(void*);
typedef bool (MemberCall00245420::*BoolInt)(int);
typedef void (MemberCall00245420::*Command)(int,int);
typedef unsigned char (MemberCall00245420::*Ahead)(void*,const Coord3D*);
typedef void (MemberCall00245420::*Height)(float,void*);
typedef void (MemberCall00245420::*Apply)(void*,const Coord3D*,int);
typedef void (MemberCall00245420::*Adjust)(void*,Coord3D*,void*,bool);
typedef void (MemberCall00245420::*UpdateGoal)(void*,const Coord3D*,int,const char*,int);
extern void j_00044774(); extern void j_00043ced(); extern void j_0001336d();
extern void j_000016a4(); extern void j_00012486(); extern void j_0002191d();
extern void j_0003251f(); extern void j_0003a1a7(); 
extern void j_0001a9dd(); extern void j_0003a391(); extern void j_000294e2();
extern void j_000047c8(); extern void j_00030d5f(); extern void j_00006dcf();
extern void j_0002a4f5(); extern void j_00004a11(); extern void j_000392ca();
extern void j_0001fb9a();
class MemberAI00245420 {
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
    virtual bool slot18c();
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
    virtual void slot1e4();
    virtual void slot1e8();

    char pad004[0x140-4]; void *m_path;
    char pad144[0x1cc-0x144]; void *m_curLocomotor;
    char pad1d0[8]; int word1d8;
};
struct MemberSub00245420 { char pad00[0x5c]; bool flag5c; };
struct MemberObject00245420 {
    char pad00[0x38]; Coord3D m_position; float m_orientation;
    char pad48[0x110-0x48]; unsigned m_modelConditionFlags[10];
    char pad138[0x204-0x138]; MemberAI00245420 *m_ai; MemberSub00245420 *ptr208;
    char pad20c[0x344-0x20c]; unsigned m_privateStatus;
    __forceinline void clear114() {
        if (m_modelConditionFlags[1]&0x10000000) {
            m_modelConditionFlags[1]&=~0x10000000;
            CALL(Void0,this,j_0002191d)();
        }
    }
};
struct MemberData00245420 {
    char pad00[0x2d8]; unsigned char byte2d8;
    char pad2d9[7]; float value2e0;
};
struct MemberAIService00245420 { char pad00[12]; void *m_pathfinder; };
extern MemberAIService00245420 *TheAI;
template<class T> __forceinline const T& min245420(const T&a,const T&b) {return a<b?a:b;}
template<class T> inline T sqr245420(T x) { return x*x; }
class HordeMemberOrder00245420 {
public:
    void *vptr; MemberData00245420 *data04; MemberObject00245420 *object08;
    char pad0c[0xe8-12]; bool flagE8; bool flagE9;
    char padEa[0x148-0xea]; void *ptr148;
    char pad14c[0x1fc-0x14c]; bool flag1fc;
    char pad1fd[7]; bool flag204;
    void apply(MemberObject00245420*,const Coord3D*,int,bool);
};
void HordeMemberOrder00245420::apply(MemberObject00245420 *obj,const Coord3D *position,int arg3,bool arg4)
{
    MemberAI00245420 *ai=obj->m_ai;
    MemberData00245420 *data=data04;
    MemberObject00245420 *owner=object08;
    MemberAI00245420 *ownerAI=owner->m_ai;
    Coord3D dest;
    if ((obj->ptr208 && obj->ptr208->flag5c) || (obj->m_privateStatus&1) || !ownerAI || !ai) return;
    if (CALL(Bool0,ownerAI,j_00044774)() && !flag1fc) {
        float dist=CALL(FloatPtr,owner,j_00043ced)(obj);
        Coord3D delta;
        delta.x=obj->m_position.x;
        delta.y=obj->m_position.y;
        delta.z=obj->m_position.z;
        delta.Sub(*position);
        delta.z=0.0f;
        float len=delta.GetLengthSqrd();
        // Retail +CF reads the selected operand once before loading value2e0.
        float nearest=(const volatile float&)min245420(dist,len);
        float radius=data->value2e0;
        if (nearest>sqr245420(radius) && !ai->slot18c())
            CALL(Command,(char*)ai+0x20,j_0001336d)(0,2);
    }
    if (ai->slot184()) {
        bool status=CALL(BoolInt,obj,j_000016a4)(74);
        if (!CALL(Bool0,ownerAI,j_00044774)() || !status) {
            if (CALL(Bool0,ai,j_00044774)()) CALL(Void0,ai,j_00012486)();
            obj->clear114();
            ai->slot1e8();
            return;
        }
    }
    MemberData00245420 *data2=data04;
    if (CALL(BoolInt,obj,j_0003251f)(11)) {
        if (!flag1fc || CALL(Bool0,ownerAI,j_00044774)()) {
            CALL(VoidPtr,obj,j_0003a1a7)(&owner->m_position);
            ((Thing*)obj)->setOrientation(owner->m_orientation);
            CALL(VoidPtr,obj,j_0001a9dd)(owner->m_modelConditionFlags);
            if (!CALL(Bool0,ownerAI,j_00044774)()) {
                void *pathfinder=TheAI->m_pathfinder;
                CALL(UpdateGoal,pathfinder,j_000294e2)(obj,&obj->m_position,
                    CALL(Int0,obj,j_0003a391)(),
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x6e6);
            }
            if (obj->m_ai && obj->m_ai->m_curLocomotor) {
                void *locomotor=obj->m_ai->m_curLocomotor;
                CALL(Height,locomotor,j_00030d5f)(CALL(Float0,owner,j_000047c8)(),obj);
            }
        }
        return;
    }
    if (flag1fc) {
        if (ai->word1d8==4 && ai->m_path && CALL(Bool0,ai->m_path,j_00006dcf)()) {
            flagE8=true;
            return;
        }
        CALL(Apply,this,j_0001fb9a)(obj,position,arg3);
    } else {
        if (ai->word1d8==4 && ai->m_path) { flagE8=true; return; }
        if (!arg4 && !flagE9 && CALL(Ahead,this,j_0002a4f5)(obj,position)==1
            && !ptr148 && data2->byte2d8==1 &&
            (CALL(Bool0,ownerAI,j_00044774)() || CALL(BoolPtr,this,j_00004a11)(obj))) {
            if (CALL(Bool0,ai,j_00044774)()) CALL(Void0,ai,j_00012486)();
            obj->clear114();
            ai->slot1e8();
            flagE8=true;
            return;
        }
        if (flag204) dest=owner->m_position;
        else {
            dest=*position;
            CALL(Adjust,TheAI->m_pathfinder,j_000392ca)(obj,&dest,owner,!arg4);
        }
        CALL(Apply,this,j_0001fb9a)(obj,&dest,arg3);
    }
}
