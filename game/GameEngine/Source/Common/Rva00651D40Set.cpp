// cl: /O2 /Ob0

class Rva00651D40
{
	int m_00;
	int m_04;
	int m_08;
	int *m_0C;

public:
	void set(int *p);
};

void Rva00651D40::set(int *p)
{
	m_0C = p;
	int v = *p;
	m_04 = v;
	m_08 = v + 0x1F0;
}
