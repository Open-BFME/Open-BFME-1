// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Three members zeroed, then the vptr -- retail sinks the store past them so the compiler's own sink agrees.
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

class DozerPrimaryIdleState : public State
{
public:
	DozerPrimaryIdleState(StateMachine *machine);

private:
	int m_24;
	int m_28;
	bool m_2c;
};

// ??0DozerPrimaryIdleState@@QAE@PAVStateMachine@@@Z
DozerPrimaryIdleState::DozerPrimaryIdleState(StateMachine *machine) :
	State(machine, "DozerPrimaryIdleState")
{
	m_24 = 0;
	m_28 = 0;
	m_2c = false;
}
