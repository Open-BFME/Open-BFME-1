// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0037D0A0
{
	unsigned char m_pad[0x20];
	unsigned m_20;

public:
	void add(unsigned v);
};

void Rva0037D0A0::add(unsigned v)
{
	m_20 += v;
}
