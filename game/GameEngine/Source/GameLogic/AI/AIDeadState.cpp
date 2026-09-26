// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Constructor 0x001713C0 installs vtable 0x01097EA0. Its slot-zero ILT
// 0x00042B04 reaches the emitted protected scalar wrapper at 0x0017FF50,
// which calls the complete destructor through existing ILT 0x00047B9F.
// State subclass constructor: build the name, hand it to the base by value,
// install this class's vptr.
//
// The AsciiString is the shim's, not a hand-rolled four-byte stand-in. The
// temporary is passed by value and only the StringBase-backed shim emits
// `mov [esp+8],esp` before `mov ecx,esp` the way retail does; an earlier attempt
// at this family declared its own AsciiString and stalled on that pair alone.
#include "Common/AsciiString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
class AIDeadState : public State
{
public:
	AIDeadState(StateMachine *machine);

protected:
	virtual ~AIDeadState();
};

// ??0AIDeadState@@QAE@PAVStateMachine@@@Z
AIDeadState::AIDeadState(StateMachine *machine) :
	State(machine, "AIDeadState")
{
}
