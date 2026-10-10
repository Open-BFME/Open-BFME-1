// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AITNGuardOuter constructor at retail 0x0018AD00, 61 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.
//
// The by-value name argument is a real WWLib AsciiString: retail pushes the
// literal and calls StringBase<char>'s const-char* constructor (0x00888BC0,
// ??0?$StringBase@D@@AAE@PBD@Z), then destroys the temporary through the
// header-inline destructor, which lands on
// StringBase<char>::releaseBuffer (0x00887940,
// ?releaseBuffer@?$StringBase@D@@AAEXXZ).  Both are COMDAT-defined in
// game/Libraries/Source/string/StringBase.cpp; the old local
// StringBaseNarrowAY/AsciiStringAY spellings pointed at nothing.
//
// Still open (both need work outside this file):
//   ?bfmeBaseInitAY@BfmeStateAY@@QAEXPAXVAsciiStringAY@@@Z -- retail
//     0x000A19E0 is the ledger's ??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z
//     (game/GameEngine/Source/Common/StateConstructor.cpp).  No header declares
//     State/StateMachine, so this file cannot spell it.
//   _bfmeVftableAY / g_Va0109B558 -- retail RVA 0x00C9B650 and 0x00C9B558,
//     anonymous .rdata (a vftable and a transition-handler table) that
//     exports.csv does not name.  Needs a datum.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The TU-local view keeps the AY spelling the symbols.csv pin uses; its two
// constructors reach the private StringBase<char> constructors through
// AsciiString, whose header-inline bodies collapse to the real calls.
class AsciiStringAY : public AsciiString
{
public:
	AsciiStringAY(const char *text) throw() : AsciiString(text)
	{
	}

	AsciiStringAY(const AsciiStringAY &other) throw() : AsciiString(other)
	{
	}

	~AsciiStringAY(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAY[];
extern int g_Va0109B558;

class BfmeStateAY
{
public:
	BfmeStateAY(void *owner);

	void bfmeBaseInitAY(void *owner, AsciiStringAY name) throw();

	void *volatile m_bfmeVfptrAY;
	char m_bfmePadAY[0x20];
	void *volatile m_bfmeTableAY;
	volatile int m_bfmeFirstAY;
	volatile int m_bfmeSecondAY;
};

BfmeStateAY::BfmeStateAY(void *owner)
{
	bfmeBaseInitAY(owner, AsciiStringAY("AITNGuardOuter"));

	m_bfmeVfptrAY = bfmeVftableAY;

	m_bfmeFirstAY = 0;

	m_bfmeTableAY = (void *)&g_Va0109B558;

	m_bfmeSecondAY = 0;
}
