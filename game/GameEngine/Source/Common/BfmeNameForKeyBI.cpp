// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the name-for-key lookup at retail 0x007696B0, 62 bytes.  A hit
// writes its name straight into our caller's return slot; a miss copies the
// shared default.
//
// Retail's miss path pushes 0x01336E50 and then calls StringBase<char>'s copy
// constructor (0x00887B60).  0x01336E50 is WWLib's exported
// ?TheEmptyString@AsciiString@@2V1@B (ascii_string.h:18), whose single
// definition is the const out-of-line copy in
// game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_initTimes.cpp,
// and 0x00887B60 is ??0?$StringBase@D@@AAE@ABV0@@Z from
// game/Libraries/Source/string/StringBase.cpp.  The old TU-local
// StringBaseNarrowBI / g_bfmeDefaultBI spellings were invented here and nothing
// defined them; the local view of the return type stays AsciiStringBI.
//
// Still open (both need work outside this file):
//   ?bfmeLookupBI@@YGPAVBfmeThingBI@@H@Z -- retail 0x00765B70, reached through
//     the already-matched incremental-link thunk ?j_00005024@@YAXXZ
//     (0x00005024, game/gen_small/thunks_001.cpp).  No ledger row owns
//     0x00765B70, so it needs a body.
//   ?bfmeNameBI@BfmeThingBI@@QAE?AVAsciiStringBI@@XZ -- retail 0x007622C0,
//     thunk ?j_00012a7b@@YAXXZ (0x00012A7B).  Same: needs a body.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// StringBase<char>'s constructors and destructor are private with AsciiString
// as a friend, so the local view has to reach them through AsciiString; both
// of the ctors it uses are header-inline and collapse to the StringBase call.
class AsciiStringBI : public AsciiString
{
public:
	AsciiStringBI(const AsciiStringBI &other) throw() : AsciiString(other)
	{
	}

	~AsciiStringBI(void) throw()
	{
	}
};

class BfmeThingBI
{
public:
	AsciiStringBI bfmeNameBI(void) throw();
};

BfmeThingBI *__stdcall bfmeLookupBI(int key) throw();

// ?bfmeNameForBI@@YG?AVAsciiStringBI@@H@Z
AsciiStringBI __stdcall bfmeNameForBI(int key)
{
	BfmeThingBI *thing = bfmeLookupBI(key);

	if (thing != 0)
		return thing->bfmeNameBI();

	return (const AsciiStringBI &)AsciiString::TheEmptyString;
}
