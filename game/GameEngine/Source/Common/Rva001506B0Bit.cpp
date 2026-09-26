// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva001506B0Inner
{
	unsigned char m_pad[0x20];
	unsigned m_20;
};

class Rva001506B0
{
	unsigned char m_pad[4];
	Rva001506B0Inner *m_4;

public:
	unsigned char get() const;
};

unsigned char Rva001506B0::get() const
{
	unsigned v = m_4->m_20;
	v >>= 1;
	unsigned char b = (unsigned char)v;
	b &= 1;
	return b;
}
