// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003826A0
{
	unsigned char m_pad[0x18];
	unsigned m_18;
	unsigned m_1C;

public:
	unsigned copyOut(unsigned *out);
};

unsigned Rva003826A0::copyOut(unsigned *out)
{
	*out = m_1C;
	return m_18;
}
