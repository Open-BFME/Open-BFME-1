// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva003D7E90Src
{
	char m_pad[0x10];
	unsigned m_10;
};

class Rva003D7E90
{
	unsigned m_0;
	unsigned char m_4;
	unsigned char m_5;
	unsigned m_8;

public:
	Rva003D7E90(const Rva003D7E90Src *src, unsigned char a, unsigned b, unsigned char c);
};

Rva003D7E90::Rva003D7E90(const Rva003D7E90Src *src, unsigned char a, unsigned b, unsigned char c)
{
	m_0 = src->m_10;
	m_4 = a;
	m_5 = c;
	m_8 = b;
}
