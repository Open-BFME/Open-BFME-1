// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Authentic constructors for the two worker master-state wrappers.  Their
// definitions come directly from WorkerAIUpdate.cpp; this focused TU keeps the
// retail out-of-line constructor bodies available even though the full source
// inlines them into WorkerStateMachine's constructor.
#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);
	virtual void stateAnchor(void);
};

class ActAsDozerState : public State
{
public:
	ActAsDozerState(StateMachine *machine);
	virtual void stateAnchor(void);
};

class ActAsSupplyTruckState : public State
{
public:
	ActAsSupplyTruckState(StateMachine *machine);
	virtual void stateAnchor(void);
};

ActAsDozerState::ActAsDozerState(StateMachine *machine) :
	State(machine, AsciiString("ActAsDozerState"))
{
}

ActAsSupplyTruckState::ActAsSupplyTruckState(StateMachine *machine) :
	State(machine, AsciiString("ActAsSupplyTruckState"))
{
}
