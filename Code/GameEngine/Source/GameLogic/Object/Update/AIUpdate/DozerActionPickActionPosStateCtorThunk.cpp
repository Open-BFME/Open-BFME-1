// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
