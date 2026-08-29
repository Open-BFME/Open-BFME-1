// Open-BFME5 conversions: push onto a global list, then drop a shared string.

class Rva0089E1E0
{
public:
	unsigned char cmp(int n);

	unsigned short *m_bfmeData;
};

struct Bfme5FreeTable
{
	void (__cdecl *m_bfmeF0)(void *);
	void (__cdecl *m_bfmeF1)(void *);
};

extern Bfme5FreeTable *g_bfme5FreeTable;
extern unsigned short g_bfme5SharedEmpty;

class Bfme5AttachNodeA
{
public:
	void bfmeAttach(void);

	int m_bfme00;
	int m_bfme04;
	Rva0089E1E0 m_bfmeStr;
	Bfme5AttachNodeA *m_bfmeNext;
};

extern Bfme5AttachNodeA *g_bfme5AttachListA;

void Bfme5AttachNodeA::bfmeAttach(void)
{
	m_bfmeNext = g_bfme5AttachListA;
	g_bfme5AttachListA = this;

	if (m_bfmeStr.cmp(0x21)) {
		unsigned short *h = m_bfmeStr.m_bfmeData;

		if (--*h == 0)
			g_bfme5FreeTable->m_bfmeF1(h);

		m_bfmeStr.m_bfmeData = &g_bfme5SharedEmpty;
		++g_bfme5SharedEmpty;
	}
}

class Bfme5AttachNodeB
{
public:
	void bfmeAttach(void);

	int m_bfme00;
	int m_bfme04;
	Rva0089E1E0 m_bfmeStr;
	Bfme5AttachNodeB *m_bfmeNext;
};

extern Bfme5AttachNodeB *g_bfme5AttachListB;

void Bfme5AttachNodeB::bfmeAttach(void)
{
	m_bfmeNext = g_bfme5AttachListB;
	g_bfme5AttachListB = this;

	if (m_bfmeStr.cmp(0x21)) {
		unsigned short *h = m_bfmeStr.m_bfmeData;

		if (--*h == 0)
			g_bfme5FreeTable->m_bfmeF1(h);

		m_bfmeStr.m_bfmeData = &g_bfme5SharedEmpty;
		++g_bfme5SharedEmpty;
	}
}
