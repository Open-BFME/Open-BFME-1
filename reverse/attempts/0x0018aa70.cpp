// ?onEnter@AITNGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.99 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardAttackAggressorState::onEnter at
// retail 0x0018AA70. 275 of 279 bytes match; the instruction stream is
// identical to retail end to end, including every branch target, spill slot
// and callee-saved push.
//
// Three changes carried this from the previous bank's 13-byte residue to 4:
//   1. A `machine` local holds m_machine across the findObjectByID call, so
//      the owner is re-read from it (`machine->m_owner`) instead of from
//      `this` again. Retail keeps that pointer in EDI and drops the second
//      `mov eax,[esi+0x1c]`; without the local we emitted three extra bytes
//      and only saved two callee-saved registers instead of retail's three.
//   2. getFrame() reads through a volatile pointer.
//   3. TheAIParseDefinitionAI is declared `AI *volatile`.
// Together 2 and 3 stop MSVC from hoisting the second global load above the
// first dereference, which restores retail's interleaved load order
//   TheGameLogic -> [+0x3c] -> TheAIParseDefinitionAI -> [+0x14] -> [+0x3c].
//
// Remaining 4 bytes at +0x96..+0xa5 are a pure ECX/EDX mirror on those two
// global loads: retail puts TheGameLogic in ECX and TheAIParseDefinitionAI
// in EDX, we get the opposite pair. Instruction order, operands and lengths
// are otherwise identical.
//
// Tried and did not move the mirror: compound `+=`; address-of-field local;
// direct `m_data` member read; a nested scope; locals for either or both
// globals in both definition orders; swapped addition operands; separate
// frame and chase locals in both orders; an AIData* local; an inline getter
// on AIData; an inline getter plus the accessor; a volatile read inside
// getAiData; volatile on TheGameLogic (loses a byte and 99 more diffs);
// `extern "C"` on TheGameLogic; a leading dummy member on GameLogic;
// declaration order of the two globals; a static inline free function for
// the whole deadline; a setter on TunnelNetworkExitConditions; explicit
// casts on either operand; and /EHsc- and /EHa instead of /EHsc.

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
        return *(const volatile unsigned int *)((const volatile unsigned char *)this + 0x3c);
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

extern "C" AI *volatile TheAIParseDefinitionAI;

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

    BfmeGuardMachine *machine = m_machine;
    Object *nemesis = TheGameLogic->findObjectByID(machine->getNemesisID());
    if (nemesis == 0)
        return STATE_SUCCESS;

    Player *ownerPlayer = machine->m_owner->getControllingPlayer();
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
