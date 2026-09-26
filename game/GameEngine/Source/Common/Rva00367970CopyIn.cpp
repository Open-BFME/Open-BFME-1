// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00367970Block
{
	unsigned m[10];
};

class Rva00367970
{
	unsigned char m_pad[0x1C];
	Rva00367970Block m_1C;

public:
	void copyIn(const Rva00367970Block *src);
};

void Rva00367970::copyIn(const Rva00367970Block *src)
{
	m_1C = *src;
}
