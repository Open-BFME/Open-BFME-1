// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Derives from TurretState, which the base call at 0x0018D890 names -- five
// retail states go there and the reference declares exactly that set as its
// children. Its constructor is protected, so it mangles IAE; making it public
// would rename the symbol QAE and the call would stop resolving.
//
// TurretState adds nothing of its own, so this class's members start at 0x24.
#include "Common/AsciiString.h"

class StateMachine;

class TurretStateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretState : public State
{
protected:
	TurretState(TurretStateMachine *machine, AsciiString name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIAimTurretState : public TurretState
{
public:
	TurretAIAimTurretState(TurretStateMachine *machine);
};

// ??0TurretState@@IAE@PAVTurretStateMachine@@VAsciiString@@@Z
TurretState::TurretState(TurretStateMachine *machine, AsciiString name) :
	State(reinterpret_cast<StateMachine *>(machine), name)
{
}

// ??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z
TurretAIAimTurretState::TurretAIAimTurretState(TurretStateMachine *machine) :
	TurretState(machine, "TurretAIAimTurretState")
{
}
