// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001E1880
{
	unsigned char m_pad[0x10];
	unsigned m_10;

public:
	void set(unsigned v);
};

void Rva001E1880::set(unsigned v)
{
	if (m_10 != v)
		m_10 = v;
}
