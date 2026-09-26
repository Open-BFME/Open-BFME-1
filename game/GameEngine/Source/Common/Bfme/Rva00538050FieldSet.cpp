// cl: /DNDEBUG /MD /EHsc
// Retail stores the pointer and tracks whether it is null, then clears the next flag.

class Rva00538050
{
public:
	void set( void *value );

private:
	void *m_value;
	unsigned char m_padding;
	unsigned char m_isNull;
	unsigned char m_state;
};

void Rva00538050::set( void *value )
{
	m_value = value;
	m_isNull = value == 0;
	m_state = 0;
}
