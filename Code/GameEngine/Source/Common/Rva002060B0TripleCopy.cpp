// cl: /DNDEBUG /MD
// Retail RVA 0x002060B0. The owner selects a three-word point from a
// pointer vector or a fallback record. The class names are address-derived.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

class Rva002060B0Triple
{
public:
	Rva002060B0Triple( const Rva002060B0Triple &other )
		: m_bfmeA( other.m_bfmeA ), m_bfmeB( other.m_bfmeB ),
		  m_bfmeC( other.m_bfmeC ) {}

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

struct Rva002060B0Entry
{
	unsigned char m_bfmePad000[ 8 ];
	Rva002060B0Triple m_bfmeTriple;
};

struct Rva002060B0Fallback
{
	unsigned char m_bfmePad000[ 0x38 ];
	Rva002060B0Triple m_bfmeTriple;
};

class Rva002060B0Owner
{
public:
	Rva002060B0Triple copyAt( int index );

	unsigned char m_bfmePad000[ 8 ];
	Rva002060B0Fallback *m_bfmeFallback;
	unsigned char m_bfmePad00C[ 0x18 ];
	Rva002060B0Entry **m_bfmeFirst;
	Rva002060B0Entry **m_bfmeLast;
};

Rva002060B0Triple Rva002060B0Owner::copyAt( int index )
{
	const Rva002060B0Triple *source;

	if( index >= 0
		&& (unsigned int)index < (unsigned int)( m_bfmeLast - m_bfmeFirst ) )
	{
		_ReadWriteBarrier();
		source = &m_bfmeFirst[ index ]->m_bfmeTriple;
	}
	else
	{
		source = &m_bfmeFallback->m_bfmeTriple;
	}

	return *source;
}
