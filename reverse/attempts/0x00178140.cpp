// ?onEnter@AIAttackMeleeEngageState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9001560062402496 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
// RVA 00178140, 641 bytes; identity is supported by the constructor-installed
// vtable 0x01099848 slot 4 -> ILT 0x0002F5E5 -> this body.
// Hub contract and Object offsets: docs/analysis/0x003e9720.md.
#include "coord3d.h"
// Visible definitions from coord3d.cpp retain native nontrivial copying.
inline Coord3D::Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &c) { x=c.x; y=c.y; z=c.z; }
inline Coord3D::~Coord3D() {}
__forceinline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &c) {
    struct Raw { unsigned int x,y,z; };
    *(Raw *)this = *(const Raw *)&c;
    return *this;
}
__forceinline Coord3D &Coord3D::operator=(const Coord3D &c) {
    *(Coord3DBase *)this = c;
    return *this;
}

class StateMachine;
class NotifyWeaponFiredInterface;
class AIAttackFireWeaponState {
    unsigned char storage[0x2c];
public:
    AIAttackFireWeaponState(StateMachine *, NotifyWeaponFiredInterface *);
};
class AttackGoalEntry00178140Object;
class AttackGoalEntry00178140AI {
public:
    void set0016A6D0(const Coord3D *);
    void destroy0026F080();
};
class AttackGoalEntry00178140Check {
public:
    bool flag0029A7A0();
};
class AttackGoalEntry00178140Weapon {
public:
    bool range001E8930(AttackGoalEntry00178140Object *, AttackGoalEntry00178140Object *, int);
};
class AttackGoalEntry00178140Object {
public:
    unsigned char pad000[0x38];
    Coord3D at038;
    unsigned char pad044[0x94-0x44];
    unsigned int at094;
    unsigned char pad098[0x204-0x98];
    AttackGoalEntry00178140AI *at204;
    AttackGoalEntry00178140Check *at208;
    unsigned char pad20c[8];
    void *at214;
    unsigned char pad218[0x344-0x218];
    unsigned char at344;
    AttackGoalEntry00178140Weapon *weapon001BE230(void *);
    int layer001BEC20();
    void status000D3EB0(int, bool);
    bool test000C4D40(int);
    const Coord3D *position() const { return &at038; }
    AttackGoalEntry00178140AI *ai() const { return at204; }
};
class AttackGoalEntry00178140Machine {
public:
    unsigned char pad000[0x10];
    AttackGoalEntry00178140Object *at010;
    bool destroyed000A1D80();
    AttackGoalEntry00178140Object *goal000A1490();
};
class AttackGoalEntry00178140Pathfinder {
public:
    void update003E9720(AttackGoalEntry00178140Object *, const Coord3D *, int, const char *, int);
    bool goal003E6080(AttackGoalEntry00178140Object *, Coord3D *);
};
struct AttackGoalEntry00178140GlobalAI {
    unsigned char pad000[0xc];
    AttackGoalEntry00178140Pathfinder *at00c;
    AttackGoalEntry00178140Pathfinder *pathfinder() { return at00c; }
};
extern AttackGoalEntry00178140GlobalAI *g00178140Va012EF214;
extern bool g00178140Va012F0239;
extern void *g00178140Va012ED4FC;
extern void j_0003a17a();
__forceinline void log00178140(const char *text) {
    if (g00178140Va012F0239 && g00178140Va012ED4FC)
        ((void (__cdecl *)(void *, const char *))j_0003a17a)(g00178140Va012ED4FC, text);
}
enum StateReturnType {
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1,
    STATE_FAILURE = -2
};
template<int N> class AttackGoalEntry00178140Slots : public AttackGoalEntry00178140Slots<N-1> {
public: virtual void unused(char (*)[N]) = 0;
};
template<> class AttackGoalEntry00178140Slots<0> {};
class AIAttackMeleeEngageState : public AttackGoalEntry00178140Slots<4> {
public:
    virtual StateReturnType onEnter();
    virtual void onExit(int status) = 0;
    virtual StateReturnType update() = 0;
    virtual bool slot007() = 0;
    virtual bool slot008() = 0;
    virtual bool slot009() = 0;
    virtual bool slot010() = 0;
    virtual bool slot011() = 0;
    virtual bool slot012() = 0;
    virtual bool slot013() = 0;
    virtual bool slot014() = 0;
    virtual bool slot015() = 0;
    virtual bool slot016() = 0;
    virtual bool computePath() = 0;
    unsigned char pad004[0x1c-4];
    AttackGoalEntry00178140Machine *at01c;
    unsigned char pad020[0x4c-0x20];
    bool at04c;
    unsigned char pad04d[3];
    AIAttackFireWeaponState *at050;
    int at054;
    int at058;
    Coord3D at05c;
    unsigned char pad068[8];
    int at070;
    bool at074;
    unsigned char pad075[3];
    NotifyWeaponFiredInterface *at078;
    StateReturnType enter00172600();
};

// Typed single-inheritance routes preserve independently decoded ILT targets.
extern void j_00010910();
__forceinline void AttackGoalEntry00178140AI::set0016A6D0(const Coord3D * pos) {
    typedef void (AttackGoalEntry00178140AI::*Call)(const Coord3D *);
    union { void (*address)(); Call member; } route = { j_00010910 };
    return (this->*route.member)(pos);
}

extern void j_000065e1();
__forceinline void AttackGoalEntry00178140AI::destroy0026F080() {
    typedef void (AttackGoalEntry00178140AI::*Call)();
    union { void (*address)(); Call member; } route = { j_000065e1 };
    return (this->*route.member)();
}

extern void j_00006eec();
__forceinline bool AttackGoalEntry00178140Check::flag0029A7A0() {
    typedef bool (AttackGoalEntry00178140Check::*Call)();
    union { void (*address)(); Call member; } route = { j_00006eec };
    return (this->*route.member)();
}

extern void j_0002e85c();
__forceinline bool AttackGoalEntry00178140Weapon::range001E8930(AttackGoalEntry00178140Object * source, AttackGoalEntry00178140Object * target, int extra) {
    typedef bool (AttackGoalEntry00178140Weapon::*Call)(AttackGoalEntry00178140Object *, AttackGoalEntry00178140Object *, int);
    union { void (*address)(); Call member; } route = { j_0002e85c };
    return (this->*route.member)(source, target, extra);
}

extern void j_00031a7f();
__forceinline AttackGoalEntry00178140Weapon * AttackGoalEntry00178140Object::weapon001BE230(void * slot) {
    typedef AttackGoalEntry00178140Weapon * (AttackGoalEntry00178140Object::*Call)(void *);
    union { void (*address)(); Call member; } route = { j_00031a7f };
    return (this->*route.member)(slot);
}

extern void j_0003a391();
__forceinline int AttackGoalEntry00178140Object::layer001BEC20() {
    typedef int (AttackGoalEntry00178140Object::*Call)();
    union { void (*address)(); Call member; } route = { j_0003a391 };
    return (this->*route.member)();
}

extern void j_00032dee();
__forceinline void AttackGoalEntry00178140Object::status000D3EB0(int bit, bool value) {
    typedef void (AttackGoalEntry00178140Object::*Call)(int, bool);
    union { void (*address)(); Call member; } route = { j_00032dee };
    return (this->*route.member)(bit, value);
}

extern void j_000016a4();
__forceinline bool AttackGoalEntry00178140Object::test000C4D40(int bit) {
    typedef bool (AttackGoalEntry00178140Object::*Call)(int);
    union { void (*address)(); Call member; } route = { j_000016a4 };
    return (this->*route.member)(bit);
}

extern void j_0000432c();
__forceinline bool AttackGoalEntry00178140Machine::destroyed000A1D80() {
    typedef bool (AttackGoalEntry00178140Machine::*Call)();
    union { void (*address)(); Call member; } route = { j_0000432c };
    return (this->*route.member)();
}

extern void j_0000e570();
__forceinline AttackGoalEntry00178140Object * AttackGoalEntry00178140Machine::goal000A1490() {
    typedef AttackGoalEntry00178140Object * (AttackGoalEntry00178140Machine::*Call)();
    union { void (*address)(); Call member; } route = { j_0000e570 };
    return (this->*route.member)();
}

extern void j_000294e2();
__forceinline void AttackGoalEntry00178140Pathfinder::update003E9720(AttackGoalEntry00178140Object * obj, const Coord3D * pos, int layer, const char * file, int line) {
    typedef void (AttackGoalEntry00178140Pathfinder::*Call)(AttackGoalEntry00178140Object *, const Coord3D *, int, const char *, int);
    union { void (*address)(); Call member; } route = { j_000294e2 };
    return (this->*route.member)(obj, pos, layer, file, line);
}

extern void j_0001b919();
__forceinline bool AttackGoalEntry00178140Pathfinder::goal003E6080(AttackGoalEntry00178140Object * obj, Coord3D * pos) {
    typedef bool (AttackGoalEntry00178140Pathfinder::*Call)(AttackGoalEntry00178140Object *, Coord3D *);
    union { void (*address)(); Call member; } route = { j_0001b919 };
    return (this->*route.member)(obj, pos);
}

extern void j_00021e27();
__forceinline StateReturnType AIAttackMeleeEngageState::enter00172600() {
    typedef StateReturnType (AttackGoalEntry00178140AI::*Call)();
    union { void (*address)(); Call member; } route = { j_00021e27 };
    return (((AttackGoalEntry00178140AI *)this)->*route.member)();
}

StateReturnType AIAttackMeleeEngageState::onEnter() {


    AttackGoalEntry00178140Object *source = at01c->at010;
    if (at01c->destroyed000A1D80()) return STATE_SUCCESS;
    if (!at050)
        at050 = new AIAttackFireWeaponState((StateMachine *)at01c, at078);
    at054 = -1;
    if (g00178140Va012F0239 && g00178140Va012ED4FC)
        ((void (__cdecl *)(void *, const char *))j_0003a17a)(g00178140Va012ED4FC, "CritterDesync: setAdjustDestination(FALSE) 35");
    at04c = false;
    at058 = 0;
    at074 = false;
    at070 = 0;
    AttackGoalEntry00178140AI *ai = source->at204;
    AttackGoalEntry00178140Object *target = at01c->goal000A1490();
    if (!target || (target->at208 && target->at208->flag0029A7A0()) ||
        (target->at344 & 1) || (target->at094 & 0x20000)) return STATE_FAILURE;
    AttackGoalEntry00178140Weapon *weapon = source->weapon001BE230(0);
    if (!weapon) return STATE_FAILURE;
    if (weapon->range001E8930(source, target, 0)) {
        Coord3D pos = source->at038;
        AttackGoalEntry00178140Pathfinder *pathfinder = g00178140Va012EF214->at00c;
        pathfinder->update003E9720(source, &pos, source->layer001BEC20(),
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1c9a);
        if (g00178140Va012EF214->pathfinder()->goal003E6080(source, &pos)) ai->set0016A6D0(&pos);
        source->status000D3EB0(28, true);
        return STATE_SUCCESS;
    }
    at05c = target->at038;
    if (source->test000C4D40(37) && source->at214) {
        source->status000D3EB0(28, false);
        return STATE_FAILURE;
    }
    ai->destroy0026F080();
    if (g00178140Va012F0239 && g00178140Va012ED4FC)
        ((void (__cdecl *)(void *, const char *))j_0003a17a)(g00178140Va012ED4FC, "CritterDesync: ComputePath27");
    if (!computePath()) return STATE_FAILURE;
    if (at074) return STATE_CONTINUE;
    StateReturnType result = enter00172600();
    if (g00178140Va012F0239 && g00178140Va012ED4FC)
        ((void (__cdecl *)(void *, const char *))j_0003a17a)(g00178140Va012ED4FC, "CritterDesync: setAdjustDestination(TRUE) 36");
    at04c = true;
    return result;
}
