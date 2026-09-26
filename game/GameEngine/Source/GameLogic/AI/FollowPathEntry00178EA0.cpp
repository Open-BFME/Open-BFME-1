// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
// RVA 00178EA0: path entry, ported from ZH AIFollowPathState::onEnter.
// Opaque receiver until the complete owning vtable identity is established.
// Layouts and hub ABI: docs/analysis/0x00172600.md.
// RET at +0x1CE; two local dwords; all eight calls retain retail order.
// Path lookup uses the landed 0016FFD0 vector accessor shape. The first two
// indices are 0 and 1 before any external call. Later lookup reloads state+50.
// Setter 0026FE90 accepts a float payload and returns with RET4. Kind predicate
// 000A2CF0 accepts ordinal25 and returns AL. Hub 00172600 returns EAX, RET0.
// 40.0f independently read from retail VA01096C50; log strings are byte checked.
#include <math.h>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::operator=(const Coord3D &c) {
    struct Words { unsigned x,y,z; };
    *(Words*)this=*(const Words*)&c; return *this;
}
template<class T> struct PathVector00178EA0 {
    T *start; T *finish;
    T *begin() { return start; }
    const T *begin() const { return start; }
    unsigned size() const { return unsigned(finish-start); }
    const T &operator[](unsigned i) const { return *(begin()+i); }
};
extern bool gFollowPathEntry00178EA0Debug;
extern void *gFollowPathEntry00178EA0Logger;
extern void j_0003a17a();
extern void j_00021e27();
extern void j_0000a9d4();
extern void j_0000ebab();
extern void j_0003251f();
class FollowPathEntry00178EA0Path {
public:
    char pad000[0x44]; PathVector00178EA0<Coord3D> points;
    const Coord3D *point(int i) const {
        if (i<0 || (unsigned)i>=points.size()) return 0;
        return &points[i];
    }
};
class FollowPathEntry00178EA0AI {
public:
    char pad000[0x30]; FollowPathEntry00178EA0Path *at030;
    char pad034[0x194-0x34]; int at194;
    char pad198[0x1cc-0x198]; void *at1cc;
    char pad1d0[0x326-0x1d0]; bool at326; char pad327; bool at328;
    const Coord3D *point(int i) const { return at030->point(i); }
    const Coord3D *pointOut(int i) {
    typedef const Coord3D *(FollowPathEntry00178EA0AI::*Method)(int);
    union { void (*raw)(); Method method; } call;
    call.raw=j_0000a9d4; return (this->*call.method)(i);
}
void extra(float f) {
    typedef void (FollowPathEntry00178EA0AI::*Method)(float);
    union { void (*raw)(); Method method; } call;
    call.raw=j_0000ebab; (this->*call.method)(f);
}
};
class FollowPathEntry00178EA0Object {
public:
    char pad000[0x204]; FollowPathEntry00178EA0AI *at204;
bool kind(int i) const {
    typedef bool (FollowPathEntry00178EA0Object::*Method)(int) const;
    union { void (*raw)(); Method method; } call;
    call.raw=j_0003251f; return (this->*call.method)(i);
}
};
struct FollowPathEntry00178EA0Machine {
    char pad000[0x10]; FollowPathEntry00178EA0Object *at010;
};
class FollowPathEntry00178EA0 {
public:
    char pad000[4]; int at004; char pad008[0x1c-8];
    FollowPathEntry00178EA0Machine *at01c;
    char pad020[4]; Coord3D at024; char pad030[0x4c-0x30];
    bool at04c; char pad04d[3]; int at050; bool at054;
int hub() {
    typedef int (FollowPathEntry00178EA0::*Method)();
    union { void (*raw)(); Method method; } call;
    call.raw=j_00021e27; return (this->*call.method)();
} int run();
};
#define PATH_LOG ((void (__cdecl *)(void*,const char*,...))j_0003a17a)
int FollowPathEntry00178EA0::run() {
    FollowPathEntry00178EA0Object *obj=at01c->at010;
    FollowPathEntry00178EA0AI *ai=obj->at204;
    at050=0;
    const Coord3D *pos=ai->point(at050);
    if (!pos) return -2;
    at024=*pos;
    const Coord3D *next=ai->point(1);
    at054=true;
    ai->at194=0;
    if (at004==7) {
        ai->at328=true; ai->at326=false;
        if(gFollowPathEntry00178EA0Debug && gFollowPathEntry00178EA0Logger)
            PATH_LOG(gFollowPathEntry00178EA0Logger,"CritterDesync: setAdjustDestination(FALSE) 39");
        at04c=false; at054=true;
    }
    int result=hub();
    if(next) {
        float dx=next->x-pos->x;
        float dy=next->y-pos->y;
        float offset=(float)sqrt(dx*dx+dy*dy);
        typedef const Coord3D *(FollowPathEntry00178EA0AI::*Point)(int);
        union { void (*raw)(); Point fn; } pointRoute={j_0000a9d4};
        const Coord3D *following=(ai->*pointRoute.fn)(at050+2);
        if(following) offset+=40.0f;
        ai->extra(offset);
        if(gFollowPathEntry00178EA0Debug && gFollowPathEntry00178EA0Logger)
            PATH_LOG(gFollowPathEntry00178EA0Logger,"CritterDesync: setAdjustDestination(FALSE) 40");
        at04c=false;
    } else {
        if(gFollowPathEntry00178EA0Debug && gFollowPathEntry00178EA0Logger)
            PATH_LOG(gFollowPathEntry00178EA0Logger,"CritterDesync: setAdjustDestination(m_adjustFinal=%s) 41",at054?"TRUE":"FALSE");
        at04c=at054;
        ai->extra(0.0f);
        if(obj->kind(25)) {
            if(ai && ai->at1cc) *(unsigned*)((char*)ai->at1cc+0x40)|=8;
        }
    }
    return result;
}
