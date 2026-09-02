// ?bfmeGo96@BfmeObj96@@QAE_NHHPAX0H@Z
// partial score=0.82 date=2026-09-02
// cl: /O2 /Ob0 /G6

class BfmeHold96
{
public:
	virtual void virt0(int);
	char m_04[4];
	int m_08;
	int m_0C;
};

class BfmeG96
{
public:
	BfmeHold96 *make(void *a2, void *a3);
};

class BfmeG96b
{
public:
	char m_00[0x3C];
	int m_3C;
};

extern BfmeG96 *g_bfmeG96;
extern BfmeG96b *g_bfmeG96b;

class BfmeObj96
{
public:
	bool bfmeGo96(int a0, int a1, void *a2, void *a3, int a4);
	char m_00[4];
	char m_04;
	char m_05[3];
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	BfmeHold96 *m_18;
	void *m_1C;
};

bool BfmeObj96::bfmeGo96(int a0, int a1, void *a2, void *a3, int a4)
{
	int k = a0;
	void *p = a2;
	void *q = a3;
	if (k >= 6 || k < 1 || !p || !q)
	{
		m_04 = 0;
		return 0;
	}
	if (!m_18)
	{
		m_08 = k;
		m_0C = a1;
		m_1C = p;
		m_18 = g_bfmeG96->make(p, q);
	}
	else if (p != m_1C)
	{
		int s08 = m_18->m_08;
		int s0C = m_18->m_0C;
		m_18->virt0(1);
		m_18 = 0;
		m_08 = k;
		m_0C = a1;
		m_1C = p;
		m_18 = g_bfmeG96->make(p, q);
		if (m_18)
		{
			m_18->m_08 = s08;
			m_18->m_0C = s0C;
		}
	}
	if (!m_18)
	{
		m_04 = 0;
		return 0;
	}
	m_10 = a4;
	m_04 = 1;
	m_14 = g_bfmeG96b->m_3C + a4;
	return 1;
}
