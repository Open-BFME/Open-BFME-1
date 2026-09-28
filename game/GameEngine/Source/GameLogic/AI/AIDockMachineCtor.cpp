// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

class Object;
class StateMachine;
class State;
typedef bool (*StateTransFuncPtr)(State *, void *);
struct StateConditionInfo
{
    StateTransFuncPtr test;
    unsigned int toStateID;
    void *userData;
    StateConditionInfo(StateTransFuncPtr t, unsigned int id, void *ud)
        : test(t), toStateID(id), userData(ud) {}
};

// BFME StateMachine: one vptr; constructor 0x000A1BD0 stores through +0x42.
// The ZH header has a different multiple-inheritance layout.
class StateMachine
{
public:
    StateMachine(Object *, AsciiString, bool);
    virtual ~StateMachine();
protected:
    void defineState(unsigned int, State *, unsigned int, unsigned int,
                     const StateConditionInfo * = 0);
private:
    char m_storage04[0x40];
};

// Layout is shared with the landed AIInternalMoveToStateCtor.cpp:
// State is 0x24 bytes and AIInternalMoveToState is 0x50 bytes.
class State
{
public:
    State(StateMachine *, AsciiString);
    virtual ~State();
private:
    char m_storage04[0x20];
};
class AIInternalMoveToState : public State
{
public:
    AIInternalMoveToState(StateMachine *, AsciiString);
    virtual ~AIInternalMoveToState();
private:
    char m_storage24[0x2c];
};

class AIDockApproachState : public AIInternalMoveToState
{
public:
    AIDockApproachState(StateMachine *m) : AIInternalMoveToState(m, "AIDockApproachState") {}
protected:
    virtual ~AIDockApproachState();
};
class AIDockWaitForClearanceState : public State
{
public:
    AIDockWaitForClearanceState(StateMachine *m) : State(m, "AIDockWaitForClearanceState"), m_enterFrame(0) {}
protected:
    virtual ~AIDockWaitForClearanceState();
    unsigned int m_enterFrame;
};
class AIDockAdvancePositionState : public AIInternalMoveToState
{
public:
    AIDockAdvancePositionState(StateMachine *m) : AIInternalMoveToState(m, "AIDockApproachState") {}
protected:
    virtual ~AIDockAdvancePositionState();
};
class AIDockMoveToEntryState : public AIInternalMoveToState
{
public:
    AIDockMoveToEntryState(StateMachine *m) : AIInternalMoveToState(m, "AIDockMoveToEntryState") {}
protected:
    virtual ~AIDockMoveToEntryState();
};
class AIDockMoveToDockState : public AIInternalMoveToState
{
public:
    AIDockMoveToDockState(StateMachine *m) : AIInternalMoveToState(m, "AIDockMoveToDockState") {}
protected:
    virtual ~AIDockMoveToDockState();
};
class AIDockProcessDockState : public State
{
public:
    AIDockProcessDockState(StateMachine *m) : State(m, "AIDockProcessDockState"), m_nextDockActionFrame(0), m_droneID(0) {}
    unsigned int m_nextDockActionFrame;
protected:
    virtual ~AIDockProcessDockState();
private:
    unsigned int m_droneID;
};
class AIDockMoveToExitState : public AIInternalMoveToState
{
public:
    AIDockMoveToExitState(StateMachine *m) : AIInternalMoveToState(m, "AIDockMoveToExitState") {}
protected:
    virtual ~AIDockMoveToExitState();
};
class AIDockMoveToRallyState : public AIInternalMoveToState
{
public:
    AIDockMoveToRallyState(StateMachine *m) : AIInternalMoveToState(m, "AIDockMoveToRallyState") {}
protected:
    virtual ~AIDockMoveToRallyState();
};

class AIDockMachine : public StateMachine
{
public:
    AIDockMachine(Object *);
    static bool ableToAdvance(State *, void *);
    int m_approachPosition;
protected:
    virtual ~AIDockMachine();
};

// Identity: matched AIDockState::onEnter and ::xfer call ILT 0x00014F15;
// retail installs AIDockMachine vtable 0x01095A38. Ported from GeneralsMD AIDock.cpp.
AIDockMachine::AIDockMachine(Object *obj) : StateMachine(obj, "AIDockMachine", false)
{
    static const StateConditionInfo waitForClearanceConditions[] = {
        StateConditionInfo(ableToAdvance, 2, 0),
        StateConditionInfo(0, 0, 0)
    };
    defineState(0, new AIDockApproachState(this), 1, 9999);
    defineState(1, new AIDockWaitForClearanceState(this), 3, 9999, waitForClearanceConditions);
    defineState(2, new AIDockAdvancePositionState(this), 1, 9999);
    defineState(3, new AIDockMoveToEntryState(this), 4, 6);
    defineState(4, new AIDockMoveToDockState(this), 5, 6);
    defineState(5, new AIDockProcessDockState(this), 6, 6);
    defineState(6, new AIDockMoveToExitState(this), 7, 9999);
    defineState(7, new AIDockMoveToRallyState(this), 9998, 9999);
    m_approachPosition = -1;
}
