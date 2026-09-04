// ?d_00749b90@@YAXXZ
// partial score=0.9 date=2026-08-29
// cl: /Oy- /Gy
// Two bit-array setters from the 0x0074xxxx run.  Identity is not recovered;
// names are address-derived.
//
// Both write one bit of a two-dimensional bitmap and both take the same shape:
// reject negative coordinates, reject coordinates past the extents, index the
// row by a pitch member and the column by x>>3, reject a byte index past the
// buffer, then set or clear bit (x & 7) according to the flag.  The bounds
// check on the byte index is UNSIGNED (`jae`) while the coordinate checks are
// signed, which is what says the index is compared against a pointer
// difference rather than against a stored count.
//
// They differ in where the buffer lives -- +0x28/+0x2c against +0x80/+0x84 --
// and in one register decision that follows from it: at 0x007497A0 `this` is
// moved out of ecx up front, because ecx has to carry the shift count later.

class Rva00749B90
{
public:
	void setBit( int x, int y, char value );

	char m_pad[ 8 ];
	int m_width;
	int m_height;
	char m_pad2[ 0x24 ];
	int m_pitch;
	char m_pad3[ 0x48 ];
	unsigned char *m_begin;
	unsigned char *m_end;
};

// @?setBit@Rva00749B90@@QAEXHHD@Z 0x00749B90
void Rva00749B90::setBit( int x, int y, char value )
{
	if( x < 0 )
		return;
	if( y < 0 )
		return;
	if( y >= m_height )
		return;
	if( x >= m_width )
		return;

	int index = m_pitch * y + ( x >> 3 );
	if( (unsigned int)index >= (unsigned int)( m_end - m_begin ) )
		return;

	unsigned char *slot = m_begin + index;
	unsigned char mask = (unsigned char)( 1 << ( x & 7 ) );
	unsigned char current = *slot;

	if( value )
		*slot = (unsigned char)( current | mask );
	else
		*slot = (unsigned char)( current & ~mask );
}

class Rva007497A0
{
public:
	void setBit( int x, int y, char value );

	char m_pad[ 8 ];
	int m_width;
	int m_height;
	char m_pad2[ 0x18 ];
	unsigned char *m_begin;
	unsigned char *m_end;
	char m_pad3[ 4 ];
	int m_pitch;
};

// @?setBit@Rva007497A0@@QAEXHHD@Z 0x007497A0
void Rva007497A0::setBit( int x, int y, char value )
{
	if( x < 0 )
		return;
	if( y < 0 )
		return;
	if( y >= m_height )
		return;
	if( x >= m_width )
		return;

	int index = m_pitch * y + ( x >> 3 );
	if( (unsigned int)index >= (unsigned int)( m_end - m_begin ) )
		return;

	unsigned char *slot = m_begin + index;
	unsigned char mask = (unsigned char)( 1 << ( x & 7 ) );
	unsigned char current = *slot;

	if( value )
		*slot = (unsigned char)( current | mask );
	else
		*slot = (unsigned char)( current & ~mask );
}
