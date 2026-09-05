// ?onEnter@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardAttackAggressorState::onEnter at
// retail 0x0018AA70.
//
// Fixed from the prior stash: findObjectByID's parameter must be `int` (not
// the ObjectID typedef) to bind the ILT thunk at 0x0001F253 that
// reverse/symbols.csv already carries for the H-mangled overload, and
// TheAIParseDefinitionAI must be `extern "C"` (matching every other landed
// file that touches it), not a mangled C++ global -- both now resolve and
// byte-match through the tunnels->updateNemesis(nemesis) call, 266/279 bytes.
//
// Remaining 13-byte diff is entirely a register-allocation choice (ecx vs
// edx) for evaluating TheGameLogic->getFrame() +
// TheAIParseDefinitionAI->getAiData()->m_guardChaseUnitFrames feeding the
// AIAttackState constructor's `m_exitConditions` argument. Every rephrasing
// tried -- a temp for either operand, an AIData* cache, swapping the operand
// order, dropping const-volatile off getFrame() -- reallocates registers
// across the WHOLE function (not just this expression) and always regresses
// the byte match elsewhere, never improves it. Looks like a whole-function
// MSVC 7.1 scheduling artifact rather than a source-shape bug; the next
// attempt should look for a different overall statement order/variable set
// for the whole function body, not just this one expression.

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

extern "C" AI *TheAIParseDefinitionAI;

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

    Object *nemesis = TheGameLogic->findObjectByID(m_machine->getNemesisID());
    if (nemesis == 0)
        return STATE_SUCCESS;

    Player *ownerPlayer = m_machine->m_owner->getControllingPlayer();
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
