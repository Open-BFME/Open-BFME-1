// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the crate pick-up state constructor at retail 0x0015D000, 53 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.
//
// Retail reaches the base through its ILT thunk 0x00032182, whose body is
// 0x0014F280 -- matched as
// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@VAsciiString@@@Z in
// game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateCtor.cpp -- so the
// base initialiser is spelled as that class's constructor, and the name
// argument is a real AsciiString rather than a TU-local stand-in.
//
// The vftable store is retail's own (0x01096348, the AIMoveAndTightenState
// family table), written by hand because a compiler-installed vftable store
// lands ahead of the field store here, not after it. Nothing in the tree
// defines that datum yet.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

extern "C" void *bfmeVftableAU[];			// retail 0x01096348

class BfmeStateAU : public AIInternalMoveToState
{
public:
	BfmeStateAU(void *owner);

	void *m_bfmeVfptrAU;
	char m_bfmePadAU[76];
	int m_bfmeFieldAU;
};

BfmeStateAU::BfmeStateAU(void *owner)
	: AIInternalMoveToState((StateMachine *)owner, AsciiString("AIAttackPickUpCrateState"))
{
	m_bfmeFieldAU = 0;

	m_bfmeVfptrAU = bfmeVftableAU;
}
