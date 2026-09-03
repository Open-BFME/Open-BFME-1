// readable body of ?onEnter@AIAttackMoveToState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout reconstruction for retail RVA 0x0017A370.

enum StateReturnType { STATE_CONTINUE = 0 };
typedef int CommandSourceType;

struct Rva0017A370Coord3D
{
    int x;
    int y;
    int z;
};

class Object;

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    unsigned char m_pad00[0x204];
    Rva0017A370AI *m_ai;

    Rva0017A370AI *getAI()
    {
        return m_ai;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void clear();
    virtual void slot18();
    virtual void slot1c();
    virtual int setState(int);

    unsigned char m_pad04[0x0c];
    Object *m_owner;
    unsigned char m_pad14[0x0c];
    Object *m_goalObject;
    Rva0017A370Coord3D m_goalPosition;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveToState
{
public:
    virtual StateReturnType onEnter();

    unsigned char m_pad04[0x18];
    StateMachine *m_machine;
    unsigned char m_pad20[0x34];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackMoveToState : public AIMoveToState
{
public:
    virtual StateReturnType onEnter();

    CommandSourceType m_commandSrc;
    StateMachine *m_attackMoveMachine;
    unsigned int m_frameToSleepUntil;
    int m_retryCount;
    Rva0017A370Coord3D m_goalPosition;
    Object *m_goalObject;
};

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
