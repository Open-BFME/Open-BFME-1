// ?update@MemberGoals002440E0@@QAEXPAVMember002440E0@@@Z
// partial score=0.24498692240627729 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include/Precompiled
// stlport
// Retail 002440E0, 1147 bytes, adjusted ECX receiver and ret4.
// Hub contract from docs/analysis/0x003e9720.md; no EH frame.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include "../../Code/Libraries/Source/WWVegas/WWMath/coord.h"

class Member002440E0;
template<int N> class Slots002440E0:public Slots002440E0<N-1> {public: virtual void unused(char(*)[N])=0;};
template<> class Slots002440E0<0> {};
class Query002440E0:public Slots002440E0<18> {public: virtual Member002440E0* slot48(int,const Coord3D*,int)=0;};
class Contain002440E0:public Slots002440E0<26> {public: virtual Query002440E0* slot68()=0;};
class AI002440E0:public Slots002440E0<97> {
public:
    virtual bool slot184()=0;
    char pad004[0x140-4]; void* path140;
    char pad144[0x1d8-0x144]; int field1D8;
};
class Weapon002440E0 {public: bool rva001e8930(Member002440E0*,Member002440E0*,int);};
class Command002440E0 {public: void rva001535a0(Member002440E0*,int,int);};
class Member002440E0 {
public:
    char pad000[0x38]; Coord3D position;
    char pad044[0x74-0x44]; int m_id;
    char pad078[0x90-0x78]; unsigned field090;
    char pad094[4]; unsigned char byte098;
    char pad099[0x1fc-0x99]; Contain002440E0* m_contain;
    char pad200[4]; AI002440E0* m_ai;
    Member002440E0* rva001cb020(int);
    bool rva000a2cf0(int); Weapon002440E0* rva001be230(int);
    void rva001cbdc0(int); bool rva000c4d40(int); int rva001bec20();
};
struct QueryOutput002440E0 {unsigned data[16];};
class Pathfinder002440E0 {
public:
    int rva003e4680(Member002440E0*,const Coord3D*,QueryOutput002440E0*);
    void rva003e9720(Member002440E0*,const Coord3D*,int,const char*,int);
};
class AIHub002440E0 {public: char pad00[12]; Pathfinder002440E0* pathfinder;};
class Clock002440E0 {public: char pad00[0x3c]; unsigned frame;};
extern AIHub002440E0* TheAI;
extern Clock002440E0* TheGameLogic;
struct Record002440E0 {
    int field000; Coord3D position; bool field010; char pad011[3];
    unsigned field014,field018;
};
class Primary002440E0 {
public:
    bool rva00238d10(Member002440E0*,Coord3D*,Member002440E0*,const Coord3D*,bool,unsigned*,bool);
};
class MemberGoals002440E0:public Slots002440E0<37> {
public:
    virtual void slot094(Member002440E0*)=0;
#define S(N) virtual void unused##N()=0
    S(38);S(39);S(40);S(41);S(42);S(43);S(44);S(45);S(46);S(47);
    S(48);S(49);S(50);S(51);S(52);S(53);S(54);S(55);S(56);S(57);
    S(58);S(59);S(60);S(61);S(62);S(63);S(64);S(65);S(66);S(67);
#undef S
    virtual void slot110(Member002440E0*)=0;
    bool field004,field005;
    char pad006[0x3c-6]; _STL::map<int,int> indices;
    char padAfterMap[0xf4-0x3c-sizeof(_STL::map<int,int>)];
    _STL::vector<Record002440E0> records;
    char padAfterRecords[0x119-0xf4-sizeof(_STL::vector<Record002440E0>)];
    bool field119;
    void update(Member002440E0* target);
};

void MemberGoals002440E0::update(Member002440E0* target) {
    if(!target) return;
    if(field005) {slot110(target);field005=false;}
    Member002440E0* owner=*(Member002440E0**)((char*)this-0xdc);
    if(!(owner->byte098&8)) slot094(owner);
    Member002440E0* parent=target->rva001cb020(0);
    if(parent) target=parent;
    unsigned frame=TheGameLogic->frame;
    _STL::list<Member002440E0*>& members=*(_STL::list<Member002440E0*>*)((char*)this-0xac);
    int budget=members.size()/2;
    budget=_STL::max(budget,2);
    for(_STL::list<Member002440E0*>::iterator it=members.begin();it!=members.end();++it) {
        Member002440E0* member=*it;
        if(!member) continue;
        AI002440E0* ai=member->m_ai;
        if(ai && ai->field1D8==4 && ai->path140) continue;
        int id=member->m_id;
        _STL::map<int,int>::iterator found=indices.find(id);
        int index=found!=indices.end()?found->second:0;
        if(index<0 || (unsigned)index>=records.size()) continue;
        Record002440E0& record=records[index];
        int line;
        if(!(member->field090&0x10000000) && !ai->slot184()) {
            bool special=false;
            if(record.field000==3) special=target->rva000a2cf0(0x5c);
            QueryOutput002440E0 output;
            int result;
            if(((target->rva000a2cf0(7) && ((result=TheAI->pathfinder->rva003e4680(member,&member->position,&output))==0 || result==2)) || special) && member->rva001be230(0) && member->rva001be230(0)->rva001e8930(member,target,0) && member->m_ai) {
                ((Command002440E0*)((char*)member->m_ai+0x20))->rva001535a0(target,0x7fffffff,2);
                line=0x1992;
                goto updateCurrent;
            }
            if(record.field014>frame && !field119) continue;
            if(record.field000==1 || record.field000==2) {field004=true;continue;}
            if(record.field000==3) {
                member->rva001cbdc0(0);
                if(member->rva000c4d40(0x1c)) continue;
            }
            if(record.field000==0 && budget>0) record.field010=true;
            if(record.field010 || record.field000==3) {
                record.position=member->position;
                Coord3D targetPosition=target->position;
                Member002440E0* related=target->rva001cb020(0);
                if(related && related->m_contain && related->m_contain->slot68()) {
                    Member002440E0* selected=related->m_contain->slot68()->slot48(0,&record.position,0);
                    if(selected) targetPosition=selected->position;
                }
                bool recent=frame<record.field018+5;
                unsigned delay=0;
                bool kind=(record.field014>0 && target->rva000a2cf0(7));
                bool result=((Primary002440E0*)((char*)this-0xe4))->rva00238d10(member,&record.position,target,&targetPosition,recent,&delay,kind);
                if(delay) record.field014=delay+frame;
                else record.field014=0;
                if(result) {--budget;field004=true;record.field000=1;}
                else {
                    if(record.field014) member->rva001cbdc0(0);
                    record.field000=0;record.field010=false;
                }
                Pathfinder002440E0* pathfinder=TheAI->pathfinder;
                pathfinder->rva003e9720(member,&record.position,member->rva001bec20(),"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x19de);
                record.field010=false;
                records[index]=record;
                if(budget<1) break;
            }
            continue;
        }
        record.field010=true;
        record.field018=frame;
        line=0x197d;
updateCurrent:
        Pathfinder002440E0* currentPathfinder=TheAI->pathfinder;
        currentPathfinder->rva003e9720(member,&member->position,member->rva001bec20(),"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",line);
    }
    field119=false;
}

// Existing ILT routes only; no new semantic pin identities.
#pragma comment(linker, "/alternatename:?rva001cb020@Member002440E0@@QAEPAV1@H@Z=?j_0000faa6@@YAXXZ")
#pragma comment(linker, "/alternatename:??$find@H@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@2@@1@ABH@Z=?j_0001f000@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000a2cf0@Member002440E0@@QAE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003e4680@Pathfinder002440E0@@QAEHPAVMember002440E0@@PBUCoord3D@@PAUQueryOutput002440E0@@@Z=?j_00027ab6@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001be230@Member002440E0@@QAEPAVWeapon002440E0@@H@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001e8930@Weapon002440E0@@QAE_NPAVMember002440E0@@0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001535a0@Command002440E0@@QAEXPAVMember002440E0@@HH@Z=?j_0002edcf@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001cbdc0@Member002440E0@@QAEXH@Z=?j_0000e4a8@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000c4d40@Member002440E0@@QAE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00238d10@Primary002440E0@@QAE_NPAVMember002440E0@@PAUCoord3D@@0PBU3@_NPAI3@Z=?j_000263f0@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001bec20@Member002440E0@@QAEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003e9720@Pathfinder002440E0@@QAEXPAVMember002440E0@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
