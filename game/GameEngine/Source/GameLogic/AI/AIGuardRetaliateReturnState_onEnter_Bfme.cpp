typedef unsigned int UnsignedInt;
typedef bool Bool;

enum StateReturnType
{
    STATE_RETURN_DEFAULT
};

struct Coord3D
{
    float x;
    float y;
    float z;
};

class LocomotorSet
{
    unsigned char m_data[4];
};

class Object;

class Pathfinder
{
public:
    Bool adjustDestination(Object *owner, const LocomotorSet &locomotors,
                           Coord3D *destination, const Coord3D *source = 0);
};

class AIData
{
public:
    unsigned char m_pad00[0x44];
    UnsignedInt m_guardEnemyReturnScanRate;
};

class AI
{
public:
    unsigned char m_pad00[0x0c];
    Pathfinder *m_pathfinder;
    unsigned char m_pad10[4];
    AIData *m_aiData;

    Pathfinder *pathfinder() const
    {
        return m_pathfinder;
    }

    AIData *getAiData() const
    {
        return m_aiData;
    }
};

extern AI *TheAI;

class GameLogic
{
public:
    unsigned char m_pad00[0x3c];
    UnsignedInt m_frame;

    UnsignedInt getFrame() const
    {
        return m_frame;
    }
};

extern GameLogic *TheBfmeGameLogic;

template<int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
    virtual void unusedSlot(char (*)[N]);
};

template<>
class AIUpdateVirtualSlots<0>
{
};

class AIUpdateInterface : public AIUpdateVirtualSlots<123>
{
public:
    virtual Bool isDoingGroundMovement() const;

    const LocomotorSet &getLocomotorSet() const
    {
        return m_locomotorSet;
    }

private:
    unsigned char m_pad04[0x1a8 - 4];
    LocomotorSet m_locomotorSet;
};

template<int N>
class ContainModuleVirtualSlots : public ContainModuleVirtualSlots<N - 1>
{
public:
    virtual void unusedSlot(char (*)[N]);
};

template<>
class ContainModuleVirtualSlots<0>
{
};

class ContainPosition;

class ContainModuleInterface : public ContainModuleVirtualSlots<26>
{
public:
    virtual ContainPosition *getContainedPosition();
};

template<int N>
class ContainPositionVirtualSlots : public ContainPositionVirtualSlots<N - 1>
{
public:
    virtual void unusedSlot(char (*)[N]);
};

template<>
class ContainPositionVirtualSlots<0>
{
};

class ContainPosition : public ContainPositionVirtualSlots<5>
{
public:
    virtual void onObjectWantsToEnterOrExit(int wantsToEnter);
};

class Object
{
public:
    unsigned char m_pad00[0x1fc];
    ContainModuleInterface *m_contain;
    unsigned char m_pad200[4];
    AIUpdateInterface *m_aiUpdate;

    AIUpdateInterface *getAIUpdateInterface() const
    {
        return m_aiUpdate;
    }
};

class AIGuardRetaliateMachine
{
public:
    unsigned char m_pad00[0x10];
    Object *m_owner;
    unsigned char m_pad14[0x30];
    Coord3D m_positionToGuard;

    const Coord3D *getPositionToGuard() const
    {
        return &m_positionToGuard;
    }
};

class AIInternalMoveToState
{
public:
    virtual StateReturnType onEnter();
};

class AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
    virtual StateReturnType onEnter();

private:
    unsigned char m_pad04[0x18];
    AIGuardRetaliateMachine *m_machine;
    unsigned char m_pad20[4];
    Coord3D m_goalPosition;
    unsigned char m_pad30[0x1c];
    Bool m_adjustsDestination;
    unsigned char m_pad4d[3];
    UnsignedInt m_nextReturnScanTime;
};

extern int GetGameLogicRandomValue(int minimum, int maximum, char *file, int line);
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);

StateReturnType AIGuardRetaliateReturnState::onEnter()
{
    UnsignedInt now = TheBfmeGameLogic->getFrame();
#line 248 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGuardRetaliate.cpp"
    m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, __FILE__, __LINE__);
#line 249 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGuardRetaliate.cpp"
    m_goalPosition = *m_machine->getPositionToGuard();

    AIUpdateInterface *ai = m_machine->m_owner->getAIUpdateInterface();
    if (ai && ai->isDoingGroundMovement())
    {
        TheAI->pathfinder()->adjustDestination(m_machine->m_owner,
            ai->getLocomotorSet(), &m_goalPosition);
    }
    ContainModuleInterface *contain = m_machine->m_owner->m_contain;
    if (contain)
    {
        ContainPosition *position = contain->getContainedPosition();
        if (position)
        {
            position->onObjectWantsToEnterOrExit(0);
        }
    }
    if (g_012F0239 && g_012ED4FC)
    {
        bfmeRetailCritterDesyncLog(g_012ED4FC,
            "CritterDesync: setAdjustDestination(TRUE) 4");
    }
    m_adjustsDestination = true;
    return AIInternalMoveToState::onEnter();
}
