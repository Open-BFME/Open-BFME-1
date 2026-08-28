// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// State subclass constructor taking an extra argument, which it stores at 0x24.
//
// The AsciiString is the shim's rather than a hand-rolled stand-in -- the name is
// passed to the base by value and only the StringBase-backed shim emits
// `mov [esp+8],esp` before `mov ecx,esp` the way retail does.
#include "Common/AsciiString.h"

class StateMachine;

class NotifyWeaponFiredInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackFireWeaponState : public State
{
public:
	AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface * notify);

private:
	NotifyWeaponFiredInterface * m_24;
	bool m_28;
};

// ??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z
AIAttackFireWeaponState::AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface * notify) :
	State(machine, "AIAttackFireWeaponState"),
	m_24(notify),
	m_28(false)
{
}
