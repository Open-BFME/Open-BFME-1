// ?onEnter@AIAttackMeleeApproachState@@UAE?AW4StateReturnType@@XZ
// partial score=0.992 date=2026-09-23
// cl: /Ob1 /ICode/Libraries/Source/WWVegas/WWMath
// Retail 00176F70, 747 bytes. AIAttackMeleeApproachState::onEnter is
// supported by vtable 0x0109A6C0 slot 4, its matched deleting destructor,
// and the matched AttackMeleeStateMachine constructor which creates it.
// Hub ABI from docs/analysis/0x00172600.md. All calls use decoded ILT routes.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
__forceinline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {
    struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&p; return *this;
}
__forceinline Coord3D &Coord3D::operator=(const Coord3D &p) { Coord3DBase *base=this; *base=p; return *this; }
inline Coord3D::Coord3D(float a,float b,float c) {x=a; y=b; z=c;}
inline Coord3D::Coord3D(const Coord3D &p) {x=p.x; y=p.y; z=p.z;}
inline Coord3D &Coord3D::Sub2D(const Coord3DBase &p) {x-=p.x; y-=p.y; return *this;}
typedef unsigned char Byte;
template<class T> __forceinline T &at(void *p, int offset) { return *(T*)((char*)p+offset); }
template<int N> struct Slots : Slots<N-1> { virtual void unused(char(*)[N])=0; };
template<> struct Slots<0> {};
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
struct State : Slots<4> {
    virtual StateReturnType onEnter()=0;
    virtual void slot05()=0; virtual void slot06()=0; virtual void slot07()=0;
    virtual void slot08()=0; virtual void slot09()=0; virtual void slot10()=0;
    virtual void slot11()=0; virtual void slot12()=0; virtual void slot13()=0;
    virtual void slot14()=0; virtual void slot15()=0; virtual void slot16()=0;
    Byte pad04[0x18]; void *m_machine;
};
struct AIInternalMoveToState : State {
    virtual StateReturnType onEnter();
    virtual bool computePath()=0;
    Byte pad20[4]; Coord3D m_goalPosition;
    Byte pad30[4]; Coord3D m_pathGoalPosition;
    Byte pad40[4]; unsigned m_pathTimestamp; unsigned m_blockedRepathTimestamp;
    bool m_adjustDestinations; Byte m_waitingForPath; Byte m_tryOneMoreRepath;
    Byte pad4f;
};
struct MachineSlot38 : Slots<14> { virtual void slot38(void*)=0; };
struct MachineSlot20 : Slots<8> { virtual void slot20(int)=0; };
struct AIAttackMeleeApproachState : AIInternalMoveToState {
    int field50; Coord3D previous54;
    virtual StateReturnType onEnter();
};
extern void *g_012EF214;
extern void *g_012ED4FC;
extern bool g_012F0239;
struct Calls00176F70 {
    bool rva0000432c(); void *rva0000e570(); void *rva00020824(); bool rva00003b1b(void*);
    bool rva000420aa(void*,int); bool rva00016199(); bool rva00006eec();
    void *rva00031a7f(void*); bool rva0002e85c(void*,void*,int);
    bool rva000016a4(int); void rva000065e1(); int rva00021e27();
};
#define C(p) ((Calls00176F70*)(p))
extern void j_0003a17a();
extern void j_00004c37();
typedef void (__cdecl *Log)(void*,const char*,...);
typedef bool (__cdecl *PairQuery)(void*,void*);
StateReturnType AIAttackMeleeApproachState::onEnter() {
    void *source=at<void*>(m_machine,0x10);
    if (C(m_machine)->rva0000432c()) return STATE_FAILURE;
    void *victim=C(m_machine)->rva0000e570();
    if (victim && C(victim)->rva00003b1b(C(source)->rva00020824())) {
        ((MachineSlot38*)m_machine)->slot38(0);
        return STATE_FAILURE;
    }
    if ((at<unsigned>(source,0x98)&8) || at<Byte>(at<void*>(source,0x204),0x33a)) {
        if (!((PairQuery)j_00004c37)(source,victim)) {
            ((MachineSlot38*)m_machine)->slot38(0);
            return STATE_FAILURE;
        }
        if (at<Byte>(at<void*>(source,0x204),0x33a)) {
            void *weapon=C(source)->rva00031a7f(0);
            if (!weapon || !C(weapon)->rva0002e85c(source,victim,0)) {
                ((MachineSlot38*)m_machine)->slot38(0);
                return STATE_FAILURE;
            }
        }
        return STATE_SUCCESS;
    }
    if (g_012F0239 && g_012ED4FC) ((Log)j_0003a17a)(g_012ED4FC,"CritterDesync: setAdjustDestination(FALSE) 31");
    m_adjustDestinations=false;
    field50=0;
    if (!victim) return STATE_FAILURE;
    if (C(source)->rva000420aa(victim,2) && C(source)->rva00016199()) {
        ((MachineSlot20*)m_machine)->slot20(233);
        return STATE_CONTINUE;
    }
    void *physics=at<void*>(victim,0x208);
    if (physics && C(physics)->rva00006eec()) return STATE_FAILURE;
    void *weapon=C(source)->rva00031a7f(0);
    if (!weapon) return STATE_FAILURE;
    if (C(weapon)->rva0002e85c(source,victim,0)) return STATE_SUCCESS;
    previous54=at<Coord3D>(victim,0x38);
    if (!C(source)->rva000420aa(victim,2)) {
        void *data=at<void*>(g_012EF214,0x14);
        Coord3D delta(at<Coord3D>(source,0x38));
        delta.Sub2D(previous54);
        delta.z=0.0f;
        if (delta.length()<at<float>(data,0x94)+at<float>(data,0x90)) return STATE_SUCCESS;
    }
    if (C(source)->rva000016a4(37) && at<void*>(source,0x214)) return STATE_FAILURE;
    C(at<void*>(source,0x204))->rva000065e1();
    previous54=at<Coord3D>(victim,0x38);
    {
        void *data=at<void*>(g_012EF214,0x14);
        Coord3D delta(at<Coord3D>(source,0x38));
        delta.Sub2D(previous54);
        delta.z=0.0f;
        if (delta.length()<at<float>(data,0x94)+at<float>(data,0x90)) return STATE_SUCCESS;
    }
    if (g_012F0239 && g_012ED4FC) ((Log)j_0003a17a)(g_012ED4FC,"CritterDesync: ComputePath19");
    if (!computePath()) return STATE_SUCCESS;
    StateReturnType result=AIInternalMoveToState::onEnter();
    if (g_012F0239 && g_012ED4FC) ((Log)j_0003a17a)(g_012ED4FC,"CritterDesync: setAdjustDestination(TRUE) 32");
    m_adjustDestinations=true;
    return result;
}
#pragma comment(linker, "/alternatename:?length@Coord3D@@QBEMXZ=?j_0002fe0f@@YAXXZ")

#pragma comment(linker, "/alternatename:?rva00021e27@Calls00176F70@@QAEHXZ=?j_00021e27@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000065e1@Calls00176F70@@QAEXXZ=?j_000065e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000016a4@Calls00176F70@@QAE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002e85c@Calls00176F70@@QAE_NPAX0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00031a7f@Calls00176F70@@QAEPAXPAX@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00006eec@Calls00176F70@@QAE_NXZ=?j_00006eec@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00016199@Calls00176F70@@QAE_NXZ=?j_00016199@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000420aa@Calls00176F70@@QAE_NPAXH@Z=?j_000420aa@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00003b1b@Calls00176F70@@QAE_NPAX@Z=?j_00003b1b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00020824@Calls00176F70@@QAEPAXXZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000e570@Calls00176F70@@QAEPAXXZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000432c@Calls00176F70@@QAE_NXZ=?j_0000432c@@YAXXZ")
