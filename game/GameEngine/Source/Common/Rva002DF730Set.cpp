// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF730
{
	unsigned char m_pad[8];
	unsigned char m_8;
	unsigned char m_pad2[0xB];
	int m_14;

public:
	void set(unsigned char v);
};

void Rva002DF730::set(unsigned char v)
{
	m_8 = v;
	m_14 = 2;
}
