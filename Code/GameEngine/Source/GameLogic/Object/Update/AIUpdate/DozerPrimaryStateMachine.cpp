// BFME DozerPrimaryStateMachine constructor, reconstructed as clean C++.
// ??0DozerPrimaryStateMachine@@QAE@PAVObject@@@Z
// Retail 0x002B7870..0x002B7A97, 551 bytes; identity is established by
// DozerAIUpdate::createMachines and the GeneralsMD five-state graph.
//
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

class Object;
class State;
typedef unsigned int StateID;
typedef bool (__cdecl *StateTransFuncPtr)(State *, void *);

struct StateConditionInfo
{
    StateTransFuncPtr test;
    StateID toStateID;
    void *userData;

    StateConditionInfo(StateTransFuncPtr t, StateID id, void *ud)
        : test(t), toStateID(id), userData(ud) {}
};

class StateMachine
{
public:
    StateMachine(Object *owner, AsciiString name, bool flag);
    virtual ~StateMachine();

protected:
    void defineState(StateID id, State *state, StateID successID,
        StateID failureID, const StateConditionInfo *conditions);

private:
    unsigned char m_layout[0x40];
};

// This is the existing pinned address-qualified view of State::State.  The
// empty view lets each derived state carry BFME's one-vptr layout explicitly;
// the retail constructor still writes the shared base fields through this ptr.
class Rva000A19E0StateBase
{
public:
    Rva000A19E0StateBase(void *machine, AsciiString name);
};

// Retail condition callbacks are already matched under their canonical names;
// these three ILTs are the exact addresses stored in the guarded table at
// 0x012F025C (the ILTs route to 0x002B6480/64E0/6540 respectively).
extern void j_0002cbc9();
extern void j_00031ceb();
extern void j_000355fd();

class DozerPrimaryIdleState : public Rva000A19E0StateBase
{
public:
    DozerPrimaryIdleState(void *machine)
        : Rva000A19E0StateBase(machine, AsciiString("DozerPrimaryIdleState"))
    {
        m_vftable = reinterpret_cast<int *>(0x010C6F00);
        m_idleTooLongTimestamp = 0;
        m_idlePlayerNumber = 0;
        m_isMarkedAsIdle = false;
    }

private:
    int *volatile m_vftable;
    unsigned char m_gap04[0x20];
    volatile unsigned int m_idleTooLongTimestamp;
    volatile int m_idlePlayerNumber;
    volatile unsigned char m_isMarkedAsIdle;
};

enum DozerTask
{
    DOZER_TASK_INVALID = -1,
    DOZER_TASK_FIRST = 0,
    DOZER_TASK_BUILD = DOZER_TASK_FIRST,
    DOZER_TASK_REPAIR = 1,
    DOZER_TASK_FORTIFY = 2,
    DOZER_NUM_TASKS
};

class DozerActionState
{
public:
    DozerActionState(StateMachine *machine, DozerTask task);

private:
    unsigned char m_layout[0x2c];
};

class DozerPrimaryGoingHomeState : public Rva000A19E0StateBase
{
public:
    DozerPrimaryGoingHomeState(void *machine)
        : Rva000A19E0StateBase(machine,
            AsciiString("DozerPrimaryGoingHomeState"))
    {
        m_vftable = reinterpret_cast<int *>(0x010C6FD8);
    }

private:
    int *volatile m_vftable;
    unsigned char m_gap04[0x20];
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
    DozerPrimaryStateMachine(Object *owner);
};

DozerPrimaryStateMachine::DozerPrimaryStateMachine(Object *owner)
    : StateMachine(owner, AsciiString("DozerPrimaryStateMachine"), false)
{
    *reinterpret_cast<int **>(this) = reinterpret_cast<int *>(0x010C6790);

    static const StateConditionInfo idleConditions[] =
    {
        StateConditionInfo((StateTransFuncPtr)j_0002cbc9, 1, 0),
        StateConditionInfo((StateTransFuncPtr)j_00031ceb, 2, 0),
        StateConditionInfo((StateTransFuncPtr)j_000355fd, 3, 0),
        StateConditionInfo(0, 0, 0)
    };

    defineState(0, (State *)new DozerPrimaryIdleState(this), 999999, 999999,
        idleConditions);
    defineState(1, (State *)new DozerActionState(this, DOZER_TASK_BUILD), 0, 0, 0);
    defineState(2, (State *)new DozerActionState(this, DOZER_TASK_REPAIR), 0, 0, 0);
    defineState(3, (State *)new DozerActionState(this, DOZER_TASK_FORTIFY), 0, 0, 0);
    defineState(4, (State *)new DozerPrimaryGoingHomeState(this), 0, 0, 0);
}
