// Open-BFME5: update two state bytes then forward the stored value through
// virtual slot +0x08, reconstructed from retail RVA 0x0059D2B0.

class Rva0059D2B0Object
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2( int value );

	void forward( int ignored );

	char m_padding08[4];
	unsigned char m_zero;
	unsigned char m_one;
	char m_padding0a[6];
	int m_value;
};

void Rva0059D2B0Object::forward( int ignored )
{
	int value = m_value;
	m_one = 1;
	m_zero = 0;
	v2( value );
}
