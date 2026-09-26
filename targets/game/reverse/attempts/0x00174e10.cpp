// ?d_00174e10@@YAXXZ
// partial score=0.26021798365122617 date=2026-09-22
// cl: /Ob1 /ICode/Libraries/Source/WWVegas/WWMath
// Retail RVA 00174E10, 734 bytes. Opaque state view: no class identity claim.
// Full control flow from retail; hub contract docs/analysis/0x00172600.md.
// Helpers 0016B010 and 00174CC0 are visible static C++ for compiler-private ABI.
// Their emitted ABI must also be checked before landing this caller.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {
    struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&p; return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &p) { Coord3DBase *base=this; *base=p; return *this; }
typedef unsigned char Byte;
template<class T> __forceinline T &at(void *p, int offset) { return *(T*)((char*)p+offset); }
template<int N> struct Slots : Slots<N-1> { virtual void unused(char(*)[N])=0; };
template<> struct Slots<0> {};
struct GroundSlot : Slots<123> { virtual bool slot1ec()=0; };
struct CommandSlot : Slots<128> { virtual int slot200()=0; };
struct MachineSlot : Slots<14> { virtual void slot38(void*)=0; };
struct ApproachEntry00174E10 : Slots<17> {
    virtual bool slot44()=0;
    Byte pad04[0x18]; void *machine; Byte pad20[4]; Coord3D goal;
    Byte pad30[0x1c]; bool adjust4c; Byte pad4d[3]; Coord3D previous50;
    Coord3D position5c; int timestamp68; unsigned wait6c;
    Byte field70; bool object71; Byte field72; Byte field73; bool force74; bool wait75;
    int enter();
};
extern void *g_012EF214;
extern void *g_012F0898;
extern void *g_012ED4FC;
extern bool g_012F0239;
extern float g_01075C70;
extern float g_01075350;
struct Calls00174E10 {
    void *rva000022bb(); bool rva0000432c(); void *rva00031a7f(void*);
    void *rva0000e570(); bool rva0002e85c(void*,void*,int); bool rva00019ff1();
    bool rva00023042(void*,const Coord3D*,void*,const Coord3D*);
    int rva0003a391(); bool rva00018eb2(const Coord3D*); bool rva000016a4(int);
    bool rva00017607(); float rva000230ab(void*); int rva000346a3();
    void rva0001a0e1(int,void*,bool); void rva000331bd(int,const Coord3D*);
    int rva00021e27(); void *rva00009c41(int); bool rva00028f74(); bool rva0000ccd4();
    void *rva00020824(); bool rva000420aa(void*,int); bool rva0000e7dc(void*,void*);
    float rva0003daa5(); float rva000047c8(); const Coord3D *rva00040246();
};
#define C(p) ((Calls00174E10*)(p))
extern void j_0003a17a();
extern void j_00004c37();
typedef void (__cdecl *Log)(void*,const char*,...);
typedef bool (__cdecl *PairQuery)(void*,void*);
static __declspec(noinline) bool permitted0016B010(void *source) {
    void *weapon = C(source)->rva00009c41(0);
    if (weapon && (C(at<void*>(weapon,4))->rva00028f74() || C(at<void*>(weapon,4))->rva0000ccd4())) return true;
    void *player = C(source)->rva00020824();
    if (at<int>(player,0x2c)!=0) return true;
    void *ai = at<void*>(source,0x204);
    if (!ai) return true;
    void *state = at<void*>(at<void*>(ai,0x30),0x1c);
    if (state && at<int>(state,4)==0x3e) return true;
    if (((CommandSlot*)ai)->slot200()!=2 || at<Byte>(ai,0x32f) || at<Byte>(source,0x1f5)) return true;
    return false;
}
static __declspec(noinline) bool pursue00174CC0(void *source,void *weapon,void *victim) {
    if (!at<void*>(victim,0x208)) return false;
    if ((at<unsigned>(source,0x94)&0x20) && at<void*>(source,0x214)) return false;
    void *ai = at<void*>(source,0x204);
    if (!ai || C(ai)->rva000346a3()==-1) return false;
    if (at<Byte>(at<void*>(g_012EF214,0x14),0x8c) && C(source)->rva00020824() &&
        at<int>(C(source)->rva00020824(),0x2c)==1 && C(source)->rva000420aa(victim,2)) return true;
    if (C(weapon)->rva0000e7dc(source,victim)) return false;
    float ours = C(at<void*>(source,0x204))->rva0003daa5();
    float theirs = C(victim)->rva000047c8();
    if (theirs >= ours) return false;
    if (theirs < ours*g_01075C70) return false;
    float dx = at<float>(victim,0x38)-at<float>(source,0x38);
    float dy = at<float>(victim,0x3c)-at<float>(source,0x3c);
    const Coord3D *direction = C(victim)->rva00040246();
    if (dx*direction->x+dy*direction->y < g_01075350) return false;
    return true;
}
int ApproachEntry00174E10::enter() {
    void *source = at<void*>(machine,0x10);
    void *ai = at<void*>(source,0x204);
    void *templ = at<void*>(source,4);
    if (!templ) templ=0;
    else if (at<void*>(templ,4)) templ=C(at<void*>(templ,4))->rva000022bb();
    if (at<unsigned>(templ,0xc8)&0x02000000) {
        void *loco = at<void*>(ai,0x1cc);
        if (loco) at<unsigned>(loco,0x40)|=8;
    }
    position5c = at<Coord3D>(source,0x38);
    if (C(machine)->rva0000432c()) return -1;
    wait75=false;
    if ((at<unsigned>(source,0x98)&8) || at<Byte>(ai,0x33a)) {
        if (((PairQuery)j_00004c37)(source,C(machine)->rva0000e570())) return -1;
        ((MachineSlot*)machine)->slot38(0);
        return -2;
    }
    previous50.x=0; previous50.y=0; previous50.z=0; timestamp68=-5;
    void *weapon=C(source)->rva00031a7f(0);
    void *victim=C(machine)->rva0000e570();
    if (victim) {
        if (!weapon) return -2;
        if (C(weapon)->rva0002e85c(source,victim,0)) {
            if (!((GroundSlot*)ai)->slot1ec() || C(victim)->rva00019ff1() ||
                !C(at<void*>(g_012EF214,0x0c))->rva00023042(source,&at<Coord3D>(source,0x38),victim,&at<Coord3D>(victim,0x38))) return -1;
        }
        if (!permitted0016B010(source)) return -2;
        if (pursue00174CC0(source,weapon,victim)) return -1;
        if (at<Byte>(at<void*>(ai,4),0x28) && C(source)->rva0003a391()>=17 &&
            !C(ai)->rva00018eb2(&at<Coord3D>(victim,0x38))) goto wait;
    } else {
        if (!weapon || !at<Byte>(at<void*>(weapon,4),0x533)) return -2;
    }
    if (C(source)->rva000016a4(37) && at<void*>(source,0x214)) return -2;
    {
        bool mobile=true;
        if (!C(source)->rva00017607()) mobile=false;
        if (C(at<void*>(ai,0x1cc))->rva000230ab(source)<g_01075C70 || !mobile) goto wait;
    }
    {
        int turret=C(ai)->rva000346a3();
        if (turret!=-1) {
            if (object71) C(ai)->rva0001a0e1(turret,victim,force74);
            else C(ai)->rva000331bd(turret,&at<Coord3D>(machine,0x24));
        }
    }
    if (!slot44()) return -2;
    if (wait75) return 0;
    if (g_012F0239 && g_012ED4FC) ((Log)j_0003a17a)(g_012ED4FC,"CritterDesync: setAdjustDestination(FALSE) 21");
    adjust4c=false;
    {
        int result=C(this)->rva00021e27();
        if (g_012F0239 && g_012ED4FC) ((Log)j_0003a17a)(g_012ED4FC,"CritterDesync: setAdjustDestination(TRUE) 22");
        adjust4c=true;
        return result;
    }
wait:
    wait75=true;
    wait6c=at<unsigned>(g_012F0898,0x3c)+10;
    return 0;
}

#pragma comment(linker, "/alternatename:?rva00020824@Calls00174E10@@QAEPAXXZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000ccd4@Calls00174E10@@QAE_NXZ=?j_0000ccd4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00028f74@Calls00174E10@@QAE_NXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00009c41@Calls00174E10@@QAEPAXH@Z=?j_00009c41@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00040246@Calls00174E10@@QAEPBVCoord3D@@XZ=?j_00040246@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000047c8@Calls00174E10@@QAEMXZ=?j_000047c8@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003daa5@Calls00174E10@@QAEMXZ=?j_0003daa5@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000e7dc@Calls00174E10@@QAE_NPAX0@Z=?j_0000e7dc@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000420aa@Calls00174E10@@QAE_NPAXH@Z=?j_000420aa@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000346a3@Calls00174E10@@QAEHXZ=?j_000346a3@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00021e27@Calls00174E10@@QAEHXZ=?j_00021e27@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000331bd@Calls00174E10@@QAEXHPBVCoord3D@@@Z=?j_000331bd@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001a0e1@Calls00174E10@@QAEXHPAX_N@Z=?j_0001a0e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000230ab@Calls00174E10@@QAEMPAX@Z=?j_000230ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00017607@Calls00174E10@@QAE_NXZ=?j_00017607@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000016a4@Calls00174E10@@QAE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00018eb2@Calls00174E10@@QAE_NPBVCoord3D@@@Z=?j_00018eb2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003a391@Calls00174E10@@QAEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00023042@Calls00174E10@@QAE_NPAXPBVCoord3D@@01@Z=?j_00023042@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00019ff1@Calls00174E10@@QAE_NXZ=?j_00019ff1@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002e85c@Calls00174E10@@QAE_NPAX0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000e570@Calls00174E10@@QAEPAXXZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00031a7f@Calls00174E10@@QAEPAXPAX@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000432c@Calls00174E10@@QAE_NXZ=?j_0000432c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000022bb@Calls00174E10@@QAEPAXXZ=?j_000022bb@@YAXXZ")
