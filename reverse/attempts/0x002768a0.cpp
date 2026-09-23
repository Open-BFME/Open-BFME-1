// ?doLocomotor@AIUpdateInterface@@MAE?AW4UpdateSleepTime@@XZ
// partial score=0.9745557350565428 date=2026-09-23
// stlport
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWMath
// Candidate only. Retail 002768A0. Identity: AIUpdateInterface table
// 010BA8A8 slot 133 -> ILT 00048D88 -> this body. Slots 134/135 are
// makeStateMachine/getTreatAsAircraftForLocoDistToGoal, in ZH declaration order.
// RET at +981; two 5-entry switch tables at +984/+998; end +9AC.
// See astra_O/LAYOUTS.md and callees1 for independent layout/callee evidence.
#include <math.h>
#include <bitset>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3DBase &v) { z=v.z; x=v.x; y=v.y; }
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &v) {
    struct Words { unsigned x,y,z; }; *(Words*)this=*(const Words*)&v; return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &v) { *(Coord3DBase*)this=v; return *this; }

// Existing ILT names retained, with signatures witnessed at the call sites
// and checked against the target bodies. No semantic callee pin is introduced.
struct Rva002768A0Override;
struct Rva002768A0Object;
struct Rva002768A0Locomotor;
struct Rva002768A0Path;
struct Rva002768A0Info { float at000; Coord3D at004,at010; int at01c,at020; };

extern void j_000022bb();
extern void j_00036a3e();
extern void j_000230ab();
extern void j_000179ef();
extern void j_0002fe0f();
extern void j_00003922();
extern void j_00014fba();
extern void j_0003a1a7();
extern void j_0001e6fa();
extern void j_0000ca68();
extern void j_00008a9e();
extern void j_0001c675();
extern void j_0000cb3f();
extern void j_0002ecad();
extern void j_00046ad3();
extern void j_00005ee3();
extern void j_0000e1c4();
extern void j_0002f66c();
extern void j_0004a327();
extern void j_0001a9dd();
extern void j_00035dd2();
extern void j_0002191d();
extern void j_00048e4b();
extern void j_00030d5f();
extern void j_00002b49();
extern void j_0000e52a();
extern void j_00004386();
extern void j_0003a391();
extern void j_00020eeb();
extern void j_00001c30();
extern void j_00032dee();
extern void j_00031f7a();
struct Rva002768A0Route {
    __forceinline Rva002768A0Override* r_000022bb() { typedef Rva002768A0Override*(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_000022bb}; return (this->*u.p)(); }
    __forceinline void r_00036a3e() { typedef void(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_00036a3e}; return (this->*u.p)(); }
    __forceinline float r_000230ab(Rva002768A0Object* a0) { typedef float(Rva002768A0Route::*P)(Rva002768A0Object*); union {void(*f)();P p;} u={j_000230ab}; return (this->*u.p)(a0); }
    __forceinline void r_000179ef(const Coord3D* a0) { typedef void(Rva002768A0Route::*P)(const Coord3D*); union {void(*f)();P p;} u={j_000179ef}; return (this->*u.p)(a0); }
    __forceinline float r_0002fe0f() { typedef float(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_0002fe0f}; return (this->*u.p)(); }
    __forceinline void r_00003922(Rva002768A0Object* a0, const Coord3D* a1, float a2, float a3, bool* a4) { typedef void(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*,float,float,bool*); union {void(*f)();P p;} u={j_00003922}; return (this->*u.p)(a0,a1,a2,a3,a4); }
    __forceinline bool r_00014fba(Rva002768A0Object* a0, const Coord3D* a1, const Coord3D* a2, const Coord3D* a3) { typedef bool(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*,const Coord3D*,const Coord3D*); union {void(*f)();P p;} u={j_00014fba}; return (this->*u.p)(a0,a1,a2,a3); }
    __forceinline void r_0003a1a7(const Coord3D* a0) { typedef void(Rva002768A0Route::*P)(const Coord3D*); union {void(*f)();P p;} u={j_0003a1a7}; return (this->*u.p)(a0); }
    __forceinline Rva002768A0Path* r_0001e6fa(Rva002768A0Object* a0, const Coord3D* a1) { typedef Rva002768A0Path*(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*); union {void(*f)();P p;} u={j_0001e6fa}; return (this->*u.p)(a0,a1); }
    __forceinline void r_0000ca68() { typedef void(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_0000ca68}; return (this->*u.p)(); }
    __forceinline void r_00008a9e(Rva002768A0Object* a0, Rva002768A0Locomotor* a1, Rva002768A0Info* a2, bool a3) { typedef void(Rva002768A0Route::*P)(Rva002768A0Object*,Rva002768A0Locomotor*,Rva002768A0Info*,bool); union {void(*f)();P p;} u={j_00008a9e}; return (this->*u.p)(a0,a1,a2,a3); }
    __forceinline int r_0001c675(Rva002768A0Object* a0, const Coord3D* a1) { typedef int(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*); union {void(*f)();P p;} u={j_0001c675}; return (this->*u.p)(a0,a1); }
    __forceinline void r_0000cb3f(int a0) { typedef void(Rva002768A0Route::*P)(int); union {void(*f)();P p;} u={j_0000cb3f}; return (this->*u.p)(a0); }
    __forceinline float r_0002ecad() { typedef float(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_0002ecad}; return (this->*u.p)(); }
    __forceinline bool r_00046ad3(Rva002768A0Object* a0) { typedef bool(Rva002768A0Route::*P)(Rva002768A0Object*); union {void(*f)();P p;} u={j_00046ad3}; return (this->*u.p)(a0); }
    __forceinline void r_00005ee3(Coord3D* a0) { typedef void(Rva002768A0Route::*P)(Coord3D*); union {void(*f)();P p;} u={j_00005ee3}; return (this->*u.p)(a0); }
    __forceinline void r_0000e1c4(float a0) { typedef void(Rva002768A0Route::*P)(float); union {void(*f)();P p;} u={j_0000e1c4}; return (this->*u.p)(a0); }
    __forceinline void r_0002f66c(const Coord3D* a0) { typedef void(Rva002768A0Route::*P)(const Coord3D*); union {void(*f)();P p;} u={j_0002f66c}; return (this->*u.p)(a0); }
    __forceinline bool r_0004a327(Rva002768A0Object* a0, const Coord3D* a1, const Coord3D* a2, void* a3) { typedef bool(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*,const Coord3D*,void*); union {void(*f)();P p;} u={j_0004a327}; return (this->*u.p)(a0,a1,a2,a3); }
    __forceinline void r_0001a9dd(void* a0) { typedef void(Rva002768A0Route::*P)(void*); union {void(*f)();P p;} u={j_0001a9dd}; return (this->*u.p)(a0); }
    __forceinline void r_00035dd2(Rva002768A0Object* a0, int a1) { typedef void(Rva002768A0Route::*P)(Rva002768A0Object*,int); union {void(*f)();P p;} u={j_00035dd2}; return (this->*u.p)(a0,a1); }
    __forceinline void r_0002191d() { typedef void(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_0002191d}; return (this->*u.p)(); }
    __forceinline int r_00048e4b() { typedef int(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_00048e4b}; return (this->*u.p)(); }
    __forceinline void r_00030d5f(float a0, Rva002768A0Object* a1) { typedef void(Rva002768A0Route::*P)(float,Rva002768A0Object*); union {void(*f)();P p;} u={j_00030d5f}; return (this->*u.p)(a0,a1); }
    __forceinline void r_00002b49(Rva002768A0Object* a0, const Coord3D* a1, int a2) { typedef void(Rva002768A0Route::*P)(Rva002768A0Object*,const Coord3D*,int); union {void(*f)();P p;} u={j_00002b49}; return (this->*u.p)(a0,a1,a2); }
    __forceinline void r_0000e52a(Rva002768A0Object* a0, float a1) { typedef void(Rva002768A0Route::*P)(Rva002768A0Object*,float); union {void(*f)();P p;} u={j_0000e52a}; return (this->*u.p)(a0,a1); }
    __forceinline bool r_00004386() { typedef bool(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_00004386}; return (this->*u.p)(); }
    __forceinline int r_0003a391() { typedef int(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_0003a391}; return (this->*u.p)(); }
    __forceinline bool r_00020eeb(Rva002768A0Object* a0) { typedef bool(Rva002768A0Route::*P)(Rva002768A0Object*); union {void(*f)();P p;} u={j_00020eeb}; return (this->*u.p)(a0); }
    __forceinline float r_00001c30() { typedef float(Rva002768A0Route::*P)(); union {void(*f)();P p;} u={j_00001c30}; return (this->*u.p)(); }
    __forceinline void r_00032dee(int a0, bool a1) { typedef void(Rva002768A0Route::*P)(int,bool); union {void(*f)();P p;} u={j_00032dee}; return (this->*u.p)(a0,a1); }
    __forceinline void r_00031f7a(int a0) { typedef void(Rva002768A0Route::*P)(int); union {void(*f)();P p;} u={j_00031f7a}; return (this->*u.p)(a0); }
};
struct Rva002768A0Override {
    unsigned at000; Rva002768A0Override *at004;
    char pad008[0xbc-8]; int at0bc;
    char pad0c0[8]; unsigned at0c8; bool at0cc;
};
inline Rva002768A0Override *last(Rva002768A0Override *const &o) {
    if(o && o->at004) return ((Rva002768A0Route*)(o->at004))->r_000022bb(); return o;
}
struct Rva002768A0Object {
    unsigned at000; Rva002768A0Override *at004;
    char pad008[0x38-8]; Coord3D at038;
    char pad044[0x110-0x44]; _STL::bitset<320> at110;
    void clear(int bit) {
        if(at110.test(bit)) { at110.set(bit,0); ((Rva002768A0Route*)(this))->r_0002191d(); }
    }
    void set(int bit) {
        if(!at110.test(bit)) { at110.set(bit); ((Rva002768A0Route*)(this))->r_0002191d(); }
    }
};
struct Rva002768A0Locomotor { unsigned at000; Rva002768A0Override *at004; };
struct Rva002768A0Path { ~Rva002768A0Path() { ((Rva002768A0Route*)(this))->r_0000ca68(); } };
struct Rva002768A0AI { char pad000[12]; void *at00c; };
enum Rva002768A0BridgeMode { Rva002768A0Mode0, Rva002768A0Mode1, Rva002768A0Mode2, Rva002768A0Mode3, Rva002768A0Mode4 };
struct Rva002768A0Bridge { char pad000[0x60]; Rva002768A0BridgeMode at060; };
template<int N> class Rva002768A0Slots:public Rva002768A0Slots<N-1> { public: virtual void slot(char(*)[N])=0; };
template<> class Rva002768A0Slots<0> {};
class Rva002768A0Terrain:public Rva002768A0Slots<6> {
public:
    virtual float slot018(float,float,void*)=0;
    virtual void slot01c()=0; virtual void slot020()=0; virtual void slot024()=0;
    virtual void slot028()=0; virtual void slot02c()=0; virtual void slot030()=0;
    virtual void slot034()=0; virtual void slot038()=0; virtual void slot03c()=0;
    virtual void slot040()=0; virtual void slot044()=0; virtual void slot048()=0;
    virtual void slot04c()=0; virtual void slot050()=0; virtual void slot054()=0;
    virtual void slot058()=0; virtual void slot05c()=0; virtual void slot060()=0;
    virtual void slot064()=0; virtual void slot068()=0; virtual void slot06c()=0;
    virtual void slot070()=0; virtual void slot074()=0; virtual void slot078()=0;
    virtual void slot07c()=0; virtual Rva002768A0Bridge *slot080(int)=0;
};
extern Rva002768A0AI *g_Rva002768A0AI;
extern Rva002768A0Terrain *g_Rva002768A0Terrain;
enum UpdateSleepTime { RVA002768A0_NONE=1, RVA002768A0_FOREVER=0x3fffffff };
// The available ZH AIUpdate header has incompatible BFME storage offsets.
// This TU declares only independently witnessed storage and virtual slots.
class AIUpdateInterface:public Rva002768A0Slots<123> {
public:
    virtual bool isDoingGroundMovement() const=0;
    char pad004[4]; Rva002768A0Object *at008;
    char pad00c[0x44-12]; float at044;
    char pad048[0x140-0x48]; Rva002768A0Path *m_path;
    char pad144[0x168-0x144]; float m_pathExtraDistance;
    int m_blockedFrames; float at170,at174;
    unsigned m_ignoreCollisionsUntil,m_queueForPathFrame;
    Coord3D at180;
    char pad18c[0x1cc-0x18c]; Rva002768A0Locomotor *m_curLocomotor;
    char pad1d0[8]; int at1d8; Coord3D at1dc;
    char pad1e8[0x248-0x1e8]; char at248[0x31d-0x248];
    bool at31d,at31e; char pad31f[6]; bool m_isBlocked;
    char pad326[3]; bool at329; char pad32a; bool m_isAiDead;
    protected:
    virtual UpdateSleepTime doLocomotor();
};

UpdateSleepTime AIUpdateInterface::doLocomotor() {
    typedef void(Rva002768A0Route::*Move)(Rva002768A0Object*,const Coord3D&,float,float,bool*);
    union { void(*raw)(); Move method; } moveRoute={j_00003922};
    Rva002768A0Object *o=at008;
    if(last(o->at004)->at0c8&4) return RVA002768A0_FOREVER;
    ((Rva002768A0Route*)(this))->r_00036a3e();
    if(m_isBlocked) ++m_blockedFrames; else m_blockedFrames=0;
    m_isBlocked=false;
    bool blocked=m_blockedFrames>0;
    bool constant=true;
    Rva002768A0Locomotor *initial=m_curLocomotor;
    if(initial) {
        if(!m_isAiDead || last(initial->at004)->at0cc) {
            switch(at1d8) {
            case 2: case 4: {
                float speed=at044;
                float maxSpeed=((Rva002768A0Route*)(initial))->r_000230ab(o);
                if(speed==999999.0f || speed>maxSpeed) speed=maxSpeed;
                Coord3D old=o->at038;
                Coord3D pos=old;
                ((Rva002768A0Route*)(&pos))->r_000179ef(&at1dc);
                (((Rva002768A0Route*)m_curLocomotor)->*moveRoute.method)(o,at1dc,pos.length()+m_pathExtraDistance,speed,&blocked);
                if(at1d8==4 && !((Rva002768A0Route*)(g_Rva002768A0AI->at00c))->r_00014fba(o,&old,&o->at038,&at1dc)) {
                    ((Rva002768A0Route*)(o))->r_0003a1a7(&old);
                    if(!m_path) {
                        m_path=((Rva002768A0Route*)(g_Rva002768A0AI->at00c))->r_0001e6fa(o,&at1dc);
                        if(!m_path) ((Rva002768A0Route*)(o))->r_0003a1a7(&at1dc);
                    }
                } else if(m_path) { delete m_path; m_path=0; }
                if(at1d8==4 && m_path) {
                    Rva002768A0Info info;
                    ((Rva002768A0Route*)(m_path))->r_00008a9e(o,m_curLocomotor,&info,true);
                    (((Rva002768A0Route*)m_curLocomotor)->*moveRoute.method)(o,info.at004,info.at000+m_pathExtraDistance,speed,&blocked);
                }
                ((Rva002768A0Route*)(o))->r_0000cb3f(((Rva002768A0Route*)(g_Rva002768A0Terrain))->r_0001c675(o,&o->at038));
                at31d=false;
                break;
            }
            case 1: {
                if(!m_path) {
                    if(at31e) {
                        float speed=((Rva002768A0Route*)(initial))->r_0002ecad();
                        if(((Rva002768A0Route*)(m_curLocomotor))->r_00046ad3(o) && m_queueForPathFrame==0) {
                            Coord3D pos;
                            ((Rva002768A0Route*)(o))->r_00005ee3(&pos);
                            ((Rva002768A0Route*)(&pos))->r_0000e1c4(speed*2);
                            ((Rva002768A0Route*)(&pos))->r_0002f66c(&o->at038);
                            if(((Rva002768A0Route*)(g_Rva002768A0AI->at00c))->r_0004a327(o,&o->at038,&pos,0))
                                (((Rva002768A0Route*)m_curLocomotor)->*moveRoute.method)(o,pos,999999.0f,speed,&blocked);
                            ((Rva002768A0Route*)(o))->r_0001a9dd(at248);
                        }
                        return RVA002768A0_FOREVER;
                    }
                    break;
                }
                Coord3D goal;
                float distance;
                Rva002768A0Bridge *bridge=0;
                if(!isDoingGroundMovement()) {
                    Rva002768A0Info info;
                    ((Rva002768A0Route*)(m_path))->r_00008a9e(o,m_curLocomotor,&info,false);
                    distance=info.at000; goal=info.at004;
                } else {
                    Rva002768A0Info info;
                    ((Rva002768A0Route*)(m_path))->r_00008a9e(o,m_curLocomotor,&info,false);
                    distance=info.at000; goal=info.at004;
                    if(info.at020!=0x7fffffff) bridge=g_Rva002768A0Terrain->slot080(info.at020);
                    if(!bridge) ((Rva002768A0Route*)(g_Rva002768A0AI->at00c))->r_00035dd2(o,info.at01c);
                }
                at329=bridge!=0;
                float speed=at044;
                float maxSpeed=((Rva002768A0Route*)(m_curLocomotor))->r_000230ab(o);
                if(speed==999999.0f || speed>maxSpeed) speed=maxSpeed;
                if(blocked && speed>at170) {
                    speed=at170;
                    if(at174>speed) at174=speed;
                    at174*=0.95f; speed=at174;
                } else {
                    blocked=false;
                    if(at174<999999.0f) {
                        if(at174<speed*0.3f) at174=speed*0.3f;
                        at174*=1.4f;
                    }
                    if(speed>at174) speed=at174;
                }
                o->clear(102);
                Rva002768A0Locomotor *loco=m_curLocomotor;
                if(((Rva002768A0Route*)(loco))->r_00048e4b()!=6 && bridge) {
                    ((Rva002768A0Route*)(loco))->r_00030d5f(speed,o);
                    Rva002768A0Info info;
                    ((Rva002768A0Route*)(m_path))->r_00008a9e(o,m_curLocomotor,&info,true);
                    Coord3D delta=info.at004;
                    ((Rva002768A0Route*)(&delta))->r_000179ef(&o->at038);
                    switch(bridge->at060) {
                    case 0: goto bridgeLayer;
                    case 2: case 4:
                        o->clear(127); o->clear(128); o->set(123);
                        ((Rva002768A0Route*)(m_curLocomotor))->r_00002b49(o,&info.at004,0);
                        ((Rva002768A0Route*)(o))->r_0003a1a7(&info.at004);
                        break;
                    case 3:
                        o->clear(127); o->clear(128); o->clear(102); o->set(123);
                        if(delta.z<delta.length()*-0.5f) {
                            delta.x=o->at038.x*2-info.at004.x;
                            delta.y=o->at038.y*2-info.at004.y;
                            delta.z=goal.z;
                            ((Rva002768A0Route*)(m_curLocomotor))->r_00002b49(o,&delta,0);
                            o->set(146); o->set(102);
                        } else {
                            if(delta.z>delta.length()*0.5f) o->set(102);
                            ((Rva002768A0Route*)(m_curLocomotor))->r_00002b49(o,&info.at004,0);
                        }
                    case 1:
                        ((Rva002768A0Route*)(o))->r_0003a1a7(&info.at004); break;
                    }
bridgeLayer:
                    ((Rva002768A0Route*)(o))->r_0000cb3f(info.at01c);
                } else {
                    o->clear(146);
                    (((Rva002768A0Route*)m_curLocomotor)->*moveRoute.method)(o,goal,distance+m_pathExtraDistance,speed,&blocked);
                }
                at31d=false; break;
            }
            case 3:
                ((Rva002768A0Route*)(initial))->r_0000e52a(o,at1dc.x); at31d=false; break;
            case 0:
                if(at31d) {
                    Coord3D pos((const Coord3DBase&)o->at038);
                    bool ground=!((Rva002768A0Route*)(o))->r_00004386() && ((Rva002768A0Route*)(o))->r_0003a391()==1;
                    float dx=at180.x-pos.x,dy=at180.y-pos.y;
                    float squared=dx*dx+dy*dy;
                    if(squared<0.25f) {
                        at31d=false;
                        if(ground) at180.z=g_Rva002768A0Terrain->slot018(at180.x,at180.y,0);
                        else at180.z=pos.z;
                        ((Rva002768A0Route*)(o))->r_0003a1a7(&at180);
                    } else {
                        float distance=sqrtf(squared);
                        if(distance<1) distance=1;
                        pos.x+=20.0f*dx/(distance*5.0f);
                        pos.y+=20.0f*dy/(distance*5.0f);
                        if(ground) pos.z=g_Rva002768A0Terrain->slot018(pos.x,pos.y,0);
                        ((Rva002768A0Route*)(o))->r_0003a1a7(&pos);
                    }
                }
                constant=((Rva002768A0Route*)(m_curLocomotor))->r_00020eeb(o); break;
            }
        }
        if(!blocked && m_blockedFrames>1) m_blockedFrames=1;
        int height=last(m_curLocomotor->at004)->at0bc;
        if(((Rva002768A0Route*)(o))->r_00001c30()>height) ((Rva002768A0Route*)(o))->r_00032dee(6,true);
        else ((Rva002768A0Route*)(o))->r_00031f7a(6);
        at170=999999.0f;
    }
    if(m_curLocomotor && at1d8==0 && !at31d && !m_isBlocked && !constant) return RVA002768A0_FOREVER;
    return RVA002768A0_NONE;
}
