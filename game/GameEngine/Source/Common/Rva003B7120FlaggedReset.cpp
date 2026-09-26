// Open-BFME5: set the two state bytes, clear the word at this+0x10, and
// dispatch the object's virtual slot +0x10, reconstructed from 0x003B7120.

class Rva003B7120Object
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();

	void reset( unsigned char value );

	char m_padding10[0x0c];
	unsigned int m_state;
	char m_padding20[0x0c];
	unsigned char m_enabled;
	unsigned char m_value;
};

void Rva003B7120Object::reset( unsigned char value )
{
	m_enabled = 1;
	m_value = value;
	m_state = 0;
	v4();
}
