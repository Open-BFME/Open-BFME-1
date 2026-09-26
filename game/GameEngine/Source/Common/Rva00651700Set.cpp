// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00651700
{
	unsigned char m_pad[0x50];
	unsigned char m_50;
	unsigned char m_51;

public:
	void set(unsigned char v);
};

void Rva00651700::set(unsigned char v)
{
	m_50 = v;
	m_51 = 1;
}
