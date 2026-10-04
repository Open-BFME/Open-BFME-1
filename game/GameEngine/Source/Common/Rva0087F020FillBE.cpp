// ?bfmeFillBE@@YAPAUBfmeElemBE@@PAU1@IABU1@ABUBfmeFalseBE@@@Z
// cl: /O2 /Ob1 /G6 /GX-

// The 0x24-byte element's member group at +0x10: the three dwords the matched
// siblings Rva0087EAA0Copy.cpp and Rva0087E9B0Fill.cpp spell BfmeCoordXX m_10,
// then the StringBase<char> tail whose copy ctor is the one out-of-line call
// this body makes (0x00887B60), then the flag byte at +0x20.
//
// Retail keeps a SECOND induction variable for this group: esi is seeded at
// first+0x18 and reaches the group's earlier fields with negative
// displacements (-0x14 .. -8). MSVC 7.1 only splits the implicit copy ctor
// into two cursors when the group is its own aggregate member, so the
// nesting here is what the byte-verified body witnesses, not a free choice.

inline void *operator new(unsigned int, void *p)
{
	return p;
}

struct BfmeFalseBE
{
};

// The tail member is retail's StringBase<char> (the ledger's public narrow
// StringBase copy at 0x00887B60), declared here only so the implicit copy ctor
// below spells the call to that real body directly instead of a local stand-in
// aliased onto it: the copy ctor is declared and never defined in this TU, so
// the reference resolves to the out-of-line body the real header owns. Same
// idiom as game/Libraries/Source/WWVegas/WWLib/RvaStringAccessor.cpp.
template <class T>
class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase();

private:
	T *m_data;
};

struct BfmeGroup10BE
{
	int m_10;
	int m_14;
	int m_18;
	StringBase<char> m_1C;
	char m_20;
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeGroup10BE m_10;
};

__declspec(noinline) BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
	const BfmeElemBE &value, const BfmeFalseBE &)
{
	BfmeElemBE *cur = first;
	while (count > 0)
	{
		if (cur != 0)
			new (cur) BfmeElemBE(value);
		++cur;
		--count;
	}
	return cur;
}
