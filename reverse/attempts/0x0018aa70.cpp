// ?onEnter@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.98 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardAttackAggressorState::onEnter at
// retail 0x0018AA70.

typedef unsigned int ObjectID;

class Object;
class Player;

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1
};

class GameLogic
{
public:
    Object *findObjectByID( ObjectID id );
    unsigned int getFrame() const volatile
    {
        return *(const unsigned int *)((const unsigned char *)this + 0x3c);
    }
};

extern GameLogic *TheGameLogic;

class AIData
{
public:
    unsigned char m_fields[0x3c];
    unsigned int m_guardChaseUnitFrames;
};

class AI
{
public:
    unsigned char m_fields[0x14];
    AIData *m_data;

    AIData *getAiData() const
    {
        return m_data;
    }
};

extern AI * volatile TheAIParseDefinitionAI;

class DamageInfo
{
public:
    unsigned char m_fields[8];
    ObjectID m_sourceID;
};

class BodyModule
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual const DamageInfo *getLastDamageInfo() const;
};

class Team;

class Object
{
public:
    BodyModule *getBodyModule() const
    {
        return *(BodyModule **)((const unsigned char *)this + 0x200);
    }

    Player *getControllingPlayer() const;
};

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

class StateMachine
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void setGoalObject( const Object *object );
};

class AttackExitConditionsInterface
{
public:
    virtual bool shouldExit( const StateMachine *machine ) const = 0;
};

class TunnelNetworkExitConditions : public AttackExitConditionsInterface
{
public:
    virtual bool shouldExit( const StateMachine * ) const { return false; }
    unsigned int m_attackGiveUpFrame;
};

class AIAttackState
{
public:
    AIAttackState( StateMachine *, bool, bool, bool,
        AttackExitConditionsInterface * );

    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual StateReturnType onEnter();
    virtual void slot04();
    virtual StateReturnType update();

    unsigned char m_fields[0x18];
    StateMachine *m_machine;
    unsigned char m_tail[0x34];
};

class BfmeGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    ObjectID m_nemesisID;

    ObjectID getNemesisID() const
    {
        return m_nemesisID;
    }
};

class AITNGuardAttackAggressorState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual StateReturnType onEnter();

    unsigned char m_stateFields[0x18];
    BfmeGuardMachine *m_machine;
    unsigned char m_unused20[4];
    TunnelNetworkExitConditions m_exitConditions;
    AIAttackState *m_attackState;
};

// ?onEnter@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardAttackAggressorState::onEnter()
{
    ObjectID nemID = (ObjectID)-1;
    Object *obj = m_machine->m_owner;
    if (obj->getBodyModule() != 0 &&
        obj->getBodyModule()->getLastDamageInfo()->m_sourceID != 0)
    {
        nemID = obj->getBodyModule()->getLastDamageInfo()->m_sourceID;
        m_machine->m_nemesisID = nemID;
    }

    BfmeGuardMachine *guard = m_machine;
    Object *nemesis = TheGameLogic->findObjectByID(guard->getNemesisID());
    if (nemesis == 0)
        return STATE_SUCCESS;

    Player *ownerPlayer = guard->m_owner->getControllingPlayer();
    TunnelTracker *tunnels = 0;
    if (ownerPlayer != 0)
        tunnels = ownerPlayer->getTunnelSystem();
    if (tunnels != 0)
        tunnels->updateNemesis(nemesis);

    m_exitConditions.m_attackGiveUpFrame =
        TheGameLogic->getFrame() +
        TheAIParseDefinitionAI->getAiData()->m_guardChaseUnitFrames;
    m_attackState = new AIAttackState(
        (StateMachine *)m_machine, true, true, false, &m_exitConditions );
    m_attackState->m_machine->setGoalObject(nemesis);

    StateReturnType result = m_attackState->onEnter();
    if (result == STATE_CONTINUE)
        return STATE_CONTINUE;
    return STATE_SUCCESS;
}
