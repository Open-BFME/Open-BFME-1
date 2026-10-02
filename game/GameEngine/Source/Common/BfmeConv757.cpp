// cl: /EHs-c-

// Open-BFME5 conversions.

// The record's head at +4 is a narrow string. Retail builds it in place: it
// copy-constructs the head from the caller's pointer, with the argument loaded
// early and pushed unconditionally and no placement-new null test between
// `push edx` and `lea ecx,[esi+4]`.
//
// Retail's copy sites of an AsciiString emit `call StringBase<char>::StringBase`
// directly rather than a call to AsciiString's own constructor (see
// ascii_string.h), so the call target here is the real copy-constructor symbol
// `??0?$StringBase@D@@AAE@ABV0@@Z` at 0x00887B60 (121 B), defined and matched
// in game/Libraries/Source/string/StringBase.cpp. MSVC 7.1 inlines a class
// constructor into its placement-new expression, which is why the call lands on
// the base constructor's own symbol instead of a local one.
//
// Two details make the shape byte-exact rather than merely linkable. The
// placement pointer goes through a temporary the compiler is told is non-null,
// because MSVC 7.1 otherwise emits a `test ecx,ecx` / `je` pair retail does not
// have, and assuming on the member address itself leaves the test in place.
// And the type being constructed is the record rather than AsciiString: naming
// AsciiString directly is inlined into the placement-new expression, which
// schedules `lea ecx,[esi+4]` before `push edx`, whereas a constructor reached
// through the record emits the argument push first.
//
// The constructor below exists only to express that in-place construction; the
// dword at +0 is written by bfmeGoDQB itself and the constructor leaves it be.

#include <new>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct BfmeOutDQB
{
	int m_bfmeA;
	AsciiString m_bfmeSub;

	BfmeOutDQB(const AsciiString &src) : m_bfmeSub(src) {}
};

BfmeOutDQB *bfmeGoDQB(BfmeOutDQB *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	void *place = out;
	__assume(place != 0);
	new (place) BfmeOutDQB(*static_cast<const AsciiString *>(arg));
	return out;
}