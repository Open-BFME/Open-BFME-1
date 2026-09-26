// cl: /O2 /Ob0

class Rva00478D80
{
	char pad[0x44];
	void *m_44;

public:
	int set(void *p);
};

int Rva00478D80::set(void *p)
{
	if (!p)
	{
		m_44 = this;
		return 0;
	}
	m_44 = p;
	return 0;
}
