// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva001506A0Inner
{
	unsigned char m_pad[0x20];
	unsigned m_20;
};

class Rva001506A0
{
	unsigned char m_pad[4];
	Rva001506A0Inner *m_4;

public:
	unsigned char test() const;
};

unsigned char Rva001506A0::test() const
{
	return m_4->m_20 != 0;
}
