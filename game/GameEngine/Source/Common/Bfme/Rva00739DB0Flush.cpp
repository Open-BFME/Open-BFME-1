// 37-byte virtual flush

class Rva00739DB0
{
public:
	virtual void v0();
	virtual void v1();
	virtual void handle( int a, int b, unsigned char c );

	void flush();

	char          m_pad04[ 0x8 ];
	int           m_valC;
	int           m_val10;
	char          m_pad14[ 0x35 ];
	unsigned char m_byte49;
	bool          m_flag4A;
};

void Rva00739DB0::flush()
{
	if ( m_flag4A )
	{
		handle( m_valC, m_val10, m_byte49 );
		m_flag4A = false;
	}
}
