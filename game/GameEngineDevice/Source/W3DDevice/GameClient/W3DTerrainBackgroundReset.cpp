// Retail's global operator delete[] (matched in
// game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp at 0x00881EF0); m_C0 is the
// FlatHeightMap tile array this class owns.
void operator delete[](void *memory);

class W3DTerrainBackground
{
public:
	void reset( void );

private:
	unsigned char m_padding78[ 0x78 ];
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	unsigned char m_paddingB8[ 0xB8 - 0x88 ];
	int m_B8;
	int m_BC;
	void *m_C0;
};

void W3DTerrainBackground::reset( void )
{
	m_84 = m_7C = m_80 = m_78 = 1;
	m_B8 = 0;
	m_BC = 0;

	if ( m_C0 )
	{
		::operator delete[]( m_C0 );
		m_C0 = 0;
	}
}
