// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001A1AE0
{
	unsigned char m_pad[0x28];
	unsigned m_28;

public:
	void sub(unsigned v);
};

void Rva001A1AE0::sub(unsigned v)
{
	m_28 -= v;
}
