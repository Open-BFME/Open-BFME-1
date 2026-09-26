// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// State subclass constructor taking an extra argument, which it stores at 0x24.
//
// The AsciiString is the shim's rather than a hand-rolled stand-in -- the name is
// passed to the base by value and only the StringBase-backed shim emits
// `mov [esp+8],esp` before `mov ecx,esp` the way retail does.
#include "Common/AsciiString.h"

class StateMachine;

enum DozerTask
{
	DOZER_TASK_INVALID = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

class DozerActionPickActionPosState : public State
{
public:
	DozerActionPickActionPosState(StateMachine *machine, DozerTask task);

private:
	DozerTask m_24;
	int m_28;
};

// ??0DozerActionPickActionPosState@@QAE@PAVStateMachine@@W4DozerTask@@@Z
DozerActionPickActionPosState::DozerActionPickActionPosState(StateMachine *machine, DozerTask task) :
	State(machine, "DozerActionPickActionPosState"),
	m_24(task),
	m_28(0)
{
}
