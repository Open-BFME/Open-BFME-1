// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Native BFME constructor/layout view. The full SupplyTruckAIUpdate.cpp uses
// Zero Hour State and StateMachine headers with different layouts/signatures.
// Identity and ABI evidence: targets/game/reverse/identity_evidence/002C6430-supply-truck-constructor.md
// These virtual declarations select the existing retail vtables; they do not
// claim the complete virtual interfaces. State is 0x24 and StateMachine 0x44.
#include "ascii_string.h"
class Object;
class StateMachine;
class State {
public:
    State(StateMachine *, AsciiString);
    virtual ~State();
private:
    char m_04[0x20]; // Retail State constructor initializes through +0x20.
};
typedef bool (*StateTransFuncPtr)(State *, void *);
struct StateConditionInfo {
    StateTransFuncPtr test;
    unsigned int toStateID;
    void *userData;
    StateConditionInfo(StateTransFuncPtr t, unsigned int id, void *ud) : test(t), toStateID(id), userData(ud) {}
};
class StateMachine {
public:
    StateMachine(Object *, AsciiString, bool = false);
    virtual ~StateMachine();
protected:
    void defineState(unsigned int, State *, unsigned int, unsigned int, const StateConditionInfo *);
    char m_04[0x40];
};
class SupplyTruckStateMachine : public StateMachine {
public:
    SupplyTruckStateMachine(Object *);
    virtual ~SupplyTruckStateMachine();
    static bool ownerIdle(State *, void *);
    static bool ownerDocking(State *, void *);
    // BFME-only condition: owner AI state equals 0x2f. Semantic name unproved.
    static bool condition002C5BE0(State *, void *);
    static bool isForcedIntoBusyState(State *, void *);
    static bool isForcedIntoWantingState(State *, void *);
    static bool ownerNotDockingOrIdle(State *, void *);
    static bool ownerAvailableForSupplying(State *, void *);
};
class SupplyTruckBusyState : public State {
public:
    SupplyTruckBusyState(StateMachine *m) : State(m, AsciiString("SupplyTruckBusyState")) {}
    virtual ~SupplyTruckBusyState();
};
class SupplyTruckIdleState : public State {
public:
    SupplyTruckIdleState(StateMachine *m) : State(m, AsciiString("SupplyTruckIdleState")) {}
    virtual ~SupplyTruckIdleState();
};
class SupplyTruckWantsToPickUpOrDeliverBoxesState : public State {
public:
    SupplyTruckWantsToPickUpOrDeliverBoxesState(StateMachine *m) : State(m, AsciiString("SupplyTruckWantsToPickUpOrDeliverBoxesState")) {}
    virtual ~SupplyTruckWantsToPickUpOrDeliverBoxesState();
};
class RegroupingState : public State {
public:
    RegroupingState(StateMachine *m) : State(m, AsciiString("RegroupingState")) {}
    virtual ~RegroupingState();
};
class DockingState : public State {
public:
    DockingState(StateMachine *m) : State(m, AsciiString("DockingState")) {}
    virtual ~DockingState();
};
class HarvestingState : public State {
public:
    HarvestingState(StateMachine *m) : State(m, AsciiString("HarvestingState")) {}
    virtual ~HarvestingState();
};
SupplyTruckStateMachine::SupplyTruckStateMachine(Object *owner)
    : StateMachine(owner, AsciiString("SupplyTruckStateMachine"), false)
{
    static const StateConditionInfo busyConditions[] = {
        StateConditionInfo(ownerIdle, 0, 0),
        StateConditionInfo(ownerDocking, 4, 0),
        StateConditionInfo(condition002C5BE0, 5, 0),
        StateConditionInfo(0, 0, 0)
    };
    static const StateConditionInfo idleConditions[] = {
        StateConditionInfo(isForcedIntoBusyState, 1, 0),
        StateConditionInfo(isForcedIntoWantingState, 2, 0),
        StateConditionInfo(ownerDocking, 4, 0),
        StateConditionInfo(condition002C5BE0, 5, 0),
        StateConditionInfo(ownerNotDockingOrIdle, 1, 0),
        StateConditionInfo(0, 0, 0)
    };
    static const StateConditionInfo wantingConditions[] = {
        StateConditionInfo(ownerDocking, 4, 0),
        StateConditionInfo(condition002C5BE0, 5, 0),
        StateConditionInfo(ownerNotDockingOrIdle, 1, 0),
        StateConditionInfo(0, 0, 0)
    };
    static const StateConditionInfo regroupingConditions[] = {
        StateConditionInfo(ownerIdle, 0, 0),
        StateConditionInfo(ownerDocking, 4, 0),
        StateConditionInfo(condition002C5BE0, 5, 0),
        StateConditionInfo(0, 0, 0)
    };
    static const StateConditionInfo dockingConditions[] = {
        StateConditionInfo(isForcedIntoBusyState, 1, 0),
        StateConditionInfo(ownerAvailableForSupplying, 2, 0),
        StateConditionInfo(ownerNotDockingOrIdle, 1, 0),
        StateConditionInfo(0, 0, 0)
    };
    defineState(1, new SupplyTruckBusyState(this), 1, 1, busyConditions);
    defineState(0, new SupplyTruckIdleState(this), 1, 1, idleConditions);
    defineState(2, new SupplyTruckWantsToPickUpOrDeliverBoxesState(this), 1, 3, wantingConditions);
    defineState(3, new RegroupingState(this), 2, 1, regroupingConditions);
    defineState(4, new DockingState(this), 1, 1, dockingConditions);
    defineState(5, new HarvestingState(this), 1, 1, dockingConditions);
}
