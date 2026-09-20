// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

class Object
{
public:
	void Rva001BE7A0( Bool enable );

private:
	unsigned char m_unreconstructed[0x344];
	unsigned char m_privateStatus;
};

void Object::Rva001BE7A0( Bool enable )
{
	if ( enable )
		m_privateStatus |= 0x04;
	else
		m_privateStatus &= 0xfb;
}
