// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the second crate pick-up state constructor at retail 0x0018AE00,
// 53 bytes. The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.
//
// Retail reaches the base through its ILT thunk 0x00032182, whose body is
// 0x0014F280 -- matched as
// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@VAsciiString@@@Z in
// game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateCtor.cpp -- so the
// base initialiser is spelled as that class's constructor and the name argument
// is a real AsciiString, not a TU-local stand-in.
//
// The vftable store is retail's own (0x0109B748), not one this TU emits: the
// derived class is not polymorphic here, and the extern below has no definition
// anywhere in the tree yet.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

extern "C" void *bfmeVftableAW[];			// retail 0x0109B748

class BfmeStateAW : public AIInternalMoveToState
{
public:
	BfmeStateAW(void *owner);

	void *m_bfmeVfptrAW;
	char m_bfmePadAW[76];
	int m_bfmeFieldAW;
};

BfmeStateAW::BfmeStateAW(void *owner)
	: AIInternalMoveToState((StateMachine *)owner, AsciiString("AIAttackPickUpCrateState"))
{
	m_bfmeFieldAW = 0;

	m_bfmeVfptrAW = bfmeVftableAW;
}
