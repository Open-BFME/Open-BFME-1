// Ten-slot availability scan recovered from retail RVA 0x00765AC0.

class Rva00765AC0
{
public:
	unsigned char ready( void ) const;

private:
	int m_pad;
	void *m_slots[ 10 ];
	char m_pad2[ 0xc ];
	unsigned int m_bits;
	char m_pad3[ 4 ];
	bool m_override;
};

// @?ready@Rva00765AC0@@QBEEXZ 0x00765AC0
unsigned char Rva00765AC0::ready( void ) const
{
	for( unsigned int i = 0; i < 10; ++i )
	{
		if( m_slots[ i ] != 0 )
		{
			if( m_override )
				return 1;
			return ( ( m_bits >> 5 ) & 1 ) != 0;
		}
	}
	return 1;
}
