// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object
// BuildAssistant slot 16; BFME has a third signed record index.
// Evidence: targets/game/reverse/identity_evidence/000fe3c0-canmakeunit-recovery.md
class Player;
class ProductionUpdateInterface;
enum ObjectScriptStatusBit { OBJECT_STATUS_SCRIPT_DISABLED = 1, OBJECT_STATUS_SCRIPT_UNPOWERED = 2 };
// ?testScriptStatusBit@Object@@QBE_NW4ObjectScriptStatusBit@@@Z absent-from-retail
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; ProductionUpdateInterface *getProductionUpdateInterface(); bool testScriptStatusBit(ObjectScriptStatusBit bit) const { return (m_scriptStatus & bit) != 0; }
#include "object.h"

enum CanMakeType {
    CANMAKE_OK = 0, CANMAKE_NO_PREREQ = 1, CANMAKE_NO_MONEY = 2,
    CANMAKE_FACTORY_IS_DISABLED = 3, CANMAKE_MAXED_OUT_FOR_PLAYER = 6,
    CanMake000FE3C0Capacity = 7
};
enum KindOfType { Kind000FE3C0 = 156 };
class ThingTemplate {
public:
    __declspec(noinline) bool isKindOf(KindOfType) const;
    int calcCostToBuild(const Player *, int) const;
    char field00[0xc8];
    unsigned int m_kindof[6];
    char fieldE0[0x480-0xe0];
    unsigned short m_maxSimultaneousOfType;
};
class ProductionUpdateInterface {
public:
    virtual CanMakeType slot00() = 0;
};
class BfmeBuildIndexSetter {
public:
    int set(int);
};
struct Rva000C7CD0Obj;
class Rva000C7CD0 {
public:
    unsigned char ok(Rva000C7CD0Obj *, int);
};
void j_00002135();
class Resolve000FE3C0 { public: const ThingTemplate *method(int); };
struct BfmeThingEJ;
struct Rva000FC2A0Tally {
    int total;
    int argument;
};
int __cdecl rva000fc2a0Tally(BfmeThingEJ *, Rva000FC2A0Tally *);
typedef void (__cdecl *ObjectIterateFunc)(Object *, void *);
// ?countMoney@Money@@QBEIXZ absent-from-retail
class Money { public: void *field00; unsigned int m_money; unsigned int countMoney() const { return m_money; } };
class Player {
public:
    void iterateObjects(ObjectIterateFunc, void *) const;
    void countObjectsByThingTemplate(int, const ThingTemplate *const *, bool, int *, bool) const;
    char field00[0x48];
    Money m_money;
    // ?getMoney@Player@@QAEPAVMoney@@XZ absent-from-retail
    Money *getMoney() { return &m_money; }
};
class BuildAssistant {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15();
    virtual CanMakeType canMakeUnit(Object *, const ThingTemplate *, int) const;
    virtual bool isPossibleToMakeUnit(Object *, const ThingTemplate *, int) const;
};

// ?canMakeUnit@BuildAssistant@@UBE?AW4CanMakeType@@PAVObject@@PBVThingTemplate@@H@Z
CanMakeType BuildAssistant::canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, int buildIndex) const
{
    if (!builder)
        return CANMAKE_NO_PREREQ;
    if (!whatToBuild && buildIndex == -1)
        return CANMAKE_NO_PREREQ;
    bool fromRecord = buildIndex != -1;
    if (builder->testScriptStatusBit(OBJECT_STATUS_SCRIPT_DISABLED) || builder->testScriptStatusBit(OBJECT_STATUS_SCRIPT_UNPOWERED))
        return CANMAKE_FACTORY_IS_DISABLED;
    if (!isPossibleToMakeUnit(builder, whatToBuild, buildIndex))
        return CANMAKE_NO_PREREQ;
    ProductionUpdateInterface *pu = builder->getProductionUpdateInterface();
    if (pu) {
        CanMakeType result = pu->slot00();
        if (result != CANMAKE_OK)
            return result;
    }
    Player *player = builder->getControllingPlayer();
    if (fromRecord) {
        void *records = (char *)player + 0x684;
        union { void (*raw)(); const ThingTemplate *(Resolve000FE3C0::*member)(int); } resolver;
        resolver.raw = j_00002135;
        unsigned int available = player->getMoney()->countMoney();
        if ((unsigned)((BfmeBuildIndexSetter *)records)->set(buildIndex) > available)
            return CANMAKE_NO_MONEY;
        if (!((Rva000C7CD0 *)((char *)player + 0x30))->ok((Rva000C7CD0Obj *)(((Resolve000FE3C0 *)records)->*resolver.member)(buildIndex), 1))
            return CanMake000FE3C0Capacity;
    } else {
        if (!whatToBuild->isKindOf(Kind000FE3C0)) {
            unsigned int available = player->getMoney()->countMoney();
            if ((unsigned)whatToBuild->calcCostToBuild(player, -1) > available)
                return CANMAKE_NO_MONEY;
        }
        if (!((Rva000C7CD0 *)((char *)player + 0x30))->ok((Rva000C7CD0Obj *)whatToBuild, 1))
            return CanMake000FE3C0Capacity;
    }
    if (whatToBuild && whatToBuild->m_maxSimultaneousOfType != 0) {
        int count;
        player->countObjectsByThingTemplate(1, &whatToBuild, true, &count, false);
        if ((unsigned)count >= whatToBuild->m_maxSimultaneousOfType)
            return CANMAKE_MAXED_OUT_FOR_PLAYER;
        Rva000FC2A0Tally tally;
        tally.argument = (int)whatToBuild;
        tally.total = 0;
        player->iterateObjects((ObjectIterateFunc)rva000fc2a0Tally, &tally);
        if ((unsigned)(count + tally.total) >= whatToBuild->m_maxSimultaneousOfType)
            return CANMAKE_MAXED_OUT_FOR_PLAYER;
    }
    return CANMAKE_OK;
}

// ?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z
inline bool ThingTemplate::isKindOf(KindOfType kind) const
{
    return (m_kindof[(unsigned int)kind >> 5] & (1U << ((unsigned int)kind & 31))) != 0;
}
