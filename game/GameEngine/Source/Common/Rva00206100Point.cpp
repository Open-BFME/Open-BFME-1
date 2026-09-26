// cl: /DNDEBUG /MD
// Retail RVA 0x00206100. Returns a three-word point by value, taken from a
// pointer vector when the index is in range and from a fallback object at +8
// otherwise. Nothing names the owner, so every class here is address-derived.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

class Rva00206100Point
{
public:
	Rva00206100Point( const Rva00206100Point &other )
		: m_bfmeX( other.m_bfmeX ), m_bfmeY( other.m_bfmeY ),
		  m_bfmeZ( other.m_bfmeZ ) {}

	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

struct Rva00206100Entry
{
	unsigned char m_bfmePad000[ 0x14 ];
	Rva00206100Point m_bfmePoint;
};

struct Rva00206100Fallback
{
	unsigned char m_bfmePad000[ 0x38 ];
	Rva00206100Point m_bfmePoint;
};

class Rva00206100Owner
{
public:
	Rva00206100Point point( int index );

	unsigned char m_bfmePad000[ 8 ];
	Rva00206100Fallback *m_bfmeFallback;
	unsigned char m_bfmePad00C[ 0x18 ];
	Rva00206100Entry **m_bfmeFirst;
	Rva00206100Entry **m_bfmeLast;
};

Rva00206100Point Rva00206100Owner::point( int index )
{
	const Rva00206100Point *source;

	if( index >= 0
		&& (unsigned int)index < (unsigned int)( m_bfmeLast - m_bfmeFirst ) )
	{
		_ReadWriteBarrier();
		source = &m_bfmeFirst[ index ]->m_bfmePoint;
	}
	else
	{
		source = &m_bfmeFallback->m_bfmePoint;
	}

	return *source;
}
