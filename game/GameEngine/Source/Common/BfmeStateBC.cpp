// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the AIBackAwayState constructor at retail 0x001804B0, 57 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes. Retail calls the AIInternalMoveToState base
// constructor through its ILT thunk 0x00032182 (body 0x0014F280, matched as
// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@VAsciiString@@@Z in
// game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateCtor.cpp), then
// writes its own fields and installs its own vftable last. The vftable is not
// an extern datum: the derived class has a virtual, so this TU emits it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );

	virtual void stateBaseAnchor() {}
};

class BfmeStateBC : public AIInternalMoveToState
{
public:
	BfmeStateBC(void *owner, const char *name);

	char m_bfmePadBC[0x4c];
	volatile int m_bfmeCountBC;
	volatile char m_bfmeFlagBC;
};

BfmeStateBC::BfmeStateBC(void *owner, const char *name)
	: AIInternalMoveToState((StateMachine *)owner, AsciiString(name))
{
	m_bfmeFlagBC = 0;

	m_bfmeCountBC = 0;
}
