// cl: /O2 /Ob0

struct Rva009F2BA0Node
{
	char pad[0x18];
	void *m_18;
	char pad2[0xF0-0x1C];
	Rva009F2BA0Node *m_F0;
};

class Rva009F2BA0
{
	Rva009F2BA0Node *m_00;
	char pad[0x14];
	void *m_18;
	void *m_1C;

public:
	void init();
};

void Rva009F2BA0::init()
{
	if (m_18)
		return;
	char *p = (char *)m_00 + 0xF0;
	m_18 = p;
	void *q = *(void **)p;
	m_1C = q;
	if (q)
		((void **)q)[6] = &m_1C;
	m_00->m_F0 = (Rva009F2BA0Node *)this;
}
