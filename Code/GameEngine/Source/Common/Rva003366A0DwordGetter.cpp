// Retail RVA 0x003366A0 reads the dword at this+0x3C and returns it.

class Rva003366A0DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[0x3C];
	unsigned int m_value;
};

unsigned int Rva003366A0DwordGetter::get() const
{
	return m_value;
}
