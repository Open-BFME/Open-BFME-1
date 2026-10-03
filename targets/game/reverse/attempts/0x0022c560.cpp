// ?method@Rva0022C560@@QAEXPAVObject@@H@Z
// partial score=0.3607 date=2026-10-03
// Complete experimental draft: 0x0022C560, 1253-byte retail extent.
// Native Object/Thing/Coord3D/Matrix3D/vector headers; opaque interface receiver.
// Not byte-exact: stack 0x6c vs retail 0x64 and x87/call-tail differences.
// ILT function-pointer adapters preserve observed receiver/stack arities.
// They are draft ABI views, not additional semantic callee identities.
// In particular j_00023d49 must use the existing bfmeTwo941F binding before
// strict promotion; no pins or production names have been changed.
// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "matrix3d.h"
#include "Lib/BaseType.h"
#include <vector>
#define BFME_HAVE_COORD3D
class Player;
#define THING_TU_MEMBERS const Coord3D *getUnitDirectionVector2D() const; void setOrientation(float); bool isKindOf(int) const;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; void *findModule(int) const; bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const; void setLayer(int); void notifyModelConditionChanged();
#include "GameLogic/Object/object.h"
namespace _STL {
template<> void vector<Coord3D>::push_back(const Coord3D &);
template<> vector<Coord3D>::~vector();
}
class Rva0022C560Call {};
template<class R> inline R c0(void (*route)(),void *p) { union {void (*raw)(); R (Rva0022C560Call::*method)();} c; c.raw=route; return (((Rva0022C560Call*)p)->*c.method)(); }
template<class R,class A> inline R c1(void (*route)(),void *p,A a) { union {void (*raw)(); R (Rva0022C560Call::*method)(A);} c; c.raw=route; return (((Rva0022C560Call*)p)->*c.method)(a); }
template<class R,class A,class B> inline R c2(void (*route)(),void *p,A a,B b) { union {void (*raw)(); R (Rva0022C560Call::*method)(A,B);} c; c.raw=route; return (((Rva0022C560Call*)p)->*c.method)(a,b); }
template<class R,class A,class B,class C> inline R c3(void (*route)(),void *p,A a,B b,C z) { union {void (*raw)(); R (Rva0022C560Call::*method)(A,B,C);} c; c.raw=route; return (((Rva0022C560Call*)p)->*c.method)(a,b,z); }
template<class R,class A,class B,class C,class D,class E> inline R c5(void (*route)(),void *p,A a,B b,C z,D d,E e) { union {void (*raw)(); R (Rva0022C560Call::*method)(A,B,C,D,E);} c; c.raw=route; return (((Rva0022C560Call*)p)->*c.method)(a,b,z,d,e); }
extern void j_0000315c(); extern void j_0000b81b(); extern void j_0001022b(); extern void j_00011252();
extern void j_0001621b(); extern void j_00019f42(); extern void j_0001c675(); extern void j_0001c882();
extern void j_0001da34(); extern void j_00020824(); extern void j_0002191d(); extern void j_00024d70();
extern void j_000294e2(); extern void j_00029f3c(); extern void j_0002ae23(); extern void j_0003251f();
extern void j_00035e0e(); extern void j_000399A5(); extern void j_0003add7(); extern void j_00040246();
extern void j_00047690(); extern void j_00048112(); extern void j_00023d49();
class BfmeGeometryInfo {public: float boxMajorRadius() const;};
class AI; class GameLogic; class TerrainLogic; class NameKeyGenerator;
extern AI *TheAI; extern GameLogic *TheGameLogic; extern TerrainLogic *TheTerrainLogic; extern NameKeyGenerator *TheNameKeyGenerator;
typedef void (Rva0022C560Call::*M0000315c)(Object*);
__forceinline M0000315c m0000315c() {union {void (*raw)();M0000315c method;} p; p.raw=j_0000315c;return p.method;}
typedef void (Rva0022C560Call::*M0000b81b)(Object*);
__forceinline M0000b81b m0000b81b() {union {void (*raw)();M0000b81b method;} p; p.raw=j_0000b81b;return p.method;}
typedef void (Rva0022C560Call::*M0001022b)(const std::vector<Coord3D>*,Object*,int);
__forceinline M0001022b m0001022b() {union {void (*raw)();M0001022b method;} p; p.raw=j_0001022b;return p.method;}
typedef bool (Rva0022C560Call::*M00011252)(Object*,const void*,Coord3D*);
__forceinline M00011252 m00011252() {union {void (*raw)();M00011252 method;} p; p.raw=j_00011252;return p.method;}
typedef void (Rva0022C560Call::*M0001621b)(const Coord3D*,bool);
__forceinline M0001621b m0001621b() {union {void (*raw)();M0001621b method;} p; p.raw=j_0001621b;return p.method;}
typedef bool (Rva0022C560Call::*M00019f42)(const char*,Coord3D*,Matrix3D*);
__forceinline M00019f42 m00019f42() {union {void (*raw)();M00019f42 method;} p; p.raw=j_00019f42;return p.method;}
typedef int (Rva0022C560Call::*M0001c675)(Object*,const Coord3D*);
__forceinline M0001c675 m0001c675() {union {void (*raw)();M0001c675 method;} p; p.raw=j_0001c675;return p.method;}
typedef void (Rva0022C560Call::*M0001c882)(int);
__forceinline M0001c882 m0001c882() {union {void (*raw)();M0001c882 method;} p; p.raw=j_0001c882;return p.method;}
typedef bool (Rva0022C560Call::*M0001da34)(Object*,Player*);
__forceinline M0001da34 m0001da34() {union {void (*raw)();M0001da34 method;} p; p.raw=j_0001da34;return p.method;}
typedef Player* (Rva0022C560Call::*M00020824)();
__forceinline M00020824 m00020824() {union {void (*raw)();M00020824 method;} p; p.raw=j_00020824;return p.method;}
typedef void (Rva0022C560Call::*M0002191d)();
__forceinline M0002191d m0002191d() {union {void (*raw)();M0002191d method;} p; p.raw=j_0002191d;return p.method;}
typedef void (Rva0022C560Call::*M00024d70)(int);
__forceinline M00024d70 m00024d70() {union {void (*raw)();M00024d70 method;} p; p.raw=j_00024d70;return p.method;}
typedef float (Rva0022C560Call::*M00029f3c)(int,const Coord3D*,Coord3D*);
__forceinline M00029f3c m00029f3c() {union {void (*raw)();M00029f3c method;} p; p.raw=j_00029f3c;return p.method;}
typedef void* (Rva0022C560Call::*M0002ae23)(int);
__forceinline M0002ae23 m0002ae23() {union {void (*raw)();M0002ae23 method;} p; p.raw=j_0002ae23;return p.method;}
typedef bool (Rva0022C560Call::*M0003251f)(int);
__forceinline M0003251f m0003251f() {union {void (*raw)();M0003251f method;} p; p.raw=j_0003251f;return p.method;}
typedef void (Rva0022C560Call::*M00035e0e)(int);
__forceinline M00035e0e m00035e0e() {union {void (*raw)();M00035e0e method;} p; p.raw=j_00035e0e;return p.method;}
typedef void (Rva0022C560Call::*M000399A5)(float);
__forceinline M000399A5 m000399A5() {union {void (*raw)();M000399A5 method;} p; p.raw=j_000399A5;return p.method;}
typedef int (Rva0022C560Call::*M0003add7)(const char*);
__forceinline M0003add7 m0003add7() {union {void (*raw)();M0003add7 method;} p; p.raw=j_0003add7;return p.method;}
typedef const Coord3D* (Rva0022C560Call::*M00040246)();
__forceinline M00040246 m00040246() {union {void (*raw)();M00040246 method;} p; p.raw=j_00040246;return p.method;}
typedef void (Rva0022C560Call::*M00047690)(Object*,int);
__forceinline M00047690 m00047690() {union {void (*raw)();M00047690 method;} p; p.raw=j_00047690;return p.method;}
typedef bool (Rva0022C560Call::*M00048112)();
__forceinline M00048112 m00048112() {union {void (*raw)();M00048112 method;} p; p.raw=j_00048112;return p.method;}
typedef void (Rva0022C560Call::*M00023d49)(const Matrix3D*);
__forceinline M00023d49 m00023d49() {union {void (*raw)();M00023d49 method;} p; p.raw=j_00023d49;return p.method;}
inline void *pathfinder() {return *(void **)((char*)TheAI+12);}
inline unsigned frame() {return *(unsigned*)((char*)TheGameLogic+0x3c);}
inline Coord3D *pos(Object *o) {return &o->m_cachedPos;}
inline void *ai(Object *o) {return o->m_ai;}
inline void *cmd(void *a) {return (char*)a+0x20;}
__forceinline void setup(void *a,Object *o,Coord3D *p) {
 (((Rva0022C560Call*)(a))->*m0000315c())((Object*)0);
 *(unsigned*)((char*)a+0x178)=frame()+5;
 (((Rva0022C560Call*)(pathfinder()))->*m00011252())(o,(char*)a+0x1a8,p);
}
template<int N> class Rva0022C560Slots:public Rva0022C560Slots<N-1> {public: virtual void slot(char (*)[N]);};
template<> class Rva0022C560Slots<0> {};
class Rva0022C560Contain: public Rva0022C560Slots<36> {public: virtual void slot90(Object*,bool);};
class Rva0022C560 {
public:
 Object *owner() {return *(Object**)((char*)this-0x28);}
 void *data() {return *(void**)((char*)this-0x2c);}
 void remove(Object *o) {((Rva0022C560Contain*)((char*)this-0x10))->slot90(o,false);}
 void method(Object*,int);
};
void Rva0022C560::method(Object *out,int door)
{
 if(*(bool*)((char*)this+0xbc)) return;
 static int key=(((Rva0022C560Call*)(TheNameKeyGenerator))->*m0003add7())((const char*)"SiegeDeploySpecialPower");
 void *special=(((Rva0022C560Call*)(owner()))->*m0002ae23())(key);
 Object *me=owner();
 void *d=data();
 if((((Rva0022C560Call*)((char*)d+0x224))->*m0001da34())(out,(((Rva0022C560Call*)(me))->*m00020824())()) && *(int*)((char*)d+0x228)>0) {
    remove(out);
    Coord3D end;
    end.x=pos(out)->x;end.y=pos(out)->y;end.z=pos(out)->z;
    Coord3D delta;
    delta.x=end.x-pos(me)->x;
    delta.y=end.y-pos(me)->y;
    delta.z=end.z-pos(me)->z;
    delta.normalize();
    end.x+=delta.x*50.0f;
    end.y+=delta.y*50.0f;
    end.z=0;
    void *a=ai(out);
    (((Rva0022C560Call*)(pathfinder()))->*m0000b81b())(out);
    if(a) {
        setup(a,out,&end);
        std::vector<Coord3D> route;
        route.push_back(end); route.push_back(end);
        (((Rva0022C560Call*)(cmd(a)))->*m0001022b())(&route,me,2);
        union {void (*raw)(); void (Rva0022C560Call::*method)(Object*, const Coord3D*, int, const char*, int);} goal;
        goal.raw=j_000294e2;
        (((Rva0022C560Call*)pathfinder())->*goal.method)(out,&end,(((Rva0022C560Call*)(TheTerrainLogic))->*m0001c675())(out,&end),"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\SiegeEngineContain.cpp",210);
    }
    return;
 }
 if(special && (((Rva0022C560Call*)(special))->*m00048112())()) {
    remove(out);
    Object *me=owner();
    if((((Rva0022C560Call*)(me))->*m0003251f())(138)) {
        Coord3D loc; Matrix3D matrix;
        (((Rva0022C560Call*)(me))->*m00019f42())((const char*)"Ladder04",&loc,&matrix);
        if(out->m_modelConditionFlags[2]&0x80000000) {
            out->m_modelConditionFlags[2]&=0x7fffffff;
            (((Rva0022C560Call*)(out))->*m0002191d())();
        }
        (((Rva0022C560Call*)(out))->*m00023d49())(&matrix);
        (((Rva0022C560Call*)(out))->*m00035e0e())(17);
        void *a=ai(out);
        (((Rva0022C560Call*)(pathfinder()))->*m0000b81b())(out);
        if(a) {
            Player *p=(((Rva0022C560Call*)(out))->*m00020824())();
            if(*(int*)((char*)p+0x2c)==1) {
                (((Rva0022C560Call*)(a))->*m0000315c())((Object*)0);
                (((Rva0022C560Call*)(cmd(a)))->*m0001c882())(2);
            } else (((Rva0022C560Call*)(cmd(a)))->*m00024d70())(2);
        }
        return;
    }
    Coord3D loc=*pos(me);
    Coord2D direction;
    const Coord3D *v=(((Rva0022C560Call*)(me))->*m00040246())();
    direction.x=v->x; direction.y=v->y;
    float radius=((BfmeGeometryInfo*)&me->m_geometryInfo)->boxMajorRadius();
    loc.x+=direction.x*radius;loc.y+=direction.y*radius;
    loc.z=(((Rva0022C560Call*)(pathfinder()))->*m00029f3c())(17,&loc,(Coord3D*)0);
    Coord3D end=loc;
    loc.x+=direction.x*20.0f;loc.y+=direction.y*20.0f;
    end.x+=direction.x*40.0f;end.y+=direction.y*40.0f;
    (((Rva0022C560Call*)(out))->*m0001621b())(&loc,false);
    (((Rva0022C560Call*)(out))->*m000399A5())(me->m_cachedAngle);
    (((Rva0022C560Call*)(out))->*m00035e0e())(17);
    void *a=ai(out);
    (((Rva0022C560Call*)(pathfinder()))->*m0000b81b())(out);
    if(a) setup(a,out,&end);
    {
      std::vector<Coord3D> route;
      route.push_back(end);route.push_back(end);
      if(a) {
        (((Rva0022C560Call*)(cmd(a)))->*m0001022b())(&route,me,2);
        union {void (*raw)(); void (Rva0022C560Call::*method)(Object*, const Coord3D*, int, const char*, int);} goal;
        goal.raw=j_000294e2;
        (((Rva0022C560Call*)pathfinder())->*goal.method)(out,&end,(((Rva0022C560Call*)(TheTerrainLogic))->*m0001c675())(out,&end),"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\SiegeEngineContain.cpp",288);
      }
    }
    return;
 }
 (((Rva0022C560Call*)(this))->*m00047690())(out,door);
}
