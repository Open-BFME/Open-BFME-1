// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME layout reconstruction of AITNGuardAttackAggressorState::update at
// retail 0x0018ABD0.

typedef int ObjectID;

enum StateReturnType
{
    STATE_CONTINUE = 0
};

class Object;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    Object *findObjectByID( ObjectID id );
};

extern GameLogic * volatile TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
    void updateNemesis( const Object *object );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
    TunnelTracker *getTunnelSystem() const
    {
        return *(TunnelTracker **)((const unsigned char *)this + 0x22c);
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
    unsigned int getID() const
    {
        return *(const unsigned int *)((const unsigned char *)this + 4);
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
    unsigned char m_fields[0x1c];
    State *m_currentState;

    State *getCurrentState() const
    {
        return m_currentState;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual StateReturnType update();

    unsigned char m_fields[0x18];
    StateMachine *m_machine;

    State *getCurrentState() const
    {
        return *(State **)((unsigned char *)m_machine + 0x1c);
    }

    StateMachine *getMachine() const
    {
        return m_machine;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
class AITNGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    ObjectID m_nemesisID;

    Object *getOwner() const
    {
        return m_owner;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
class AITNGuardAttackAggressorState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual StateReturnType update();

private:
    unsigned char m_stateFields04[0x18];
    AITNGuardMachine *m_machine;
    unsigned char m_exitConditions[0xc];
    AIAttackState *m_attackState;
};

// ?update@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardAttackAggressorState::update()
{
    StateMachine *attackMachine = *(StateMachine **)((unsigned char *)m_attackState + 0x1c);
    if (attackMachine->getCurrentState() != 0 &&
        attackMachine->getCurrentState()->getID() == 0x67)
    {
        AITNGuardMachine *guardMachine = m_machine;
        Object *nemesis =
            (*TheGameLogic).findObjectByID(guardMachine->m_nemesisID);
        Player *ownerPlayer = guardMachine->getOwner()->getControllingPlayer();
        if (ownerPlayer != 0)
        {
            TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
            if (tunnels != 0)
                tunnels->updateNemesis(nemesis);
        }
    }
    return m_attackState->update();
}
