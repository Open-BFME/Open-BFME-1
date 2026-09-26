// cl: /DNDEBUG /MD

class Rva001BD3A0Object
{
public:
	unsigned char getByte() const;

private:
	char m_padding[0x342];
	unsigned char m_value;
};

unsigned char Rva001BD3A0Object::getByte() const
{
	return m_value;
}
