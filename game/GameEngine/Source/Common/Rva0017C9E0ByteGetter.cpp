// Retail 0x0017C9E0 reads the byte at this+0x21 and returns it.

class Rva0017C9E0ByteGetter
{
public:
	unsigned char get();

private:
	char m_padding[ 0x21 ];
	unsigned char m_value;
};

unsigned char Rva0017C9E0ByteGetter::get()
{
	return m_value;
}
