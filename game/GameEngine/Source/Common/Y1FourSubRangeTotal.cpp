// 0x003CD2D0, 143 bytes, ret 0: sum the element counts of four optional
// sub-ranges hanging off the object at +0x10, +0x14, +0x18 and +0x1C.
//
//     int n = 0;
//     if ( m_a ) n += m_a->size();      // size() == m_end - m_begin
//     if ( m_b ) n += m_b->size();
//     if ( m_c ) n += m_c->size();
//     if ( m_d ) n += m_d->size();
//     return n;
//
// WHAT THE BYTES SHOW.  Each of the four blocks reads +0x0C and +0x08 out of the
// sub-object, subtracts, and then divides by 60 the way MSVC 7.1 divides a
// SIGNED int by a constant: `mov eax,0x88888889 / imul / add edx,x / sar edx,5`
// followed by `shr ...,0x1F / add` to fold the sign.  60 is 0x3C, the same
// element stride the 0x3C-walks elsewhere in this range use, so the sub-object
// is a half-open pair over those elements and this is its element COUNT.
//
// The first block MOVES its result into esi where the other three ADD to it --
// the fold of `0 + x` against the `xor esi,esi` that precedes the first test, so
// all four statements are the same `n += ...` in the source.
//
// THE `size()` HELPER IS LOAD-BEARING.  Spelling the four sums as
// `m_a->m_end - m_a->m_begin` inline compiles the same arithmetic but places
// `push edi` one test earlier and allocates the fourth block differently, four
// bytes longer than retail.  Routing them through an inline member that returns
// the difference reproduces retail exactly.  That is the shape of a container
// with a size() accessor, which is also what the half-open pair looks like.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the owner or the four sub-ranges;
// every name here is address-derived or describes only what the byte does.

class Y1SubRangeElement
{
public:
	char m_pad[ 0x3C ];
};

class Y1SubRange
{
public:
	char m_lead[ 8 ];
	Y1SubRangeElement *m_begin;
	Y1SubRangeElement *m_end;

	int size() const { return m_end - m_begin; }
};

class Rva003CD2D0
{
public:
	char m_lead[ 0x10 ];
	Y1SubRange *m_a;
	Y1SubRange *m_b;
	Y1SubRange *m_c;
	Y1SubRange *m_d;

	int total() const;
};

int Rva003CD2D0::total() const
{
	int n = 0;

	if ( m_a ) n += m_a->size();
	if ( m_b ) n += m_b->size();
	if ( m_c ) n += m_c->size();
	if ( m_d ) n += m_d->size();

	return n;
}
