// Twelve accessors on ONE object, one per vector member, all twelve landing in
// a single 0x60-spaced block of retail.
//
// WHAT THE BYTES SHOW.  A __thiscall with no stack arguments.  It reads two
// pointers at OFFSET and OFFSET+4, takes their difference, divides by 0x70 (the
// magic-multiply for 112) to get an element COUNT, and compares that count
// UNSIGNED against a dword at a fixed 0x148.  When the count is greater it
// returns first + index*0x70; otherwise it returns the address of one fixed
// global.
//
// The re-load of the OFFSET pointer in the hit path is the detail that fixes the
// source.  A single flat expression over two members keeps the base in a
// register and the body comes out at 63 bytes.  Retail loads [ecx+OFFSET] a
// SECOND time and costs 69, which is what a size() taken on a SUB-OBJECT and an
// indexing done on that same sub-object compile to -- the container is named
// twice, so the composite is a member struct, not two loose pointers.
//
// ONE OBJECT, NOT TWELVE.  The twelve offsets are 0xA8, 0xB4, 0xC0 ... 0x12C:
// an arithmetic progression of TWELVE bytes.  A three-pointer vector is twelve
// bytes, so this is one array-of-twelve region on one class, all twelve sharing
// the same index member at 0x148, the same 0x70 element width, and the SAME
// fallback address.  One shared global is therefore the right model -- twelve
// separate globals at one address would gate green and still be wrong.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The fallback global's
// address is a DIR32 site filled from retail; it is not evidence of anything
// beyond being ONE address shared by all twelve.
//
// WHAT THE BYTES CANNOT DECIDE.  The element type beyond its 0x70 width; the
// third pointer of each vector (never read here); everything before 0xA8 and
// between 0x134 and 0x148.

struct Q3IndexedItem { char m_bytes[ 0x70 ]; };

extern Q3IndexedItem g_q3IndexedFallback;

struct Q3IndexedVector
{
	Q3IndexedItem *m_start;
	Q3IndexedItem *m_finish;
	Q3IndexedItem *m_endOfStorage;
	unsigned int size() const { return (unsigned int)( m_finish - m_start ); }
};

struct Q3IndexedOwner
{
	char m_lead[ 0xA8 ];
	Q3IndexedVector m_vA8;
	Q3IndexedVector m_vB4;
	Q3IndexedVector m_vC0;
	Q3IndexedVector m_vCC;
	Q3IndexedVector m_vD8;
	Q3IndexedVector m_vE4;
	Q3IndexedVector m_vF0;
	Q3IndexedVector m_vFC;
	Q3IndexedVector m_v108;
	Q3IndexedVector m_v114;
	Q3IndexedVector m_v120;
	Q3IndexedVector m_v12C;
	char m_gap[ 0x148 - 0x138 ];
	unsigned int m_index;
	Q3IndexedItem *Rva0049B320();
	Q3IndexedItem *Rva0049B3E0();
	Q3IndexedItem *Rva0049B380();
	Q3IndexedItem *Rva0049B440();
	Q3IndexedItem *Rva0049B4A0();
	Q3IndexedItem *Rva0049B560();
	Q3IndexedItem *Rva0049B500();
	Q3IndexedItem *Rva0049B5C0();
	Q3IndexedItem *Rva0049B620();
	Q3IndexedItem *Rva0049B6E0();
	Q3IndexedItem *Rva0049B680();
	Q3IndexedItem *Rva0049B740();
};

Q3IndexedItem *Q3IndexedOwner::Rva0049B320()
{
	if ( m_vA8.size() > m_index )
		return m_vA8.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B3E0()
{
	if ( m_vB4.size() > m_index )
		return m_vB4.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B380()
{
	if ( m_vC0.size() > m_index )
		return m_vC0.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B440()
{
	if ( m_vCC.size() > m_index )
		return m_vCC.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B4A0()
{
	if ( m_vD8.size() > m_index )
		return m_vD8.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B560()
{
	if ( m_vE4.size() > m_index )
		return m_vE4.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B500()
{
	if ( m_vF0.size() > m_index )
		return m_vF0.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B5C0()
{
	if ( m_vFC.size() > m_index )
		return m_vFC.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B620()
{
	if ( m_v108.size() > m_index )
		return m_v108.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B6E0()
{
	if ( m_v114.size() > m_index )
		return m_v114.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B680()
{
	if ( m_v120.size() > m_index )
		return m_v120.m_start + m_index;
	return &g_q3IndexedFallback;
}

Q3IndexedItem *Q3IndexedOwner::Rva0049B740()
{
	if ( m_v12C.size() > m_index )
		return m_v12C.m_start + m_index;
	return &g_q3IndexedFallback;
}

