// cl: /O2 /Ob0

class Rva00160620
{
	char pad[0x0C];
	Rva00160620 *m_0C;
	Rva00160620 *m_10;

public:
	void set(Rva00160620 **p);
};

void Rva00160620::set(Rva00160620 **p)
{
	m_10 = *p;
	if (*p)
		(*p)->m_0C = this;
	*p = this;
}
