// ?attack00155DA0@AIGroupGroupAttackObjectPrivateShim@@QAEX_NPAVObject@@HW4CommandSourceType@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>

#include "../../../Include/Common/ScalarTypes.h"



typedef unsigned int size_t;

void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
#include "../command_source_type.h"

enum DisabledType { DISABLED_HELD = 3 };

#include "../../../Include/Common/Enums/AbleToAttackType.h"





enum CanAttackResult
{
    ATTACKRESULT_NOT_POSSIBLE,
    ATTACKRESULT_INVALID_SHOT,
    ATTACKRESULT_POSSIBLE_AFTER_MOVING,
    ATTACKRESULT_POSSIBLE
};

#include "../../../Include/Common/Enums/IterOrderType.h"




class SimpleObjectIterator
{
protected:
    virtual ~SimpleObjectIterator();

public:
    enum SimpleObjectIteratorMagicEnum
    {
        SIMPLE_OBJECT_ITERATOR_GLUE_NOT_IMPLEMENTED = 0
    };

    inline void *operator new(size_t size, SimpleObjectIteratorMagicEnum)
    {
        return ::operator new(size);
    }

    inline void operator delete(void *object, SimpleObjectIteratorMagicEnum)
    {
        ::operator delete(object);
    }

    virtual Object *first();
    virtual Object *next();

    SimpleObjectIterator();
    void insert(Object *, Real);
    void sort(IterOrderType);

private:
    char m_unmodelled[0x0c];
};

class ContainModuleInterface
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32();
    virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38();
    virtual void slot39();
    virtual Bool isPassengerAllowedToFire() const;
    virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46();
    virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52();
    virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58();
    virtual void slot59(); virtual void slot60(); virtual void slot61();
    virtual void slot62(); virtual void slot63(); virtual void slot64();
    virtual const std::list<Object *> *getContainedItemsList() const;
};

class SpawnBehaviorInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void orderSlavesToAttackTarget(Object *, Int, CommandSourceType);
};

class AICommandInterface
{
public:
    void aiAttackObject(Object *, Int, CommandSourceType);
    void aiForceAttackObject(Object *, Int, CommandSourceType);
    void aiBfmeCommand39(Object *, CommandSourceType);
    // ?aiBfmeAttackObject@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z absent-from-retail
    void aiBfmeAttackObject(Object *victim, CommandSourceType source) { aiBfmeCommand39(victim, source); }
};

class AIUpdateModuleData
{
public:
    char m_unreconstructed_000[0x20];
    UnsignedInt m_autoAcquireEnemiesWhenIdle;
};

class AIUpdateInterface
{
public:
    char m_unreconstructed_000[4];
    AIUpdateModuleData *m_moduleData;
    char m_unreconstructed_008[0x20 - 0x08];
    AICommandInterface m_commands;
};

// Use STLport's bit access on the canonical mask word.
#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS Bool isDisabledByType(DisabledType type) const { return reinterpret_cast<const std::bitset<sizeof(m_disabledMask) * 8> *>(&m_disabledMask)->test(type); } \
    const Coord3D *getPosition() const { return &m_cachedPos; } \
    ContainModuleInterface *getContain() const { return m_contain; } \
    SpawnBehaviorInterface *getSpawnBehaviorInterface() const; \
    AIUpdateInterface *getAI() const { return m_ai; } \
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; } \
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, CommandSourceType) const; \
    int bfmeIsGiantBird() const;
#include "../Object/object.h"

class ActionManager
{
public:
    CanAttackResult getCanAttackObject(const Object *, const Object *,
        CommandSourceType, AbleToAttackType);
};

extern ActionManager *TheActionManager;

class AIGroupGroupAttackObjectPrivateShim
{
public:
    void attack00155DA0(Bool forced, Object *victim,
        Int maxShotsToFire, CommandSourceType cmdSource);

private:
    char m_unmodelled_000[4];
    std::list<Object *> m_memberList;
};

// ?attack00155DA0@AIGroupGroupAttackObjectPrivateShim@@QAEX_NPAVObject@@HW4CommandSourceType@@@Z
void AIGroupGroupAttackObjectPrivateShim::attack00155DA0(Bool forced, Object *victim,
    Int maxShotsToFire, CommandSourceType cmdSource)
{
    if (!victim) {
        // Hard to kill em if they're already dead.  jba
        return;
    }

    Coord3D victimPos;
    victimPos.x = victim->getPosition()->x;
    victimPos.y = victim->getPosition()->y;
    SimpleObjectIterator *iter = ::new SimpleObjectIterator;

    std::list<Object *>::iterator i;
    for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
        Real dx, dy;
        Coord3D unitPos;
        unitPos.x = (*i)->getPosition()->x;
        unitPos.y = (*i)->getPosition()->y;
        if ((*i)->isDisabledByType(DISABLED_HELD))
            continue; // don't bother telling the occupants to move.
        dx = unitPos.x - victimPos.x;
        dy = unitPos.y - victimPos.y;
        iter->insert((*i), dx * dx + dy * dy);
    }

    iter->sort(ITER_SORTED_NEAR_TO_FAR);
    // Works better if you let the near units get the first paths... jba.
    Object *theUnit;
    for (theUnit = iter->first(); theUnit; theUnit = iter->next()) {
        //Determine if this object is a garrisoned container capable of firing!
        //If so, order everyone inside to attack as well!
        ContainModuleInterface *contain = theUnit->getContain();
        if (contain && contain->isPassengerAllowedToFire()) {
            //Loop through each member and order them to attack the same target (if possible)
            const std::list<Object *> *items = contain->getContainedItemsList();
            if (items) {
                std::list<Object *>::const_iterator it;
                for (it = items->begin(); it != items->end(); ++it) {
                    Object *garrisonedMember = *it;
                    CanAttackResult result = garrisonedMember->getAbleToAttackSpecificObject(forced ? ATTACK_NEW_TARGET_FORCED : ATTACK_NEW_TARGET, victim, cmdSource);
                    if (result == ATTACKRESULT_POSSIBLE ||
                        result == ATTACKRESULT_POSSIBLE_AFTER_MOVING) {
                        AIUpdateInterface *memberAI = garrisonedMember->getAI();
                        if (memberAI) {
                            if (forced) {
                                memberAI->m_commands.aiForceAttackObject(victim, maxShotsToFire, cmdSource);
                            } else {
                                memberAI->m_commands.aiAttackObject(victim, maxShotsToFire, cmdSource);
                            }
                        }
                    }
                }
            }
        }

        //Do a check to see if we have a hive object that has slaved objects.
        SpawnBehaviorInterface *spawnInterface = theUnit->getSpawnBehaviorInterface();
        if (spawnInterface)
            spawnInterface->orderSlavesToAttackTarget(victim, maxShotsToFire, cmdSource);

        //Order the specific group object to attack!
        AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
        if (ai && theUnit != victim) {
            if ((unsigned char)theUnit->bfmeIsGiantBird()) {
                CanAttackResult result = TheActionManager->getCanAttackObject(theUnit, victim, cmdSource, ATTACK_NEW_TARGET);
                if (result == ATTACKRESULT_POSSIBLE ||
                    result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
                    ai->m_commands.aiBfmeAttackObject(victim, cmdSource);
            } else if (forced) {
                ai->m_commands.aiForceAttackObject(victim, maxShotsToFire, cmdSource);
            } else {
                ai->m_commands.aiAttackObject(victim, maxShotsToFire, cmdSource);
            }
        }
    }
}
