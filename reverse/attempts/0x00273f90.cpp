// ?d_00273f90@@YAXXZ
// partial score=0.335877862595 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail 00273F90, 917 bytes. The update flow parallels ZH AIUpdate.cpp:1009.
// Opaque owner retained: caller metadata alone is not an identity witness.
// Hub ABI/layout witnesses: docs/analysis/0x003e9720.md.
// All offset views below are witnessed by this body's complete instructions.
#include "basetype.h"

template<class T, int O> __forceinline T& field(void *p) { return *(T*)((char*)p+O); }
struct TickSub00273F90 { char pad00[0x5c]; bool flag5c; };
struct TickObject00273F90 {
    char pad00[0x38]; Coord3D m_position;
    char pad44[0x74-0x44]; int m_id;
    char pad78[0x98-0x78]; unsigned word98;
    char pad9c[0x110-0x9c]; unsigned m_modelConditionFlags[10];
    char pad138[0x208-0x138]; TickSub00273F90 *ptr208;
    char pad20c[0x344-0x20c]; unsigned m_privateStatus;
};
struct TickCurrent00273F90 { void *vptr; int id; };
class TickCall00273F90 {};
template<class T> __forceinline T member(void (*raw)()) {
    union { void (*raw)(); T m; } u; u.raw=raw; return u.m;
}
#define CALL(T,p,j) (((TickCall00273F90*)(p))->*member<T>(j))
typedef void (TickCall00273F90::*Void0)();
typedef bool (TickCall00273F90::*Bool0)();
typedef int (TickCall00273F90::*Int0)();
typedef void (TickCall00273F90::*VoidInt)(int);
typedef void (TickCall00273F90::*VoidPtr)(void*);
typedef bool (TickCall00273F90::*BoolInt)(int);
typedef TickObject00273F90* (TickCall00273F90::*PtrInt)(int);
typedef bool (TickCall00273F90::*BoolPos)(void*,Coord3D*);
typedef void (TickCall00273F90::*VoidPos)(void*,Coord3D*);
enum TickSleep00273F90 { TickNone=1, TickForever=0x3fffffff };
typedef void (TickCall00273F90::*VoidSleep)(void*,TickSleep00273F90*);
typedef void (TickCall00273F90::*UpdateGoal)(void*,const Coord3D*,int,const char*,int);
extern void j_0003d95b(); extern void j_0001f253(); extern void j_0003251f();
extern void j_000398a1(); extern void j_00031f7a(); extern void j_00016888();
extern void j_00048928(); extern void j_0002191d(); extern void j_000065e1();
extern void j_00015d02(); extern void j_0001b919(); extern void j_00009d04();
extern void j_0003a391(); extern void j_000294e2(); extern void j_0000315c();
extern void j_00013eee(); extern void j_00010456(); extern void j_00027566();
extern void *TheAI;
extern void *TheBfmeGameLogic;

class TickStateMachine00273F90 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual int slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(int);
    char pad04[0x1c-4]; TickCurrent00273F90 *ptr1c;
    char pad20[0x40-0x20]; bool flag40;
    int currentID() { return ptr1c ? ptr1c->id : -1; }
};
class UpdateTick00273F90 {
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
    virtual bool slot180();
    virtual void slot184();
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
    virtual void slot1ec();
    virtual void slot1f0();
    virtual void slot1f4();
    virtual void slot1f8();
    virtual void slot1fc();
    virtual void slot200();
    virtual void slot204();
    virtual void slot208();
    virtual void slot20c();
    virtual void slot210();
    virtual int slot214();

    char pad004[0x4];
    TickObject00273F90* m_object;
    char pad00c[0x24];
    TickStateMachine00273F90* m_stateMachine;
    char pad034[0x108];
    void* ptr13c;
    char pad140[0x3c];
    unsigned m_queueForPathFrame;
    Coord3D pos180;
    char pad18c[0x4c];
    int word1d8;
    char pad1dc[0x141];
    bool flag31d;
    char pad31e[0x5];
    bool flag323;
    char pad324[0x7];
    bool m_isAiDead;
    char pad32c[0x4];
    bool m_isInUpdate;
    char pad331[0x5];
    bool flag336;
    unsigned run();
    TickObject00273F90 *object() { return m_object; }
    TickStateMachine00273F90 *machine() { return m_stateMachine; }
    void clear114() {
        TickObject00273F90 *p=object();
        if (p->m_modelConditionFlags[1]&0x10000000) {
            p->m_modelConditionFlags[1]&=~0x10000000;
            CALL(Void0,p,j_0002191d)();
        }
    }
    void clear120() {
        TickObject00273F90 *p=object();
        if (p->m_modelConditionFlags[4]&0x40000) {
            p->m_modelConditionFlags[4]&=~0x40000;
            CALL(Void0,p,j_0002191d)();
        }
    }
};

unsigned UpdateTick00273F90::run()
{
    TickObject00273F90 *obj=object();
    if ((obj->m_privateStatus&1) && (obj->word98&0x40)) {
        TickObject00273F90 *other=CALL(PtrInt,TheBfmeGameLogic,j_0001f253)(CALL(Int0,obj,j_0003d95b)());
        if (other && CALL(BoolInt,other,j_0003251f)(164)) {
            CALL(VoidPtr,other,j_000398a1)(obj);
            CALL(VoidInt,obj,j_00031f7a)(70);
        }
    }
    CALL(Void0,this,j_00016888)();
    TickSub00273F90 *sub=obj->ptr208;
    if (sub && sub->flag5c) {
        if (obj->m_privateStatus&1) {
            if (machine()->currentID()==13) goto clearConditions;
            if (CALL(Bool0,machine(),j_00048928)()) goto clearConditions;
            machine()->slot20(13);
        } else {
            goto noPrivateStatus;
        }
clearConditions:
        clear114();
        clear120();
        return 1;
noPrivateStatus:
        if (machine()->currentID()!=0) {
            CALL(Void0,this,j_000065e1)();
            slot1e8();
        }
        CALL(VoidPtr,(field<void*,0xc>(TheAI)),j_00015d02)(obj);
        goto clearConditions;
    }
    if (!slot180()) flag336=true;
    m_isInUpdate=true;
    ptr13c=0;
    TickSleep00273F90 sleep=TickForever;
    int stateSleep=machine()->slot10();
    if (stateSleep>0) {
        if (stateSleep<(int)sleep) sleep=(TickSleep00273F90)stateSleep;
    } else sleep=TickNone;
    if (slot18c()) return sleep;
    if (flag323) {
        m_queueForPathFrame=0;
        CALL(Void0,this,j_000065e1)();
        if (word1d8!=3) slot1e8();
        clear114();
        clear120();
        Coord3D goal;
        if (CALL(BoolPos,(field<void*,0xc>(TheAI)),j_0001b919)(object(),&goal)) {
            float dx=goal.x-object()->m_position.x;
            float dy=goal.y-object()->m_position.y;
            if (dx*dx+dy*dy>=100.0f) {
                goal=object()->m_position;
                CALL(VoidPos,(field<void*,0xc>(TheAI)),j_00009d04)(object(),&goal);
            }
            pos180=goal;
            flag31d=false;
            if (!CALL(BoolInt,obj,j_0003251f)(108))
                CALL(UpdateGoal,(field<void*,0xc>(TheAI)),j_000294e2)(obj,&goal,
                    CALL(Int0,object(),j_0003a391)(),
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp",0x75f);
        }
        flag323=false;
        CALL(VoidPtr,this,j_0000315c)(0);
    }
    unsigned now=field<unsigned,0x3c>(TheBfmeGameLogic);
    if (m_queueForPathFrame!=0) {
        if (now>=m_queueForPathFrame) {
            CALL(BoolInt,(field<void*,0xc>(TheAI)),j_00013eee)(object()->m_id);
            m_queueForPathFrame=0;
        } else {
            unsigned delta=m_queueForPathFrame-now;
            if (delta<sleep) sleep=(TickSleep00273F90)delta;
        }
    }
    TickSleep00273F90 turretSleep=sleep;
    CALL(VoidSleep,this,j_00010456)(obj,&turretSleep);
    unsigned result;
    if (m_isAiDead && machine()->currentID()!=13) {
        CALL(Void0,machine(),j_00027566)();
        machine()->slot14();
        machine()->slot20(13);
        machine()->flag40=true;
        result=1;
    } else result=turretSleep;
    int tmp=slot214();
    if (tmp<(int)result) result=tmp;
    m_isInUpdate=false;
    if (ptr13c) return 1;
    return result;
}
