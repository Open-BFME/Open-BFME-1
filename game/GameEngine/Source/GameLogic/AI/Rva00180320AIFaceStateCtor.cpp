// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

protected:
	int *volatile m_vftable;
	unsigned char m_head[0x20];
};

extern int g_AIFaceStateVTable;

// Retail's AIStateMachine builds its face states (0x24, 0x25 and 0x3B) as
// 0x30-byte objects on vtable 0x0109AD20, whose name slot returns "AIFaceState"
// and whose update slot is AIFaceState::update. The first part of the body is
// AIIdleState's constructor with LOOK_FOR_TARGETS: the "AIIdleState" state name
// and the same stores to +0x24..+0x27. The second parameter replaces Zero
// Hour's Bool: retail stores a full dword, and AIStateMachine stores 1, 0 and 2
// there. Its type is unknown, so the class name stays address-derived.
class Rva00180320AIFaceState : public State
{
public:
	Rva00180320AIFaceState(StateMachine *machine, int obj);

private:
	unsigned short m_initialSleepOffset;
	bool m_shouldLookForTargets;
	bool m_inited;
	int m_obj;
	bool m_canTurnInPlace;
};

Rva00180320AIFaceState::Rva00180320AIFaceState(StateMachine *machine, int obj) :
	State(machine, "AIIdleState")
{
	m_inited = false;
	m_canTurnInPlace = false;
	m_shouldLookForTargets = true;
	m_initialSleepOffset = 0xFFFF;
	m_vftable = &g_AIFaceStateVTable;
	m_obj = obj;
}
