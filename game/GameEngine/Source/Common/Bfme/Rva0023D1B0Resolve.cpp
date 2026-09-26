// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
//
// Retail 0x0023D1B0, complete 92-byte boundary.  No named caller, vtable, or
// source owner is proven for this entry; the neutral address-derived owner
// below records only the raw ABI and the fields used by the code.
//
// The first call is the already pinned RvaC4390Second::resolve(int) ILT.  When
// it returns a non-null object, retail reads that object's +4; otherwise it
// reads +4 from the supplied object.  The resulting override is optionally
// advanced through the already owned BfmeOverridable ILT at 0x000022BB.
// Its +0x20 member is copied into a by-value AsciiString argument for the
// anonymous helper reached through the existing j_000289d9 thunk.  The helper
// is a __thiscall taking one four-byte string object and returns a pointer;
// its ret 4 and the caller's ECX receiver are proven by the retail body.

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

struct Rva0023D1B0EntryPrefix
{
	unsigned char m_unreconstructed_000[0x78];
};

struct Rva0023D1B0EntryTail
{
	void *m_payload;
};

struct Rva0023D1B0Entry : Rva0023D1B0EntryPrefix,
	Rva0023D1B0EntryTail
{
};

class Rva00238740Call
{
public:
	Rva0023D1B0Entry *lookup(AsciiString key);
};

class Rva0023D1B0Owner
{
public:
	Rva0023D1B0EntryTail *call_0023D1B0(RvaC4390Second *candidate);
};

Rva0023D1B0EntryTail *Rva0023D1B0Owner::call_0023D1B0(
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

	typedef Rva0023D1B0Entry *(Rva00238740Call::*LookupThunk)(AsciiString);
	union
	{
		void (*raw)(void);
		LookupThunk member;
	} thunk;
	thunk.raw = j_000289d9;
	Rva0023D1B0Entry *answer =
		(reinterpret_cast<Rva00238740Call *>(reinterpret_cast<char *>(this) - 0xe4)->*thunk.member)(
			AsciiString(overrideObject->m_name));
	if (answer == 0)
		return 0;
	return answer;
}
