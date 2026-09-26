// cl: /O2 /Ob0

struct Rva006DB2F0Vec
{
	int a0;
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	int a7;
	int a8;
	int a9;
	int a10;
	int a11;
};

class Rva006DB2F0
{
	char m_pad[0x14];
	Rva006DB2F0Vec m_14;

public:
	void set(const Rva006DB2F0Vec *p);
};

void Rva006DB2F0::set(const Rva006DB2F0Vec *p)
{
	m_14.a0 = p->a0;
	m_14.a1 = p->a1;
	m_14.a2 = p->a2;
	m_14.a3 = p->a3;
	m_14.a4 = p->a4;
	m_14.a5 = p->a5;
	m_14.a6 = p->a6;
	m_14.a7 = p->a7;
	m_14.a8 = p->a8;
	m_14.a9 = p->a9;
	m_14.a10 = p->a10;
	m_14.a11 = p->a11;
}
