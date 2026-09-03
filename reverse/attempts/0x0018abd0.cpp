// ?update@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.98 date=2026-09-03
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

class GameLogic
{
public:
    Object *findObjectByID( ObjectID id );
};

extern GameLogic * volatile TheGameLogic;

class TunnelTracker
{
public:
    void updateNemesis( const Object *object );
};

class Player
{
public:
    TunnelTracker *getTunnelSystem() const
    {
        return *(TunnelTracker **)((const unsigned char *)this + 0x22c);
    }
};

class Object
{
public:
    Player *getControllingPlayer() const;
};

class State
{
public:
    unsigned int getID() const
    {
        return *(const unsigned int *)((const unsigned char *)this + 4);
    }
};

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

class AITNGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    volatile ObjectID m_nemesisID;

    __forceinline ObjectID getNemesisID() const
    {
        return m_nemesisID;
    }

    Object *getOwner() const
    {
        return m_owner;
    }
};

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
        ObjectID nemesisID = guardMachine->getNemesisID();
        Object *nemesis = TheGameLogic->findObjectByID(nemesisID);
        Player *ownerPlayer = guardMachine->getOwner()->getControllingPlayer();
        TunnelTracker *tunnels = 0;
        if (ownerPlayer != 0)
            tunnels = ownerPlayer->getTunnelSystem();
        if (tunnels != 0)
            tunnels->updateNemesis(nemesis);
    }
    return m_attackState->update();
}
