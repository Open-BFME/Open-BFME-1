// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003609F0
{
	unsigned char m_pad[0x20];
	unsigned m_20;

public:
	void clamp();
};

void Rva003609F0::clamp()
{
	if (m_20 != 1)
		m_20 = 0;
}
