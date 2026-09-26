// cl: /DNDEBUG /MD /EHsc
// Retail replaces the selected high bit-field while preserving all other bits.

class Rva006C5310
{
public:
	void set( unsigned int value );

private:
	unsigned int m_value;
};

void Rva006C5310::set( unsigned int value )
{
	m_value = (m_value & 0xFFEFFFFFu) | (value << 20);
}
