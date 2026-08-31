// ?setBit@Rva00749A10@@QAEXHHD@Z
// partial score=0.7 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// Retail 0x00749A10 is a bounds-checked bit setter for a two-dimensional
// byte bitmap.  The concrete class identity is not present in the available
// BFME source or symbols, so the address-derived class name is intentional.
class Rva00749A10
{
public:
	void setBit( int x, int y, char value );

	char m_pad[ 8 ];
	int m_width;
	int m_height;
	char m_pad2[ 0x24 ];
	int m_pitch;
	char m_pad3[ 0x3C ];
	unsigned char *m_begin;
	unsigned char *m_end;
};

void Rva00749A10::setBit( int x, int y, char value )
{
	Rva00749A10 *self = this;

	if( x < 0 )
		return;
	if( y < 0 )
		return;
	if( y >= self->m_height )
		return;
	if( x >= self->m_width )
		return;

	int index = self->m_pitch * y + ( x >> 3 );
	if( (unsigned int)index >= (unsigned int)( self->m_end - self->m_begin ) )
		return;

	unsigned char *slot = self->m_begin + index;
	unsigned char mask = (unsigned char)( 1 << ( x & 7 ) );
	unsigned char current = *slot;

	if( value )
		*slot = (unsigned char)( current | mask );
	else
		*slot = (unsigned char)( current & ~mask );
}
