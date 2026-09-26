// cl: /O2 /Ob0

class Rva00672F30
{
	char pad[4];
	Rva00672F30 *m_04;

public:
	int count();
};

int Rva00672F30::count()
{
	int n = 0;
	Rva00672F30 *p = m_04;
	if (p)
	{
		do
		{
			p = p->m_04;
			n++;
		} while (p);
	}
	return n;
}
