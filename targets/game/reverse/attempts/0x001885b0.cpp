// ?d_001885b0@@YAXXZ
// partial score=0.6 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// readable bodies of AIAttackMoveToState::onEnter and update: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout reconstruction for retail RVAs 0x0017A370 and 0x001885B0.

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1 };
typedef int CommandSourceType;

struct Rva0017A370Coord3D
{
    float x;
    float y;
    float z;
    float GetLengthEstimate() const;
};

class Object;
class BfmeCurrentState
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual bool isIdle() const;
};

class AIUpdateInterface;

class BfmeGameLogic
{
public:
    unsigned char m_pad[0x3c];
    unsigned int m_frame;
    Object *findObjectByID(int id);
};

#define BFME_LOGIC (*(BfmeGameLogic **)0x012F0898)
#define BFME_REPATH_DISTANCE (*(const float *)0x01075344)
#define BFME_CLOSE_ENOUGH_SQUARED (*(const float *)0x0109B3FC)

template <int N>
class Rva0017A370VirtualSlots : public Rva0017A370VirtualSlots<N - 1>
{
public:
    virtual void slot(char (*)[N]);
};
template <> class Rva0017A370VirtualSlots<0> {};

class Rva0017A370AI : public Rva0017A370VirtualSlots<128>
{
public:
    virtual CommandSourceType getLastCommandSource() const;
    Object *checkForCrateToPickup();
    Object *getNextMoodTarget(bool includeCurrent, bool includeFriends);
    void friend_endingMove();

    unsigned char m_pad04[0x48 - 4];
    CommandSourceType m_commandSrc;
    unsigned char m_pad4c[0x335 - 0x4c];
    bool m_retargeted;
};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    unsigned char m_pad00[0x38];
    Rva0017A370Coord3D m_position;
    unsigned char m_pad44[0x204 - 0x44];
    Rva0017A370AI *m_ai;

    Rva0017A370AI *getAI()
    {
        return m_ai;
    }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual int updateStateMachine();
    virtual void clear();
    virtual void slot18();
    virtual void slot1c();
    virtual int setState(int);
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void setGoalObject(Object *);
    void setGoalPosition(const Rva0017A370Coord3D *);
    Object *getGoalObject();

    unsigned char m_pad04[0x0c];
    Object *m_owner;
    unsigned char m_pad14[0x08];
    BfmeCurrentState *m_currentState;
    Object *m_goalObject;
    Rva0017A370Coord3D m_goalPosition;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveToState
{
public:
    virtual StateReturnType onEnter();
    virtual StateReturnType update();

    unsigned char m_pad04[0x18];
    StateMachine *m_machine;
    unsigned char m_pad20[0x14];
    Rva0017A370Coord3D m_pathGoalPosition;
    unsigned char m_pad40[0x14];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackMoveToState : public AIMoveToState
{
public:
    virtual StateReturnType onEnter();
    virtual StateReturnType update();


    CommandSourceType m_commandSrc;
    StateMachine *m_attackMoveMachine;
    unsigned int m_frameToSleepUntil;
    int m_retryCount;
    Rva0017A370Coord3D m_goalPosition;
    Object *m_goalObject;
};
static bool inIdleState(StateMachine *machine)
{
    return !machine->m_currentState || machine->m_currentState->isIdle();
}

StateReturnType AIAttackMoveToState::onEnter()
{
    Object *owner = m_machine->m_owner;
    Rva0017A370AI *ai = owner->getAI();
    m_attackMoveMachine->clear();
    m_attackMoveMachine->setState(0);
    m_commandSrc = ai->getLastCommandSource();
    m_retryCount = 5;
    m_frameToSleepUntil = 0;
    StateReturnType result = AIMoveToState::onEnter();
    Object *goal = m_machine->m_goalObject;
    if (goal)
        m_goalObject = goal;
    else
        m_goalPosition = m_machine->m_goalPosition;
    return result;
}

#pragma comment(linker, "/alternatename:?checkForCrateToPickup@Rva0017A370AI@@QAEPAVObject@@XZ=?j_000265a8@@YAXXZ")
#pragma comment(linker, "/alternatename:?getNextMoodTarget@Rva0017A370AI@@QAEPAVObject@@_N0@Z=?j_00003f58@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_endingMove@Rva0017A370AI@@QAEXXZ=?j_00012486@@YAXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@BfmeGameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?GetLengthEstimate@Rva0017A370Coord3D@@QBEMXZ=?j_00036aa2@@YAXXZ")

StateReturnType AIAttackMoveToState::update()
{
    Object *owner = m_machine->m_owner;
    Rva0017A370AI *ai = owner->getAI();
    bool forceRetarget = false;
    bool shouldRepath = false;

    if (!inIdleState(m_attackMoveMachine))
    {
        Object *goal = m_machine->getGoalObject();
        if (goal && goal != m_attackMoveMachine->getGoalObject())
            m_attackMoveMachine->setGoalObject(goal);
        m_attackMoveMachine->updateStateMachine();
        if (!m_attackMoveMachine || !inIdleState(m_attackMoveMachine))
            return STATE_CONTINUE;
        forceRetarget = true;
        shouldRepath = true;
        ai->m_commandSrc = m_commandSrc;
    }

    if (inIdleState(m_attackMoveMachine))
    {
        Object *crate = ai->checkForCrateToPickup();
        if (crate)
        {
            m_attackMoveMachine->setGoalObject(crate);
            m_attackMoveMachine->setState(0x27);
            return STATE_CONTINUE;
        }

        Object *victim = ai->getNextMoodTarget(!forceRetarget, false);
        if (victim)
        {
            ai->friend_endingMove();
            m_attackMoveMachine->setGoalObject(victim);
            m_attackMoveMachine->setState(0x0a);
            ai->m_commandSrc = 2;
            ai->m_retargeted = true;
            return STATE_CONTINUE;
        }
    }

    Rva0017A370Coord3D machineGoal = m_machine->m_goalPosition;
    Rva0017A370Coord3D destination;
    Object *goal = BFME_LOGIC->findObjectByID((int)m_goalObject);
    if (goal)
        destination = goal->m_position;
    else
        destination = m_goalPosition;
    destination.x -= machineGoal.x;
    destination.y -= machineGoal.y;
    destination.z -= machineGoal.z;
    if (!(destination.GetLengthEstimate() < BFME_REPATH_DISTANCE))
    {
        if (goal)
            m_machine->setGoalObject(goal);
        else
            m_machine->setGoalPosition(&m_goalPosition);
        shouldRepath = true;
    }

    if (m_frameToSleepUntil > BFME_LOGIC->m_frame)
        return STATE_CONTINUE;
    if (m_frameToSleepUntil == BFME_LOGIC->m_frame)
        shouldRepath = true;
    if (shouldRepath)
    {
        AIMoveToState::onEnter();
        m_pathGoalPosition.x = -100.0f;
        m_pathGoalPosition.y = -100.0f;
        m_pathGoalPosition.z = -100.0f;
        *(int *)((char *)this + 0x44) = -5;
    }
    StateReturnType result = AIMoveToState::update();
    if (result != STATE_CONTINUE && m_retryCount >= 1)
    {
        float dx = owner->m_position.x - m_pathGoalPosition.x;
        float dy = owner->m_position.y - m_pathGoalPosition.y;
        float distanceSquared = dx * dx + dy * dy;
        if (distanceSquared >= BFME_CLOSE_ENOUGH_SQUARED)
        {
            result = STATE_CONTINUE;
            --m_retryCount;
            m_frameToSleepUntil = BFME_LOGIC->m_frame + 15;
        }
    }
    return result;
}
