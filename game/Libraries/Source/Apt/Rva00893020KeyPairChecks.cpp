// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
//
// The table scan at retail 0x00892FD0 (71 bytes, ret 8), the update-or-append
// at 0x00895790 (287 bytes) on the same table, and the two
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
// UPDATE-OR-APPEND at retail 0x00895790 (287 bytes, ret 0x10), reached from
// bfmeRva00896470 and Rva008958B0Forward on the same receiver type: find the
// entry whose +0 counted string equals the key; when found, replace its +4
// value only if it equals `expected`; otherwise append {key, fallback}. The
// search has the same back-edge shape as the scan and uses the same range
// temporary, written directly in the member. Three more spellings carry the
// bytes (measured; docs/shape_levers.md): the string compare goes through a
// static helper taking both lengths as int (keeps `movzx` and a 32-bit
// compare instead of a 16-bit one), the appended element is a temporary
// (its iterators land in the dead argument homes), and the string release
// keeps its data pointer in a local across the decrement (no reload between
// `dec word [eax]` and `cmp word [eax],0`).
//
// IDENTITY IS NOT RECOVERED. Type and member names are derived from addresses
// and offsets; BfmeStrVKI / BfmeStringData3AF0 / BfmeStringPool3AF0 are the
// names sibling units already use for the counted string and its pool.

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

struct BfmeStringPool3AF0
{
	void *m_slot0;
	void (__cdecl *m_release)(BfmeStringData3AF0 *);
};
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;	// retail 0x01337A30

class BfmeStrVKI
{
public:
	BfmeStrVKI(const BfmeStrVKI &other) : m_data(other.m_data) { ++m_data->m_refCount; }
	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->m_release(data);
	}

	int length() const { return m_data->m_length; }
	bool operator==(const BfmeStrVKI &other) const
	{
		return equal(m_data, length(), other.m_data, other.length());
	}

private:
	static bool equal(const BfmeStringData3AF0 *a, int aLength, const BfmeStringData3AF0 *b, int bLength)
	{
		return aLength == bLength && (a == b || memcmp(a->m_data, b->m_data, aLength) == 0);
	}

	BfmeStringData3AF0 *m_data;
};

struct Rva00892FD0Entry
{
	Rva00892FD0Entry( const BfmeStrVKI &key, int value ) : m_00( key ), m_04( value ) {}
	BfmeStrVKI m_00;
	int m_04;
};

// retail 0x00893F10 (MASM row ?Rva00893F10@@YAXXZ): range insert taking its
// three iterators by reference.
extern "C" void __cdecl __identifier("?Rva00893F10@@YAXXZ")();

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
	void rva00895790( const BfmeStrVKI &key, int expected, int replacement, int fallback );
	bool rva00893020();
	bool rva008951F0();

private:
	Rva00892FD0Range range() { return Rva00892FD0Range( m_08, m_08 + m_00 ); }
	Rva00892FD0Entry *begin() { return range().begin(); }
	Rva00892FD0Entry *end() { return range().end(); }
	void insert( const Rva00892FD0Entry *const &first, const Rva00892FD0Entry *const &last, Rva00892FD0Entry *const &position )
	{
		union { void (__cdecl *symbol)(); void (Gen_uw_00893e70::*member)( void *, void *, void * ); } c;
		c.symbol = &__identifier("?Rva00893F10@@YAXXZ");
		( this->*c.member )( (void *)&first, (void *)&last, (void *)&position );
	}
	void push_back( const Rva00892FD0Entry &value ) { insert( &value, &value + 1, end() ); }

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

void Gen_uw_00893e70::rva00895790( const BfmeStrVKI &key, int expected, int replacement, int fallback )
{
	for ( Rva00892FD0Entry *entry = begin(); entry != end(); ++entry )
		if ( entry->m_00 == key )
		{
			if ( entry->m_04 == expected )
				entry->m_04 = replacement;
			return;
		}
	push_back( Rva00892FD0Entry( key, fallback ) );
}

bool Gen_uw_00893e70::rva00893020()
{
	return Rva00892FD0( 4, 2 );
}

bool Gen_uw_00893e70::rva008951F0()
{
	return Rva00892FD0( 3, 2 );
}
