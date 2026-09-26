// ?onEnter@AIAttackMeleeApproachState@@UAE?AW4StateReturnType@@XZ
// partial score=0.996 date=2026-09-24
// cl: /Ob1 /ICode/Libraries/Source/WWVegas/WWMath
// AIAttackMeleeApproachState::onEnter, retail RVA 0x00176F70 (747 bytes).
// Owner: vtable 0x0109A6C0 slot 4, its matched deleting destructor 0x00185450
// and the matched AttackMeleeStateMachine constructor 0x00180EE0 that builds
// it; the base AIInternalMoveToState::onEnter (0x00172600) shares slot 4.
// reverse/identity_evidence/00176f70.md has the detail.
// Callees use the ledger names retail's ILT calls reach (tools/callees.py).
// Remaining residue (3 bytes): the second AI-data pointer is EDI, retail ESI.
// Measured: ESI frees only when `source` is dead at the data load in IL; any
// data load between the copy and Sub2D is an ambiguous read that keeps the
// copy stores (770 B), and a load after the stores cannot be scheduled above them.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
__forceinline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {
    struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&p; return *this;
}
__forceinline Coord3D &Coord3D::operator=(const Coord3D &p) { Coord3DBase *base=this; *base=p; return *this; }
inline Coord3D::Coord3D(const Coord3D &p) {x=p.x; y=p.y; z=p.z;}
inline Coord3D &Coord3D::Sub2D(const Coord3DBase &p) {x-=p.x; y-=p.y; return *this;}
typedef unsigned char Byte;
template<int N> struct Slots : Slots<N-1> { virtual void unused(char(*)[N])=0; };
template<> struct Slots<0> {};
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };
enum WeaponSlotType;

class Object;
class Player;

class Weapon {
public:
    bool isWithinAttackRange(const Object *source, const Object *victim, int unused) const;
};

class AIUpdateInterface {
public:
    void destroyPath();
    Byte pad000[0x33a]; Byte m_flag33a;
};

// Object +0x208 query reached through ILT 0x00006EEC.
class Gen_0029A7A0 {
public:
    bool bfmeFlagged() const;
};

class BFMEObjectStealthQuery {
public:
    bool isStealthedAndUndetected(const Object *viewer) const;
};

class Object {
public:
    Player *getControllingPlayer() const;
    bool crushPolicy(Object *victim, CrushSquishTestType test) const;
    bool rva001c7530();
    bool testStatus(int status) const;
    Weapon *getCurrentWeapon(WeaponSlotType *slot);
    const Coord3D *getPosition() const { return &m_position; }
    AIUpdateInterface *getAI() const { return m_ai; }

    Byte pad000[0x38]; Coord3D m_position;
    Byte pad044[0x98-0x44]; unsigned m_status98;
    Byte pad09c[0x204-0x9c]; AIUpdateInterface *m_ai; Gen_0029A7A0 *ptr208;
    Byte pad20c[0x214-0x20c]; void *dword214;
};

class BfmeOutOfWeaponRangeObject;
bool rva0014ca60(BfmeOutOfWeaponRangeObject *source, BfmeOutOfWeaponRangeObject *victim);

class StateMachine {
public:
    bool isGoalObjectDestroyed() const;
    Object *getGoalObject();
    Byte pad00[0x10]; Object *m_owner;
};
struct MachineSlot38 : Slots<14> { virtual void slot38(void*)=0; };
struct MachineSlot20 : Slots<8> { virtual void slot20(int)=0; };

class TAiData {
public:
    Byte pad00[0x90]; float m_float90; float m_float94;
};
class AI {
public:
    const TAiData *getAiData() const { return m_aiData; }
    Byte pad00[0x14]; TAiData *m_aiData;
};
extern AI *TheAI;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...);

struct State : Slots<4> {
    virtual StateReturnType onEnter()=0;
    virtual void slot05()=0; virtual void slot06()=0; virtual void slot07()=0;
    virtual void slot08()=0; virtual void slot09()=0; virtual void slot10()=0;
    virtual void slot11()=0; virtual void slot12()=0; virtual void slot13()=0;
    virtual void slot14()=0; virtual void slot15()=0; virtual void slot16()=0;
    Byte pad04[0x18]; StateMachine *m_machine;
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
struct AIAttackMeleeApproachState : AIInternalMoveToState {
    int field50; Coord3D previous54;
    virtual StateReturnType onEnter();
};

StateReturnType AIAttackMeleeApproachState::onEnter() {
    Object *source=m_machine->m_owner;
    if (m_machine->isGoalObjectDestroyed()) return STATE_FAILURE;
    Object *victim=m_machine->getGoalObject();
    if (victim && ((BFMEObjectStealthQuery*)victim)->isStealthedAndUndetected((const Object*)source->getControllingPlayer())) {
        ((MachineSlot38*)m_machine)->slot38(0);
        return STATE_FAILURE;
    }
    if ((source->m_status98&8) || source->getAI()->m_flag33a) {
        // Positive predicate arm first: generation order gives retail's
        // eax/cl temporaries for the second flag read.
        if (rva0014ca60((BfmeOutOfWeaponRangeObject*)source,(BfmeOutOfWeaponRangeObject*)victim)) {
            if (source->getAI()->m_flag33a) {
                Weapon *weapon=source->getCurrentWeapon(0);
                if (!weapon || !weapon->isWithinAttackRange(source,victim,0)) {
                    ((MachineSlot38*)m_machine)->slot38(0);
                    return STATE_FAILURE;
                }
            }
            return STATE_SUCCESS;
        }
        ((MachineSlot38*)m_machine)->slot38(0);
        return STATE_FAILURE;
    }
    if (Glo012F0239 && TheCRCParameterCheck) bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"CritterDesync: setAdjustDestination(FALSE) 31");
    m_adjustDestinations=false;
    field50=0;
    if (!victim) return STATE_FAILURE;
    if (source->crushPolicy(victim,TEST_CRUSH_OR_SQUISH) && source->rva001c7530()) {
        ((MachineSlot20*)m_machine)->slot20(233);
        return STATE_CONTINUE;
    }
    Gen_0029A7A0 *physics=victim->ptr208;
    if (physics && physics->bfmeFlagged()) return STATE_FAILURE;
    Weapon *weapon=source->getCurrentWeapon(0);
    if (!weapon) return STATE_FAILURE;
    if (weapon->isWithinAttackRange(source,victim,0)) return STATE_SUCCESS;
    previous54=*victim->getPosition();
    if (!source->crushPolicy(victim,TEST_CRUSH_OR_SQUISH)) {
        const TAiData *data=TheAI->getAiData();
        Coord3D delta(*source->getPosition());
        delta.Sub2D(previous54);
        delta.z=0.0f;
        if (delta.length()<data->m_float94+data->m_float90) return STATE_SUCCESS;
    }
    if (source->testStatus(37) && source->dword214) return STATE_FAILURE;
    source->getAI()->destroyPath();
    previous54=*victim->getPosition();
    {
        const TAiData *data=TheAI->getAiData();
        Coord3D delta(*source->getPosition());
        delta.Sub2D(previous54);
        delta.z=0.0f;
        if (delta.length()<data->m_float94+data->m_float90) return STATE_SUCCESS;
    }
    if (Glo012F0239 && TheCRCParameterCheck) bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"CritterDesync: ComputePath19");
    if (!computePath()) return STATE_SUCCESS;
    StateReturnType result=AIInternalMoveToState::onEnter();
    if (Glo012F0239 && TheCRCParameterCheck) bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"CritterDesync: setAdjustDestination(TRUE) 32");
    m_adjustDestinations=true;
    return result;
}
