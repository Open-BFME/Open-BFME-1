// cl: /O2 /DNDEBUG /MD /EHsc
//
// Seven unclaimed call-free bodies, each alone in a .text gap no ledger row
// covered: a 16-byte-aligned start directly after an int3 pad run, a terminal
// ret / ret N followed by int3 padding or the next matched row, and no call,
// ILT stub, table slot, code immediate, pin or dir32 name at the address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// 0x007F9B10 (25 bytes): copies the dwords at +4/+8/+0xC of its argument.
class Rva007F9B10
{
public:
	void assign( const Rva007F9B10 &other );

	int m_0;
	int m_4;
	int m_8;
	int m_c;
};

void Rva007F9B10::assign( const Rva007F9B10 &other )
{
	m_4 = other.m_4;
	m_8 = other.m_8;
	m_c = other.m_c;
}

// 0x008A0630 (29 bytes): the 20-byte record before `record`, wrapping from the
// first record at +0 to the last of the +0x12B0 count.
struct Rva008A0630Record
{
	char m_bytes[ 20 ];
};

class Rva008A0630Ring
{
public:
	Rva008A0630Record *previous( Rva008A0630Record *record ) const;

	Rva008A0630Record *m_records;
	char m_lead[ 0x12B0 - 4 ];
	int m_count;
};

Rva008A0630Record *Rva008A0630Ring::previous( Rva008A0630Record *record ) const
{
	Rva008A0630Record *prior = record - 1;
	if ( prior < m_records )
		prior = m_records + m_count - 1;
	return prior;
}

// 0x0094C3D0 (51 bytes): copy constructor of a refcounted handle (word count
// at +4 of the block) followed by a 16-byte value.
struct Rva0094C3D0Block
{
	char m_lead[ 4 ];
	unsigned short m_refs;
};

class Rva0094C3D0Handle
{
public:
	Rva0094C3D0Handle( const Rva0094C3D0Handle &other ) : m_block( other.m_block )
	{
		if ( m_block )
			++m_block->m_refs;
	}

	Rva0094C3D0Block *m_block;
};

struct Rva0094C3D0Box
{
	int m_values[ 4 ];
};

class Rva0094C3D0
{
public:
	Rva0094C3D0( const Rva0094C3D0 &other );

	Rva0094C3D0Handle m_handle;
	Rva0094C3D0Box m_box;
};

Rva0094C3D0::Rva0094C3D0( const Rva0094C3D0 &other )
	: m_handle( other.m_handle ), m_box( other.m_box )
{
}

// 0x00924240 / 0x00924300 (25 bytes each): ((high << 16) + low) % buckets
// over a two-dword key; `this` is never read.
struct Rva00924240Key
{
	unsigned int m_low;
	unsigned int m_high;
};

class Rva00924240Table
{
public:
	unsigned int bucketOf( const Rva00924240Key &key, unsigned int buckets ) const;
};

unsigned int Rva00924240Table::bucketOf( const Rva00924240Key &key, unsigned int buckets ) const
{
	return ( ( key.m_high << 16 ) + key.m_low ) % buckets;
}

struct Rva00924300Key
{
	unsigned int m_low;
	unsigned int m_high;
};

class Rva00924300Table
{
public:
	unsigned int bucketOf( const Rva00924300Key &key, unsigned int buckets ) const;
};

unsigned int Rva00924300Table::bucketOf( const Rva00924300Key &key, unsigned int buckets ) const
{
	return ( ( key.m_high << 16 ) + key.m_low ) % buckets;
}

// 0x008B2BB0 / 0x008B38C0 (13 / 14 bytes): six-bit type at +4 equals 0x20 /
// 0x21, as a 0/1 dword.
class Rva008B2BB0Value
{
public:
	int isType() const;

	int m_0;
	unsigned int m_type : 6;
	unsigned int m_rest : 26;
};

int Rva008B2BB0Value::isType() const
{
	return m_type == 0x20;
}

class Rva008B38C0Value
{
public:
	int isType() const;

	int m_0;
	unsigned int m_type : 6;
	unsigned int m_rest : 26;
};

int Rva008B38C0Value::isType() const
{
	return m_type == 0x21;
}
