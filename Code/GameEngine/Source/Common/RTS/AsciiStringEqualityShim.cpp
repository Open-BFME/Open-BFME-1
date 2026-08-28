// Retail 0x005A8140, 94 bytes: the target of the AsciiString equality
// incremental-link thunk, already pinned in symbols.csv as
// ?equal@AsciiStringEqualityShim@@SA_NABVAsciiString@@0@Z.
//
// The bytes are not an equality test and the operands are not four-byte
// strings. Both references are indexed at +0x00, +0x04, +0x08 and +0x0C and
// each slot is handed to StringBase<char>::compareNoCase, so what the thunk
// actually reaches is a lexicographic less-than over a sixteen-byte record of
// four strings. The pinned spelling is kept verbatim so the thunk still
// resolves; only the layout is written to what the body reads.
//
// The comparison order is not the declaration order: the body tests +0x00,
// then +0x08, then +0x04, and only falls through to +0x0C. Each of the first
// three is a three-way test -- jl returns true, jg returns false -- and the
// two exits are shared, which is why the false exit is reached both by a jg
// and by a jle from the third test.
//
// Returns are byte-wide throughout (mov al,1 / xor al,al / setl dl), so the
// result type is bool rather than int.

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const;	// retail 0x00090570

private:
	T *m_bfmeData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	StringBase<char> m_bfmeSlot0;		// +0x00
	StringBase<char> m_bfmeSlot4;		// +0x04
	StringBase<char> m_bfmeSlot8;		// +0x08
	StringBase<char> m_bfmeSlotC;		// +0x0C
};

class AsciiStringEqualityShim
{
public:
	static bool equal(const AsciiString &a, const AsciiString &b);
};

// ?equal@AsciiStringEqualityShim@@SA_NABVAsciiString@@0@Z
bool AsciiStringEqualityShim::equal(const AsciiString &a, const AsciiString &b)
{
	int order = a.m_bfmeSlot0.compareNoCase(b.m_bfmeSlot0);

	if (order < 0)
		return true;

	if (order > 0)
		return false;

	order = a.m_bfmeSlot8.compareNoCase(b.m_bfmeSlot8);

	if (order < 0)
		return true;

	if (order > 0)
		return false;

	order = a.m_bfmeSlot4.compareNoCase(b.m_bfmeSlot4);

	if (order < 0)
		return true;

	if (order > 0)
		return false;

	return a.m_bfmeSlotC.compareNoCase(b.m_bfmeSlotC) < 0;
}
