// ?onEnter@AITNGuardOuterState@@UAE?AW4StateReturnType@@XZ
// partial score=0.98 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardOuterState::onEnter at 0x0018A6C0.

typedef int ObjectID;

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1
};

class Object;

class GameLogic
{
public:
    Object *findObjectByID( int id );

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
    volatile unsigned int m_guardChaseUnitFrames;
};

class AI
{
public:
    unsigned char m_fields[0x14];
    AIData *m_data;

    AIData *getAiData()
    {
        return m_data;
    }
};

extern "C" AI *TheAIParseDefinitionAI;

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
    virtual bool shouldExit( const StateMachine * ) const
    {
        return false;
    }

    unsigned int m_attackGiveUpFrame;
};

class BfmeAIAttackState
{
public:
    BfmeAIAttackState( StateMachine *, bool, bool, bool,
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

    StateMachine *getMachine()
    {
        return m_machine;
    }
};

class BfmeGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    ObjectID m_nemesisID;
    int m_guardMode;
};

class AITNGuardOuterState
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
    BfmeAIAttackState *m_attackState;
};

// ?onEnter@AITNGuardOuterState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardOuterState::onEnter()
{
    int guardMode = m_machine->m_guardMode;
    if (guardMode == 1)
        return STATE_SUCCESS;

    int nemesisID = m_machine->m_nemesisID;
    GameLogic *logic = TheGameLogic;
    Object *nemesis = logic->findObjectByID(nemesisID);
    if (nemesis == 0)
        return STATE_SUCCESS;

    AI *ai = TheAIParseDefinitionAI;
    AIData *aiData = ai->getAiData();
    unsigned int gameFrame = logic->getFrame();
    m_exitConditions.m_attackGiveUpFrame =
        gameFrame + aiData->m_guardChaseUnitFrames;
    m_attackState = new BfmeAIAttackState(
        (StateMachine *)m_machine, false, true, false, &m_exitConditions );
    m_attackState->getMachine()->setGoalObject(nemesis);

    StateReturnType result = m_attackState->onEnter();
    if (result == STATE_CONTINUE)
        return STATE_CONTINUE;
    return STATE_SUCCESS;
}
