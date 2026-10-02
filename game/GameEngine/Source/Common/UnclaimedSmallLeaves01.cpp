// Eight unclaimed leaf bodies, each alone in a .text gap no ledger row
// covered.  Every one starts 16-byte aligned directly after an int3 pad run
// and ends on a ret followed by int3 padding (or the next matched row); none is
// reached by a call, ILT stub, table slot or code immediate, and no pin or
// dir32 name sits at any of the addresses.  None calls anything.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; member
// and field names say only what the bytes do.

// 0x00924360 / 0x009D63A0: cdecl equality of two two-dword records.  The two
// differ only in which argument is loaded and compared first.
struct Rva00924360Pair
{
	int m_first;
	int m_second;
};

int Rva00924360PairEqual( const Rva00924360Pair *a, const Rva00924360Pair *b )
{
	return a->m_first == b->m_first && a->m_second == b->m_second;
}

struct Rva009D63A0Pair
{
	int m_first;
	int m_second;
};

int Rva009D63A0PairEqual( const Rva009D63A0Pair *a, const Rva009D63A0Pair *b )
{
	return b->m_first == a->m_first && b->m_second == a->m_second;
}

// 0x009D6920: true when the dwords at +8 and +0xC equal those at +0 and +4.
struct Rva009D6920Position
{
	int m_first;
	int m_second;
};

class Rva009D6920Span
{
public:
	int atStart() const;

	Rva009D6920Position m_begin;
	Rva009D6920Position m_cursor;
};

int Rva009D6920Span::atStart() const
{
	Rva009D6920Position cursor = m_cursor;
	Rva009D6920Position begin = m_begin;
	return cursor.m_first == begin.m_first && cursor.m_second == begin.m_second;
}

// 0x00918F30: set or clear bit 0 of the dword at +0x148.
class Rva00918F30Flags
{
public:
	void setBit0( int on );

	char         m_lead[ 0x148 ];
	unsigned int m_flags;
};

void Rva00918F30Flags::setBit0( int on )
{
	if ( on )
		m_flags |= 1;
	else
		m_flags &= ~1u;
}

// 0x0090F270: cdecl strided dword fill.
void Rva0090F270StridedFill( char *dest, int stride, int value, int count )
{
	while ( count-- )
	{
		*(int *)dest = value;
		dest += stride;
	}
}

// 0x009266C0: cdecl lexicographic less-than over three ints.  The name and
// point type keep the ones its earlier banked attempt established.
struct Rva009266C0Point
{
	int x;
	int y;
	int z;
};

int lessXYZ( const Rva009266C0Point *a, const Rva009266C0Point *b )
{
	return a->x < b->x
		|| ( !( b->x < a->x )
			&& ( a->y < b->y
				|| ( !( b->y < a->y ) && a->z < b->z ) ) );
}

// 0x009D7880: hash of a [start,finish) char range (h = 5h + c) modulo the
// second argument; `this` is never read.
struct Rva009D7880Key
{
	const char *m_start;
	const char *m_finish;
};

class Rva009D7880Table
{
public:
	unsigned int bucketOf( const Rva009D7880Key &key, unsigned int buckets ) const;
};

unsigned int Rva009D7880Table::bucketOf( const Rva009D7880Key &key, unsigned int buckets ) const
{
	unsigned long hash = 0;
	unsigned int length = key.m_finish - key.m_start;
	const char *data = key.m_start;
	for ( unsigned int i = 0; i < length; ++i )
		hash = 5 * hash + data[ i ];
	return hash % buckets;
}

// 0x0087ECC0: bounds-checked store of one byte into element i of a vector of
// 36-byte records whose begin/end pointers sit at +0x2C/+0x30.
struct Rva0087ECC0Record
{
	char m_lead[ 0x20 ];
	char m_flag;
	char m_pad[ 3 ];
};

struct Rva0087ECC0Records
{
	Rva0087ECC0Record *m_begin;
	Rva0087ECC0Record *m_end;

	unsigned int size() const { return (unsigned int)( m_end - m_begin ); }
	Rva0087ECC0Record &operator[]( unsigned int index ) { return *( m_begin + index ); }
};

class Rva0087ECC0Owner
{
public:
	void setFlag( int index, char flag );

	char               m_lead[ 0x2C ];
	Rva0087ECC0Records m_records;
};

void Rva0087ECC0Owner::setFlag( int index, char flag )
{
	if ( index >= 0 && (unsigned int)index < m_records.size() )
		m_records[ index ].m_flag = flag;
}
