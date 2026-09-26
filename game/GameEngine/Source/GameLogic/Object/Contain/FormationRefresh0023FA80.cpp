// cl: /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWMath
// Compile symbol: ?run@FormationRefresh0023FA80@@QAEHXZ
// Complete 649-byte boundary at RVA 0023FA80. Receiver is an interior view:
// its owner is at -8 and its primary interface is at -0x10.
// Hub ABI: docs/analysis/0x003e9720.md; retail instructions in
// build/hub_003e9720/retail/0x0023fa80.asm. No original method name claimed.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &c) { x=c.x; y=c.y; z=c.z; }
inline Coord3D::~Coord3D() {}

extern void j_0004a37c(); extern void j_00035ca1();
extern void j_000133ef(); extern void j_00046894();
extern void j_00044774(); extern void j_00014d62();
extern void j_00040f52(); extern void j_0003a391();
extern void j_00035e0e(); extern void j_00044f6c();
extern void j_000294e2(); extern void j_00025f77();

class Refresh0023FA80Route {};
#define ROUTE0(ret, name, thunk) \
    __forceinline ret name() { typedef ret (Refresh0023FA80Route::*Call)(); \
    union { void (*address)(); Call member; } route = { thunk }; \
    return (((Refresh0023FA80Route *)this)->*route.member)(); }

class Refresh0023FA80Flags {
public:
    unsigned int words[10];
    __forceinline bool differs(const Refresh0023FA80Flags &other) const {
        typedef bool (Refresh0023FA80Route::*Call)(const Refresh0023FA80Flags &);
        union { void (*address)(); Call member; } route = { j_00035ca1 };
        return (((Refresh0023FA80Route *)this)->*route.member)(other);
    }
};
class Refresh0023FA80AI { public: ROUTE0(bool, blocked, j_00044774) };
class Refresh0023FA80Object {
public:
    unsigned char pad000[0x38];
    Coord3D at038;
    unsigned char pad044[0x110-0x44];
    Refresh0023FA80Flags at110;
    unsigned char pad138[0x204-0x138];
    Refresh0023FA80AI *at204;
    ROUTE0(int, layer, j_0003a391)
    __forceinline void setLayer(int value) {
        typedef void (Refresh0023FA80Route::*Call)(int);
        union { void (*address)(); Call member; } route = { j_00035e0e };
        (((Refresh0023FA80Route *)this)->*route.member)(value);
    }
};
// Opaque receiver; typed PMFs at the call sites retain the exact by-value ABI.
class Refresh0023FA80Pathfinder {};
struct Refresh0023FA80GlobalAI {
    unsigned char pad000[12]; Refresh0023FA80Pathfinder *at00c;
    Refresh0023FA80Pathfinder *pathfinder() const { return at00c; }
};
struct Refresh0023FA80GameLogic { unsigned char pad000[0x3c]; unsigned int at03c; };
extern Refresh0023FA80GlobalAI *g0023FA80Va012EF214;
extern Refresh0023FA80GameLogic *g0023FA80Va012F0898;

template<int N> class Refresh0023FA80Slots : public Refresh0023FA80Slots<N-1> {
public: virtual void unused(char (*)[N]) = 0;
};
template<> class Refresh0023FA80Slots<0> {};
class Refresh0023FA80Primary : public Refresh0023FA80Slots<28> {
public:
    virtual bool slot070() = 0;
    virtual void slot074() = 0;
    virtual void slot078() = 0;
    virtual void slot07c() = 0;
    virtual void slot080() = 0;
    unsigned char pad004[4];
    Refresh0023FA80Object *at008;
    ROUTE0(void, changed, j_00046894)
    ROUTE0(void, periodic, j_00025f77)
    __forceinline void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj) { if (ai && obj) schedule(ai,obj); }
    __forceinline void guardedSchedule() {
        scheduleNullable(at008 ? at008->at204 : 0,at008);
    }
    __forceinline void schedule(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj) {
        typedef void (Refresh0023FA80Route::*Call)(Refresh0023FA80AI *, Refresh0023FA80Object *);
        union { void (*address)(); Call member; } route = { j_0004a37c };
        (((Refresh0023FA80Route *)this)->*route.member)(ai, obj);
    }
};
struct Refresh0023FA80Node {
    Refresh0023FA80Node *next, *prev;
    Refresh0023FA80Object *object;
};
class Refresh0023FA80Tree {
public:
    void *at000; unsigned int at004;
    ROUTE0(void, clear0023AB70, j_00014d62)
    ROUTE0(void, clear00235E80, j_00044f6c)
};
class FormationRefresh0023FA80 {
public:
    unsigned char pad000[0x28];
    Refresh0023FA80Node *at028;
    unsigned char pad02c[0xd8-0x2c];
    bool at0d8, at0d9;
    unsigned char pad0da[2];
    Refresh0023FA80Flags at0dc;
    unsigned char pad104[0x134-0x104];
    Refresh0023FA80Tree at134;
    unsigned char pad13c[4];
    int at140, at144;
    unsigned char pad148[0x198-0x148];
    Refresh0023FA80Tree at198;
    unsigned char pad1a0[0x1ee-0x1a0];
    unsigned char at1ee;
    unsigned char pad1ef[9];
    unsigned int at1f8;
    Refresh0023FA80Primary *primary() { return (Refresh0023FA80Primary *)((char *)this-0x10); }
    Refresh0023FA80Object *owner() { return primary()->at008; }
    ROUTE0(int, update0022D660, j_000133ef)
    int run();
};

int FormationRefresh0023FA80::run() {
    if (at1ee == 1) {
        primary()->guardedSchedule();
        return 10;
    }
    Refresh0023FA80Flags flags = owner()->at110;
    bool changed = false;
    if (at0dc.differs(flags)) {
        changed = true;
        at0dc = flags;
    }
    int result = update0022D660();
    Refresh0023FA80Object *obj = owner();
    Refresh0023FA80AI *ai = obj->at204;
    if (!ai) return result;
    if (changed) primary()->changed();
    if (ai->blocked()) {
        at0d8 = true;
        at134.clear0023AB70();
        at1f8 = 0;
    } else {
        typedef int (Refresh0023FA80Route::*LayerCall)(Refresh0023FA80Object *, Coord3D);
        union { void (*address)(); LayerCall member; } layerCall = { j_00040f52 };
        int layer = (((Refresh0023FA80Route *)g0023FA80Va012EF214->pathfinder())->*layerCall.member)(obj,obj->at038);
        if (layer != obj->layer()) {
            obj->setLayer(layer);
            for (Refresh0023FA80Node *node=at028->next; node!=at028; node=node->next) {
                Refresh0023FA80Object *member=node->object;
                int memberLayer = (((Refresh0023FA80Route *)g0023FA80Va012EF214->pathfinder())->*layerCall.member)(member,member->at038);
                member->setLayer(memberLayer);
            }
            at0d8 = true;
        }
    }
    primary()->schedule(ai,obj);
    if (g0023FA80Va012F0898->at03c % 5 == 0 && primary()->slot070()) return 1;
    if (at0d8 || at134.at004 || at144) {
        at0d8=false;
        if (at144 && !at140) {
            at144=0;
            at198.clear00235E80();
            at0d9=true;
        }
        primary()->slot080();
        if (at0d8) return 1;
        at0d9=false;
        if (!ai->blocked()) {
            Refresh0023FA80Pathfinder *finder=g0023FA80Va012EF214->pathfinder();
            typedef void (Refresh0023FA80Route::*UpdateCall)(Refresh0023FA80Object *, const Coord3D *, int, const char *, int);
            union { void (*address)(); UpdateCall member; } updateCall = { j_000294e2 };
            (((Refresh0023FA80Route *)finder)->*updateCall.member)(obj,&obj->at038,obj->layer(),
                "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x898);
        }
        if (at0d8 || at134.at004) return 1;
    }
    if (g0023FA80Va012F0898->at03c % 5 == 0) primary()->periodic();
    return result;
}
