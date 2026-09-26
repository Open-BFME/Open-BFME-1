// cl: /DNDEBUG /MD /EHsc
// Retail initializes two state fields; the incoming dword is intentionally unused.

class Rva00537B10
{
public:
	void set( unsigned int ignored );

private:
	unsigned char m_padding[0x188];
	unsigned int m_value;
	unsigned char m_between[0x28];
	unsigned char m_state;
};

void Rva00537B10::set( unsigned int ignored )
{
	m_value = 1;
	m_state = 0;
}
