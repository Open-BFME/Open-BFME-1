// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: 0x0006A980, a constructor that copies two words, builds a
// sub-object at this+8 from the argument's own this+8 through the out-of-line
// helper at 0x00069F00, mirrors this+0x0C into this+0x18, and then clears four
// words.
//
// Those four clears come out DESCENDING -- 0x28 0x24 0x20 0x1C -- and MSVC 7.1
// does not reorder straight-line constant stores, so that is not scheduling: it
// is one CHAINED assignment, `m_1C = m_20 = m_24 = m_28 = 0`, which evaluates
// right to left. Written as four separate statements the same source compiles
// ascending.
//
// The helper at 0x00069F00 is called with ecx holding THIS+8 rather than this
// (`lea ecx,[esi+8]`), so it is a member of the sub-object at +8 and not of the
// enclosing type -- declaring it on the outer class costs a byte and compiles
// `mov ecx,esi` instead. It is unconverted; it is pinned by name here so the
// REL32 resolves and its identity is not recovered.
//
// Identity is address-derived.

typedef int Int;

struct Rva0006A980Cursor
{
	void build(const Rva0006A980Cursor *source);		///< retail 0x00069F00

	Int m_first;										///< cursor+0x00
	Int m_second;										///< cursor+0x04
};

class Rva0006A980Range
{
public:
	Rva0006A980Range(const Rva0006A980Range &other);

private:
	Int m_value00;										///< retail this+0x00
	Int m_value04;										///< retail this+0x04
	Rva0006A980Cursor m_cursor;							///< retail this+0x08
	Int m_value10;										///< retail this+0x10
	Int m_value14;										///< retail this+0x14
	Int m_value18;										///< retail this+0x18
	Int m_value1C;										///< retail this+0x1C
	Int m_value20;										///< retail this+0x20
	Int m_value24;										///< retail this+0x24
	Int m_value28;										///< retail this+0x28
};

// ??0Rva0006A980Range@@QAE@ABV0@@Z
Rva0006A980Range::Rva0006A980Range(const Rva0006A980Range &other)
{
	m_value00 = other.m_value00;
	m_value04 = other.m_value04;

	m_cursor.build(&other.m_cursor);

	m_value18 = m_cursor.m_second;

	m_value1C = m_value20 = m_value24 = m_value28 = 0;
}
