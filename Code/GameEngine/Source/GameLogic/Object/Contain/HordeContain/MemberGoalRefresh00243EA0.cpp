// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0x00243EA0: HordeContain interface 0x010AED58 slot 68, beginMelee.
// Adjusted receiver (this-0xdc). The dword the caller pushes is the target.
// Hub contracts: docs/analysis/0x003e9720.md. ret4; incoming dword unused.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <map>
#include <vector>
#include "coord.h"

// Existing ILT routes; typed member pointers preserve each proved thiscall ABI.
extern void j_00015d02(); // removeGoal: Object*, ret4, body 003E3D20.
extern void j_000294e2(); // updateGoal: five arguments, ret20, body 003E9720.
extern void j_0003a391(); // destination layer getter: no args, EAX, body 001BEC20.
extern void j_00024d70(); // aiIdle: command source dword, ret4, body 000D87E0.

template<int N> class Slots00243EA0 : public Slots00243EA0<N-1> {
public: virtual void unused(char (*)[N])=0;
};
template<> class Slots00243EA0<0> {};
class AI00243EA0 : public Slots00243EA0<96> {
public:
    virtual bool slot180()=0;
#define S(N) virtual void unused##N()=0
    S(97);S(98);S(99);S(100);S(101);S(102);S(103);S(104);S(105);
    S(106);S(107);S(108);S(109);S(110);S(111);S(112);S(113);S(114);
    S(115);S(116);S(117);S(118);S(119);S(120);S(121);
#undef S
    virtual void slot1E8()=0;
    char pad004[0x140-4];
    void *field140;
    char pad144[0x1d8-0x144];
    int field1D8;
};
class Member00243EA0 {
public:
    char pad000[0x38]; Coord3D position;
    char pad044[0x74-0x44]; int m_id;
    char pad078[0x90-0x78]; unsigned field090;
    char pad094[0x204-0x94]; AI00243EA0 *m_ai;
    int destinationLayer() const {
        union { void (*entry)(); int (Member00243EA0::*member)() const; } call;
        call.entry=j_0003a391;
        return (this->*call.member)();
    }
};
class Command00243EA0 { public: void idle(int source) {
    union { void (*entry)(); void (Command00243EA0::*member)(int); } call;
    call.entry=j_00024d70;
    (this->*call.member)(source);
} };
class Pathfinder00243EA0 { public:
    void removeGoal(Member00243EA0 *object) {
        union { void (*entry)(); void (Pathfinder00243EA0::*member)(Member00243EA0 *); } call;
        call.entry=j_00015d02;
        (this->*call.member)(object);
    }
};
class AI { public: char pad000[12]; Pathfinder00243EA0 *pathfinder; };
extern AI *TheAI;
struct Slot00243EA0 {
    int field000; Coord3D position; bool field010; char pad011[11];
};
class MemberGoalRefresh00243EA0 {
public:
    void beginMelee(int target);
    char pad000[4]; bool field004,field005;
    char pad006[0x3c-6]; _STL::map<int,int> indices;
    char padAfterMap[0xf4-0x3c-sizeof(_STL::map<int,int>)];
    _STL::vector<Slot00243EA0> slots;
    char padAfterSlots[0x118-0xf4-sizeof(_STL::vector<Slot00243EA0>)];
    bool field118;
};

void MemberGoalRefresh00243EA0::beginMelee(int target)
{
    Member00243EA0 *owner=*(Member00243EA0 **)((char *)this-0xdc);
    field118=true;
    field004=true;
    field005=false;
    TheAI->pathfinder->removeGoal(owner);
    _STL::list<Member00243EA0 *> &members=*(_STL::list<Member00243EA0 *> *)((char *)this-0xac);
    for (_STL::list<Member00243EA0 *>::iterator it=members.begin();it!=members.end();++it) {
        Member00243EA0 *member=*it;
        if (!member) continue;
        AI00243EA0 *ai=member->m_ai;
        if (ai && ai->field1D8==4 && ai->field140) continue;
        int memberID=member->m_id;
        _STL::map<int,int>::iterator found=indices.find(memberID);
        int index=found!=indices.end()?found->second:0;
        if (!(member->field090&0x10000000) && ai && !ai->slot180())
            ((Command00243EA0 *)((char *)ai+0x20))->idle(2);
        if (index>=0 && (unsigned)index<slots.size()) {
            Slot00243EA0 &slot=slots[index];
            const Coord3D *position=&member->position;
            slot.position=*position;
            slot.field010=true;
            Pathfinder00243EA0 *pathfinder=TheAI->pathfinder;
            union { void (*entry)(); void (Pathfinder00243EA0::*member)(Member00243EA0 *,const Coord3D *,int,const char *,int); } update;
            update.entry=j_000294e2;
            (pathfinder->*update.member)(member,position,member->destinationLayer(),
                "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x1862);
            member->m_ai->slot1E8();
        }
    }
}
