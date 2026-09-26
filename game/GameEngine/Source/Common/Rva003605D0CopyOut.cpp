// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva003605D0Block
{
	unsigned m[10];
};

class Rva003605D0
{
	unsigned char m_pad[0x50];
	Rva003605D0Block m_50;

public:
	Rva003605D0Block *copyOut(Rva003605D0Block *dest) const;
};

Rva003605D0Block *Rva003605D0::copyOut(Rva003605D0Block *dest) const
{
	*dest = m_50;
	return dest;
}
