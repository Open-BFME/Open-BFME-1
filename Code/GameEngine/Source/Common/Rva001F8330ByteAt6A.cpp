// cl: /O2 /MD /EHsc-

class Rva001F8330ByteAt6A
{
public:
	unsigned char get() const;

private:
	char m_padding[0x6a];
	unsigned char m_value;
};

unsigned char Rva001F8330ByteAt6A::get() const
{
	return m_value;
}
