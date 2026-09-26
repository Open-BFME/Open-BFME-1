// 0x003D3250, 77 bytes, ret 4: elementwise equality of two half-open dword
// ranges.
//
//     size  = (m_end - m_begin) >> 2          <- sar, so the difference is a
//     other = (o->m_end - o->m_begin) >> 2       SIGNED pointer subtraction
//     if ( size != other ) return false;
//     for ( i = 0; i < size; ++i )
//         if ( m_begin[i] != o->m_begin[i] ) return false;
//     return true;
//
// WHAT THE BYTES SHOW.  Two dwords are read out of `this` and two out of the
// argument, both differences are `sar ...,2` -- element size 4 and a signed
// subtraction, i.e. C++ pointer arithmetic, not an unsigned byte count.  The
// three exits all set AL alone (`mov al,1` / `xor al,al`), which is MSVC 7.1's
// `bool`.  The comparison loop counts in edx and walks ecx by 4, comparing
// `[ecx]` against `[esi+ecx]` where esi was pre-biased by `sub esi,ecx` -- the
// compiler's strength reduction of a shared index, not two indices in the
// source.
//
// This is the `operator==` shape of an STL vector-of-int comparison: size first,
// then elements, bailing on the first difference.  It is written as an ordinary
// member here rather than instantiated from the vendored container because a
// container instantiation would emit a family of other members this file cannot
// claim.
//
// IDENTITY IS NOT RECOVERED.  No caller names it and nothing says what the
// dwords mean; the name is address-derived.

class Rva003D3250
{
public:
	int *m_begin;
	int *m_end;

	bool equals( const Rva003D3250 *other ) const;
};

bool Rva003D3250::equals( const Rva003D3250 *other ) const
{
	int size = m_end - m_begin;
	if ( size != other->m_end - other->m_begin )
		return false;

	for ( int i = 0; i < size; ++i )
		if ( m_begin[ i ] != other->m_begin[ i ] )
			return false;

	return true;
}
