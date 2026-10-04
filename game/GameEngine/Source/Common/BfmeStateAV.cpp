// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the exit state constructor at retail 0x00171680, 53 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.
//
// Retail reaches the base through its ILT thunk 0x000035B2, whose body is
// 0x000A19E0 -- matched as
// ??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z in
// game/GameEngine/Source/Common/StateConstructor.cpp -- so the base
// initialiser is spelled as that class's constructor and the name argument is
// a real AsciiString, not a TU-local stand-in.
//
// The vftable store is retail's own (0x01098188), not one this TU emits: the
// derived class is not polymorphic here, and the extern below has no definition
// anywhere in the tree yet.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class StateMachine;

class State
{
public:
	State( StateMachine *machine, AsciiString name );
};

extern "C" void *bfmeVftableAV[];			// retail 0x01098188

class BfmeStateAV : public State
{
public:
	BfmeStateAV(void *owner);

	void *m_bfmeVfptrAV;
	char m_bfmePadAV[32];
	int m_bfmeFieldAV;
};

BfmeStateAV::BfmeStateAV(void *owner)
	: State((StateMachine *)owner, AsciiString("AIExitState"))
{
	m_bfmeFieldAV = 0;

	m_bfmeVfptrAV = bfmeVftableAV;
}
