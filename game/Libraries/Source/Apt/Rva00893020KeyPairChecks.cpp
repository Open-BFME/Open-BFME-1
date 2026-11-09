// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
//
// The table scan at retail 0x00892FD0 (71 bytes, ret 8) and the two
// unreferenced 10-byte __thiscall bodies, each alone in an int3-padded gap,
// that call it on the SAME receiver (ecx is passed through untouched) with a
// fixed key pair and return its bool:
//
//     push 2 / push 4 (or 3) / call 0x00892FD0 / ret
//
// The scan reads a count at +0 and 8-byte entries at +8 and answers whether
// every entry's +4 key is one of the two arguments. The pin's class is the
// generated name the 0x00896710 caller reaches it through.
//
// SCAN SHAPE (BFME 1 retail facts). Retail loads the entry base once before
// the guard, copies it (`mov edx,eax / add edx,esi`) to form the end, keeps
// count*8 in esi across the loop and RE-READS the base at the back-edge. That
// is what VC7.1 emits when begin()/end() are raw pointers taken from a
// two-pointer range temporary rebuilt on every call: the temporary keeps the
// end from being hoisted whole, while the loop variable stays a plain pointer
// in eax. A three-word iterator object as the loop variable gives the same
// 71 bytes with eax/edx exchanged; plain `m_entries + m_count` hoists the end
// (54 bytes).
//
// Donor lead (not BFME 1 proof): Open-BFME-2 67a8a17e42
// Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp, Rva006CEB10Playback::
// readyFor, spells begin()/end() through `PlaybackRange(items, items + size)`.
// The range temporary is carried from there; the donor's three-word checked
// iterator and its entry member names are NOT (they do not reproduce these
// bytes and nothing in BFME 1 witnesses them).
//
// IDENTITY IS NOT RECOVERED. Type and member names are derived from addresses
// and offsets.

struct Rva00892FD0Entry
{
	int m_00;
	int m_04;
};

struct Rva00892FD0Range
{
	Rva00892FD0Entry *m_first;
	Rva00892FD0Entry *m_last;
	Rva00892FD0Range( Rva00892FD0Entry *first, Rva00892FD0Entry *last ) : m_first( first ), m_last( last ) {}
	Rva00892FD0Entry *begin() const { return m_first; }
	Rva00892FD0Entry *end() const { return m_last; }
};

class Gen_uw_00893e70
{
public:
	bool Rva00892FD0( int first, int second );
	bool rva00893020();
	bool rva008951F0();

private:
	Rva00892FD0Range range() { return Rva00892FD0Range( m_08, m_08 + m_00 ); }
	Rva00892FD0Entry *begin() { return range().begin(); }
	Rva00892FD0Entry *end() { return range().end(); }

	int m_00;                 // +0x00 entry count
	int m_04;
	Rva00892FD0Entry *m_08;   // +0x08 entry array
};

bool Gen_uw_00893e70::Rva00892FD0( int first, int second )
{
	for ( Rva00892FD0Entry *entry = begin(); entry != end(); ++entry )
		if ( entry->m_04 != first && entry->m_04 != second )
			return false;
	return true;
}

bool Gen_uw_00893e70::rva00893020()
{
	return Rva00892FD0( 4, 2 );
}

bool Gen_uw_00893e70::rva008951F0()
{
	return Rva00892FD0( 3, 2 );
}
