// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: AIMoveAndEvacuateState constructor, retail 0x0017FD10, 57 bytes.

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
	virtual ~AIInternalMoveToState();

private:
	unsigned char m_body[0x2C];
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	AIMoveAndEvacuateState(StateMachine *machine);

private:
	Coord3D m_origin;
};

// ??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z
AIMoveAndEvacuateState::AIMoveAndEvacuateState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIMoveAndEvacuateState")
{
	Coord3D *const position = &m_origin;
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
}
