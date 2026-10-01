// ?method@Rva0015F0F0@@QAEHXZ
// partial score=0.3498 date=2026-10-01
// cl: /Igame/GameEngine/Source/Common/Thing
// stlport
// Retail 263B. The initial INT3 padding and ILT 000300B7 target the entry;
// the tail virtual jump at +104 ends at +107, before INT3 padding.
// This bank claims no semantic receiver or original method name.
// Direct callees use the independently verified GameLogicFindObjectByID.cpp,
// StateMachine_getGoalObject.cpp, friend_setGoalObject in AIUpdate.cpp,
// and Rva0015EBE0GuardContainQuery.cpp ABI declarations.
#include "GameLogicObjectLookup.h"

class AIUpdateInterface { public: void friend_setGoalObject(Object *); };
class StateMachine { public: Object *getGoalObject(); };
class Rva0015EBE0State { public: int queryGuardContain(); };
extern GameLogic *TheGameLogic;

struct Rva0015F0F0Horde;
struct Rva0015F0F0Contain;
struct Rva0015F0F0Machine;
struct Rva0015F0F0Substate;
struct Rva0015F0F0Condition;

struct Rva0015F0F0Horde {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11C();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12C();
    virtual bool slot130(Object *);
    virtual void slot134();
    virtual void slot138();
    virtual void slot13C();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14C();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15C();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16C();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17C();
    virtual void slot180();
    virtual void slot184();
    virtual void slot188();
    virtual void slot18C();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19C();
    virtual void slot1A0();
    virtual void slot1A4();
    virtual void slot1A8();
    virtual void slot1AC();
    virtual void slot1B0();
    virtual void slot1B4();
    virtual void slot1B8();
    virtual void slot1BC();
    virtual void slot1C0();
    virtual void slot1C4();
    virtual void slot1C8();
    virtual void slot1CC();
    virtual void slot1D0();
    virtual void slot1D4();
    virtual void slot1D8();
    virtual void slot1DC();
    virtual void slot1E0();
    virtual void slot1E4();
    virtual void slot1E8();
    virtual void slot1EC();
    virtual void slot1F0();
    virtual void slot1F4();
    virtual void slot1F8();
    virtual int slot1FC(int);
};
struct Rva0015F0F0Contain {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual Rva0015F0F0Horde *slot68();
};
struct Rva0015F0F0Object {
    char m_at00[0x74]; int m_at74;
    char m_at78[0x90 - 0x78]; unsigned int m_at90;
    char m_at94[0x1fc - 0x94]; Rva0015F0F0Contain *m_at1fc;
    char m_at200[4]; AIUpdateInterface *m_at204;
    char m_at208[0x344 - 0x208]; unsigned char m_at344;
};
struct Rva0015F0F0Machine {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38(Object *);
    char m_at04[12]; Rva0015F0F0Object *m_at10;
    char m_at14[0x50 - 0x14]; int m_at50;
};
struct Rva0015F0F0Condition {
    virtual bool slot00(StateMachine *);
    char m_at04[0x18];
};
struct Rva0015F0F0Substate {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual int slot18();
};
class Rva0015F0F0 {
public:
    int method();
    char m_at00[0x1c]; Rva0015F0F0Machine *m_at1c;
    char m_at20[4]; Rva0015F0F0Condition m_at24;
    Rva0015F0F0Substate *m_at40;
};

int Rva0015F0F0::method()
{
    Rva0015F0F0Machine *machine = m_at1c;
    Rva0015F0F0Object *target = (Rva0015F0F0Object *)TheGameLogic->findObjectByID(machine->m_at50);
    if (target && (target->m_at344 & 1)) target = 0;
    Rva0015F0F0Object *goal = (Rva0015F0F0Object *)((StateMachine *)machine)->getGoalObject();
    if (goal && (goal->m_at344 & 1)) goal = 0;
    Rva0015F0F0Object *owner = m_at1c->m_at10;
    if (!goal)
    {
        if (!target) target = (Rva0015F0F0Object *)((Rva0015EBE0State *)this)->queryGuardContain();
        if (!target) return -1;
        owner->m_at204->friend_setGoalObject((Object *)target);
        m_at1c->m_at50 = target->m_at74;
        m_at1c->slot38((Object *)target);
    }
    if (m_at24.slot00((StateMachine *)m_at1c) || !m_at40) return -1;
    bool flag = ((owner->m_at90 >> 28) & 1) != 0;
    Rva0015F0F0Contain *contain = owner->m_at1fc;
    if (contain)
    {
        Rva0015F0F0Horde *horde = contain->slot68();
        if (horde && target)
        {
            if (horde->slot130((Object *)target)) flag = true;
            if (horde->slot1FC(target->m_at74) == target->m_at74) goto refresh;
        }
    }
    if (flag)
    {
refresh:
        unsigned int frame = *(unsigned int *)((char *)TheGameLogic + 0x3c) + 20;
        unsigned int &deadline = *(unsigned int *)((char *)this + 0x3c);
        if (deadline < frame) deadline = frame;
    }
    return m_at40->slot18();
}
