// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
//
// Retail 0x0023D130, complete 92-byte boundary.  No named caller, vtable, or
// source emitter proves a semantic owner for this body.  The address-derived
// owner below records only the ABI and the fields witnessed in the retail code.
//
// The nearby 0x0023D1B0 body provides an independently landed MSVC 7.1 shape
// for this resolver/override/string/lookup sequence.  This copy keeps its own
// address-derived entry types: the target returns the lookup result's +0x08
// subobject, while 0x0023D1B0 returns its +0x78 subobject.
//
// ABI evidence from the target body: thiscall receiver in ECX, one pointer
// argument at [esp+4], and ret 4; resolve takes one int and returns a pointer;
// the override helper takes no explicit arguments and returns a pointer; the
// lookup thunk takes one four-byte AsciiString by value and returns a pointer.

#include "StringInline.h"

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	void *m_vtable;
	BfmeOverridable *m_nextOverride;
	unsigned char m_gap08[0x18];
	AsciiString m_name;
};

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int allowLookup);

private:
	unsigned char m_gap00[4];
	BfmeOverridable *m_template;
};

extern void j_000289d9(void);

struct Rva0023D130EntryPrefix
{
	unsigned char m_unreconstructed_000[0x08];
};

struct Rva0023D130EntryTail
{
	void *m_payload;
};

struct Rva0023D130Entry : Rva0023D130EntryPrefix,
	Rva0023D130EntryTail
{
};

class Rva0023D130Lookup
{
public:
	Rva0023D130Entry *lookup(AsciiString key);
};

class Rva0023D130Owner
{
public:
	Rva0023D130EntryTail *call_0023D130(RvaC4390Second *candidate);
};

Rva0023D130EntryTail *Rva0023D130Owner::call_0023D130(
	RvaC4390Second *candidate)
{
	if (candidate == 0)
		return 0;

	void *resolved = candidate->resolve(0);
	void *base = resolved;
	if (base == 0)
		base = candidate;

	BfmeOverridable *overrideObject =
		*(BfmeOverridable **)((char *)base + 4);
	if (overrideObject && overrideObject->m_nextOverride)
		overrideObject = overrideObject->m_nextOverride->friend_getFinalOverride();

	typedef Rva0023D130Entry *(Rva0023D130Lookup::*LookupThunk)(AsciiString);
	union
	{
		void (*raw)(void);
		LookupThunk member;
	} thunk;
	thunk.raw = j_000289d9;
	Rva0023D130Entry *answer =
		(reinterpret_cast<Rva0023D130Lookup *>(reinterpret_cast<char *>(this) - 0xe4)->*thunk.member)(
			AsciiString(overrideObject->m_name));
	if (answer == 0)
		return 0;
	return answer;
}
