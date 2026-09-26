// cl: /DNDEBUG /MD

class Rva0037A860ByteGetter
{
public:
	unsigned char getByte(void) const;

private:
	unsigned char m_padding[0x2D];
	unsigned char m_value;
};

unsigned char Rva0037A860ByteGetter::getByte(void) const
{
	return m_value;
}
