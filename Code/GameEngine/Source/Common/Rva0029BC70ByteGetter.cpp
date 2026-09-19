// Retail RVA 0x0029BC70 reads the byte at this+0x34 and returns it.

class Rva0029BC70ByteGetter
{
public:
	unsigned char get() const;

private:
	unsigned char m_padding[0x34];
	unsigned char m_value;
};

unsigned char Rva0029BC70ByteGetter::get() const
{
	return m_value;
}
