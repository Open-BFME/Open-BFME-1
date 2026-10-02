// A bounded scan over the 0x28-byte records used by the three U4 proxy
// forwarders.  The proxy at 0x00606E20 proves the receiver and two-argument
// shape; this body's unnormalised EAX return proves that the result is a
// pointer rather than the historical Bool guess.

struct U4Elem
{
	char m_pad[0x28];
	void *m_named[0x1C8 / 4];
};

// The mask the scan applies to each record is not a filter object: it is Zero
// Hour's BitFlags<304>, and the per-element call is BitFlags<304>::testForAll,
// whose body is game/GameEngine/Source/Common/BitFlags304TestForAll.cpp
// (retail 0x00606BF0).  Retail loads the mask into ECX and pushes the element
// pointer as its `const BitFlags &`.
//
// ?testForAll@?$BitFlags@$0BDA@@@QBE_NABV1@@Z		retail 0x00606BF0
template <size_t NUMBITS>
class BitFlags
{
public:
	bool testForAll( const BitFlags &that ) const;
};

// The scan's second argument, still named for its address only: its body is
// never recovered here, so it stays incomplete and the call site casts it to
// the BitFlags<304> it actually is.
class U4Filter;

class U4Scan
{
public:
	const char *firstNamed(void *out, const U4Filter *filter) const;

	int m_f00;
	int m_f04;
	U4Elem *m_begin;
	U4Elem *m_end;
};

const char *U4Scan::firstNamed(void *out, const U4Filter *filter) const
{
	U4Elem *p = m_begin;
	U4Elem *end = m_end;
	unsigned int index = (unsigned int)out;

	for (; p != end; ++p)
	{
		if (((const BitFlags<304> *)filter)->testForAll(*(const BitFlags<304> *)p)
			&& p->m_named[index] != 0)
			return static_cast<const char *>(p->m_named[index]) + 4;
	}

	return 0;
}
