// cl: /O2 /Ob0

struct Rva009A2350Node
{
	char pad[8];
	Rva009A2350Node *m_08;
	char pad2[4];
	void *m_10;
};

class Rva009A2350
{
	Rva009A2350Node *m_00;
	char pad[0x0C];
	void *m_10;
	void *m_14;

public:
	void init();
};

void Rva009A2350::init()
{
	if (m_10)
		return;
	char *p = (char *)m_00 + 8;
	m_10 = p;
	void *q = *(void **)p;
	m_14 = q;
	if (q)
		((void **)q)[4] = &m_14;
	m_00->m_08 = (Rva009A2350Node *)this;
}
