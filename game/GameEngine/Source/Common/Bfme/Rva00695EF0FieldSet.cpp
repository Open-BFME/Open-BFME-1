// cl: /DNDEBUG /MD /EHsc
// Retail marks this record active and stores the supplied 32-bit value.

class Rva00695EF0
{
public:
	void set( unsigned int value );

private:
	unsigned char m_padding[0x637];
	unsigned char m_active;
	unsigned int m_value;
};

void Rva00695EF0::set( unsigned int value )
{
	m_active = 0;
	m_value = value;
}
