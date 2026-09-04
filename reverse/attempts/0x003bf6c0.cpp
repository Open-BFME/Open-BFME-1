// ?test@Rva003BF6C0@@QAEEH@Z
// partial score=0.85 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Rva003BF6C0::test partial, retail 0x003BF6C0, 86 bytes.
// Prologue through probe call matches; residue is mixed fail width
// (xor al,al early vs xor eax,eax late) plus end/begin load order and
// mov eax,1 success vs setne.

class Gen003BF6C0Owner
{
public:
	int probe( void * key );
};

class Rva003BF6C0
{
public:
	unsigned char test( int index );

private:
	char m_pad00[ 0x28 ];
	Gen003BF6C0Owner *m_at28;
	char m_pad2C[ 0x4 ];
	char m_at30;
	char m_pad31[ 0x84 - 0x31 ];
	unsigned short *m_at84;
	unsigned short *m_at88;
};

unsigned char Rva003BF6C0::test( int index )
{
	Gen003BF6C0Owner *owner = m_at28;
	int idx = index;
	if( !owner || idx < 0 || !owner->probe( &m_at30 ) )
		return 0;
	unsigned short *end = m_at88;
	unsigned short *begin = m_at84;
	unsigned count = (unsigned)( end - begin );
	if( (unsigned)idx >= count )
		return 0;
	if( !( (unsigned char *)begin )[ idx * 2 + 1 ] )
		return 0;
	return 1;
}
