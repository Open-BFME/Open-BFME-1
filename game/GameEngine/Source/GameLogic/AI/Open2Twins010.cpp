// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
//
// Two more move-state constructors, landed as relocation-blind twins of
// game/GameEngine/Source/GameLogic/AI/AIMoveAndTightenStateCtorThunk.cpp
// (0x0017F390).  Each differs in two slots: the state-name literal it passes
// up and its own vtable.  The names are in the binary --
// "AIMoveAwayPanicState" and "AIMoveAwayAndCowerState" -- so unlike most of
// this file's neighbours these two carry real identity.
//
// The two stores stay in the BODY, not the initialiser list, and in retail's
// order: the flag at 0x54 before the word at 0x50.  Member initialisation
// follows declaration order and cannot express that.

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	unsigned char m_body[0x2C];
};


class MoveAwayPanicState : public AIInternalMoveToState
{
public:
	MoveAwayPanicState(StateMachine *machine);

private:
	int m_50;
	bool m_54;
};

// @??0MoveAwayPanicState@@QAE@PAVStateMachine@@@Z 0x0017F4A0
MoveAwayPanicState::MoveAwayPanicState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIMoveAwayPanicState")
{
	m_54 = false;
	m_50 = 0;
}

class MoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	MoveAwayAndCowerState(StateMachine *machine);

private:
	int m_50;
	bool m_54;
};

// @??0MoveAwayAndCowerState@@QAE@PAVStateMachine@@@Z 0x00180450
MoveAwayAndCowerState::MoveAwayAndCowerState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIMoveAwayAndCowerState")
{
	m_54 = false;
	m_50 = 0;
}
