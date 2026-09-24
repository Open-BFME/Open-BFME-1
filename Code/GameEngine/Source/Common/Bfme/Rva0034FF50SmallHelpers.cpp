// 12-byte, 13-byte, and 15-byte helper methods

class Rva0034FF50
{
public:
	void checkAndSet();

	int m_val0;
};

void Rva0034FF50::checkAndSet()
{
	if ( m_val0 == 15 )
	{
		m_val0 = 61;
	}
}

class Rva00336630
{
public:
	void addFloat34( float val );

	char  m_pad0[ 0x34 ];
	float m_val34;
};

class Rva00321EE0
{
public:
	unsigned int getBit2() const;

	char          m_pad0[ 0x344 ];
	unsigned char m_byte344;
};

