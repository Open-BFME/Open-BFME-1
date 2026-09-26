// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva0044F6A0ByteGetter
{
public:
	unsigned char get(void) const;

private:
	char m_padding[9];
	unsigned char m_value;
};

unsigned char Rva0044F6A0ByteGetter::get(void) const
{
	return m_value;
}
