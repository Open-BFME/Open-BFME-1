// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DB1E0
{
	void *m_0;
	void *m_4;
	unsigned char m_pad[0xC];
	int m_14;

public:
	void set(void *p);
};

void Rva002DB1E0::set(void *p)
{
	m_4 = p;
	m_14 = 1;
}
