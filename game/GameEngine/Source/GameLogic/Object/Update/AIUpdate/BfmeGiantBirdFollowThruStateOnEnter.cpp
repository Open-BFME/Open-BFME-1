// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/Common/Thing
// stlport
// Identity and ABI: targets/game/reverse/identity_evidence/002c3b90-followthru-onenter.md

#include "Coord3D.h"
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

class StateMachine
{
public:
    void setGoalPosition(const Coord3D *);
    char m_pad00[0x10];
    Object *m_owner;
};

template<int N> class Rva002C3B90Slots : public Rva002C3B90Slots<N-1>
{ public: virtual void unused(char (*)[N]) = 0; };
template<> class Rva002C3B90Slots<0> {};

enum LocomotorSetType { LOCOMOTORSET_NORMAL = 0 };
enum StateReturnType { STATE_CONTINUE = 0, STATE_FAILURE = -2 };

struct Rva002C3B90Locomotor
{
    char m_pad00[0x44];
    float m_float44;
};

class Rva002C3B90AI : public Rva002C3B90Slots<127>
{
public:
    virtual bool chooseLocomotorSet(LocomotorSetType) = 0;
    char m_pad04[0x1cc-4];
    Rva002C3B90Locomotor *m_curLocomotor;
    char m_pad1d0[0x3f0-0x1d0];
    unsigned m_word3f0;
    char m_pad3f4[8];
    int m_id3fc;
    char m_pad400[0x424-0x400];
    bool m_bool424;
    char m_pad425[0x490-0x425];
    bool m_bool490;
    char m_pad491[3];
    int m_mode494;
    bool test(int bit) const { return (m_word3f0 >> bit) & 1; }
};

struct ModelConditionFlags
{
    unsigned test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
    void set(int bit) { m_bits[bit >> 5] |= (1u << (bit & 31)); }
    void reset(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
    unsigned m_bits[10];
};
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "GameEngine/Source/GameLogic/Object/object.h"

class Rva002BC260GoalOwner
{ public: void run(void *, void *, void *, unsigned char); };
class Rva002C3B90Terrain : public Rva002C3B90Slots<6>
{ public: virtual float slot18(float, float, Coord3D *) = 0; };
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern int g_012F02D4;
extern int g_012F02D8;
extern void j_00033a87();

class BfmeGiantBirdFollowThruState
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual StateReturnType onEnter();
    char m_pad04[0x18];
    StateMachine *m_machine;
    char m_pad20[4];
    bool m_enabled;
    char m_pad25[3];
    int m_counter;
};

// ?onEnter@BfmeGiantBirdFollowThruState@@UAE?AW4StateReturnType@@XZ
StateReturnType BfmeGiantBirdFollowThruState::onEnter()
{
    m_counter = 0;
    Object *owner = m_machine->m_owner;
    if (owner->m_modelConditionFlags.test(145))
    {
        owner->m_modelConditionFlags.reset(145);
        owner->notifyModelConditionChanged();
    }
    Rva002C3B90AI *ai = (Rva002C3B90AI *)owner->m_ai;
    if (ai == 0)
        return STATE_FAILURE;
    ai->m_bool490 = true;
    if (owner->m_privateStatus & 1)
        return STATE_FAILURE;
    ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
    Rva002C3B90Locomotor *locomotor = ai->m_curLocomotor;
    if (locomotor == 0)
        return STATE_FAILURE;
    Coord3D goal;
    bool result = false;
    typedef void (BfmeGiantBirdFollowThruState::*Compute)(Coord3D *, bool *, bool);
    union { void (*fn)(); Compute call; } compute = {j_00033a87};
    (this->*compute.call)(&goal, &result, m_enabled);
    float desired = goal.z + locomotor->m_float44;
    float ground = ((Rva002C3B90Terrain *)TheTerrainLogic)->slot18(goal.x, goal.y, 0);
    float minimum = ground + locomotor->m_float44 * 1.25f;
    if (desired > minimum)
    {
        desired = goal.z + locomotor->m_float44 * 0.25f;
        if (!(desired > minimum))
            desired = minimum;
    }
    goal.z = desired;
    if (ai->m_mode494 != 2)
    {
        goal.z = ground + locomotor->m_float44;
        goal.x = (goal.x + owner->m_cachedPos.x) * 0.5f;
        goal.y = (goal.y + owner->m_cachedPos.y) * 0.5f;
    }
    m_machine->setGoalPosition(&goal);
    if (!result && !ai->test(3))
        ((Rva002BC260GoalOwner *)ai)->run(&goal, &g_012F02D4, 0, 1);
    else
        ((Rva002BC260GoalOwner *)ai)->run(&goal, &g_012F02D8, 0, 1);
    ai->m_word3f0 &= ~8;
    if (!ai->m_bool424)
        return STATE_FAILURE;
    if (ai->test(6) && ai->m_id3fc != 0)
    {
        Object *target = TheGameLogic->findObjectByID(ai->m_id3fc);
        if (target && !(target->m_modelConditionFlags.test(71)))
        {
            target->m_modelConditionFlags.set(71);
            target->notifyModelConditionChanged();
        }
    }
    return STATE_CONTINUE;
}
