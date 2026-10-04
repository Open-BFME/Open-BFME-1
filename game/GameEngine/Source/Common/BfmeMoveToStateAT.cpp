// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIMoveToState constructor at retail 0x00185700, 50 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the flag.

// The state name is built by the real AsciiString: retail's copy sites build
// the temporary with a direct `call StringBase<char>::StringBase(char const*)`,
// and ascii_string.h's inline AsciiString(const char *) is exactly that call --
// no intermediate body, so the bytes are unchanged.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class StateMachine;

// The base initialiser this constructor calls is reached through ILT 0x00032182,
// whose jump lands on rva 0x0014F280: the 149-byte matched
// AIInternalMoveToState(StateMachine *, AsciiString) ctor
// (game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateCtor.cpp), whose
// signature is the by-value state name this body pushes.  Only that ctor is
// known here, so the base declares nothing else and the derived view below keeps
// the two stores at the offsets retail writes (+0 vftable, +0x50 flag).
class AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);
};

extern "C" void *bfmeVftableAT[];			// retail 0x0109B370

class BfmeMoveToStateAT : public AIInternalMoveToState
{
public:
	BfmeMoveToStateAT(void *owner);

	void *m_bfmeVfptrAT;
	char m_bfmePadAT[0x4c];
	char m_bfmeReadyBfmeAT;
};

BfmeMoveToStateAT::BfmeMoveToStateAT(void *owner)
	: AIInternalMoveToState(reinterpret_cast<StateMachine *>(owner),
		AsciiString("AIMoveToState"))
{
	m_bfmeReadyBfmeAT = 1;

	m_bfmeVfptrAT = bfmeVftableAT;
}