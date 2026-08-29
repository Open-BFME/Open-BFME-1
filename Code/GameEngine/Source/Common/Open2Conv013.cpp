// Two bodies from the 0x005xxxxx run.  Identity is not recovered; names are
// address-derived.

// ---------------------------------------------------------------------------
// 0x005719B0 -- insertion sort over twelve-byte records keyed on their first
// dword.
//
// The element is three dwords and the sort walks BACKWARDS in twelve-byte
// steps, sliding each record up until the key in front of it is no longer
// larger.  The comparison is `jge`/`jl`, so the key is signed.
//
// There is NO bounds check in the inner walk and the outer one starts at
// `first` itself, reading `[first-12]` on the very first turn: this is
// STLport's __unguarded_linear_insert, which relies on a sentinel already
// sitting in front of the range.  Adding a `hole != first` guard costs eight
// bytes and changes the loop shape.

class Open25719B0Record
{
public:
	int m_key;
	int m_second;
	int m_third;
};

// @?Rva005719B0@@YAXPAVOpen25719B0Record@@0@Z 0x005719B0
void Rva005719B0( Open25719B0Record *first, Open25719B0Record *last )
{
	for( Open25719B0Record *cursor = first; cursor != last; ++cursor )
	{
		Open25719B0Record value = *cursor;
		Open25719B0Record *hole = cursor;
		Open25719B0Record *previous = hole - 1;

		while( value.m_key < previous->m_key )
		{
			*hole = *previous;
			hole = previous;
			--previous;
		}

		*hole = value;
	}
}
