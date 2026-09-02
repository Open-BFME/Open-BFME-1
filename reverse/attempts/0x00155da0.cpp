// ?groupAttackObjectPrivate@AIGroup@@AAEX_NPAVObject@@HW4CommandSourceType@@@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int size_t;

void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

class Object;
enum CommandSourceType
{
};

enum AbleToAttackType
{
    ATTACK_NEW_TARGET = 0,
    ATTACK_NEW_TARGET_FORCED = 1
};

enum CanAttackResult
{
    ATTACKRESULT_NOT_POSSIBLE,
    ATTACKRESULT_INVALID_SHOT,
    ATTACKRESULT_POSSIBLE_AFTER_MOVING,
    ATTACKRESULT_POSSIBLE
};

enum IterOrderType
{
    ITER_SORTED_NEAR_TO_FAR = 1
};

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
    void aiAttackObject(Object *, CommandSourceType);
};

class AIUpdatePrefix
{
public:
    char m_unmodelled[0x20];
};

class AIUpdateInterface : public AIUpdatePrefix, public AICommandInterface
{
protected:
    virtual void privateMoveToPosition();
    virtual void privateAttackObject();
    virtual void privateForceAttackObject();

public:
    virtual AIUpdateInterface *getAIUpdateInterface();
};

class Object
{
public:
    const Coord3D *getPosition() const { return &m_position; }
    ContainModuleInterface *getContain() const { return m_contain; }
    SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
    AIUpdateInterface *getAI() const { return m_ai; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,
        const Object *, CommandSourceType) const;
    Bool bfmeIsGiantBird() const;

private:
    char m_unmodelled_000[0x38];
    Coord3D m_position;
    char m_unmodelled_044[0x160];
    Int m_disabledMask;
    char m_unmodelled_1a8[0x54];
    ContainModuleInterface *m_contain;
    char m_unmodelled_200[0x04];
    AIUpdateInterface *m_ai;
};

class ActionManager
{
public:
    CanAttackResult getCanAttackObject(const Object *, const Object *,
        CommandSourceType, AbleToAttackType);
};

extern ActionManager *TheActionManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
    void groupAttackObjectPrivate(bool, Object *, int, CommandSourceType);
};

class AIGroupGroupAttackObjectPrivateShim
{
public:
    void attack(bool forced, Object *target, int maxShots, CommandSourceType source);

private:
    char m_unmodelled_000[4];
    std::list<Object *> m_memberList;
};

void AIGroupGroupAttackObjectPrivateShim::attack(bool forced, Object *victim,
    int maxShotsToFire, CommandSourceType cmdSource)
{
    if (!victim)
        return;

    Coord3D victimPos;
    victimPos.x = victim->getPosition()->x;
    victimPos.y = victim->getPosition()->y;
    SimpleObjectIterator *iter = new(SimpleObjectIterator::SIMPLE_OBJECT_ITERATOR_GLUE_NOT_IMPLEMENTED) SimpleObjectIterator;

    std::list<Object *>::iterator i;
    for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
        Real dx, dy;
        Coord3D unitPos;
        unitPos.x = (*i)->getPosition()->x;
        unitPos.y = (*i)->getPosition()->y;
        if ((*(const unsigned char *)((const char *)(*i) + 0x1a4) & 0x08) != 0)
            continue;
        dx = unitPos.x - victimPos.x;
        dy = unitPos.y - victimPos.y;
        iter->insert((*i), dx * dx + dy * dy);
    }

    iter->sort(ITER_SORTED_NEAR_TO_FAR);
    Object *theUnit;
    for (theUnit = iter->first(); theUnit; theUnit = iter->next()) {
        ContainModuleInterface *contain = theUnit->getContain();
        if (contain && contain->isPassengerAllowedToFire()) {
            const std::list<Object *> *items = contain->getContainedItemsList();
            if (items) {
                std::list<Object *>::const_iterator it;
                for (it = items->begin(); it != items->end(); ++it) {
                    Object *garrisonedMember = *it;
                    const AbleToAttackType attackType =
                        forced ? ATTACK_NEW_TARGET_FORCED : ATTACK_NEW_TARGET;
                    CanAttackResult result =
                        garrisonedMember->getAbleToAttackSpecificObject(
                            attackType, victim, cmdSource);
                    if (result == ATTACKRESULT_POSSIBLE ||
                        result == ATTACKRESULT_POSSIBLE_AFTER_MOVING) {
                        AIUpdateInterface *memberAI = garrisonedMember->getAI();
                        if (memberAI) {
                            if (forced) {
                                memberAI->aiForceAttackObject(victim, maxShotsToFire,
                                    cmdSource);
                            } else {
                                memberAI->aiAttackObject(victim, maxShotsToFire,
                                    cmdSource);
                            }
                        }
                    }
                }
            }
        }

        SpawnBehaviorInterface *spawnInterface = theUnit->getSpawnBehaviorInterface();
        if (spawnInterface)
            spawnInterface->orderSlavesToAttackTarget(victim, maxShotsToFire, cmdSource);

        AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
        if (ai && theUnit != victim) {
            if (theUnit->bfmeIsGiantBird()) {
                CanAttackResult result = TheActionManager->getCanAttackObject(
                    theUnit, victim, cmdSource, ATTACK_NEW_TARGET);
                if (result == ATTACKRESULT_POSSIBLE ||
                    result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
                    ai->aiAttackObject(victim, cmdSource);
            } else if (forced) {
                ai->aiForceAttackObject(victim, maxShotsToFire, cmdSource);
            } else {
                ai->aiAttackObject(victim, maxShotsToFire, cmdSource);
            }
        }
    }
}

void AIGroup::groupAttackObjectPrivate(bool forced, Object *target, int maxShots, CommandSourceType source)
{
    ((AIGroupGroupAttackObjectPrivateShim *)this)->attack(forced, target, maxShots, source);
}
