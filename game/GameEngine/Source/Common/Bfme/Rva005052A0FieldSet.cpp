// cl: /DNDEBUG /MD /EHsc
// Retail marks this record active and stores the supplied 32-bit value.

class Rva005052A0
{
public:
	void set( unsigned int value );

private:
	unsigned char m_padding[0x43C];
	unsigned char m_active;
	unsigned int m_value;
};

void Rva005052A0::set( unsigned int value )
{
	m_active = 1;
	m_value = value;
}
