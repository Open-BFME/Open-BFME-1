// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG

class Rva007497A0
{
public:
	void setBit( int x, int y, bool value );

	char m_pad[ 8 ];
	int m_width;
	int m_height;
	char m_pad2[ 0x18 ];
	unsigned char *m_begin;
	unsigned char *m_end;
	char m_pad3[ 4 ];
	int m_pitch;
};

// ?setBit@Rva007497A0@@QAEXHHD@Z 0x007497A0
void Rva007497A0::setBit( int x, int y, bool value )
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

	if( value )
		m_begin[index] |= (unsigned char)( 1 << ( x & 7 ) );
	else
		m_begin[index] &= (unsigned char)~( 1 << ( x & 7 ) );
}
