// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00538B20
{
	void *m_0;
	char m_4;
	unsigned char m_5;
	unsigned char m_6;

public:
	Rva00538B20 *set(void *p);
};

Rva00538B20 *Rva00538B20::set(void *p)
{
	m_0 = p;
	m_5 = p == 0;
	m_6 = 0;
	return this;
}
