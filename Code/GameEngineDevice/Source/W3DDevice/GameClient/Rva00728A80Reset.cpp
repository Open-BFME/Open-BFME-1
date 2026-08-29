extern "C" void Gen00881EF0( void *memory );

class Rva00728A80Reset
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

void Rva00728A80Reset::reset( void )
{
	m_84 = m_7C = m_80 = m_78 = 1;
	m_B8 = 0;
	m_BC = 0;

	if ( m_C0 )
	{
		Gen00881EF0( m_C0 );
		m_C0 = 0;
	}
}
