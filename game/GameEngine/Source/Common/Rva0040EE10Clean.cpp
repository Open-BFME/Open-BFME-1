// cl: /O2 /Ob0

class BfmeStrEE
{
public:
	void set(const BfmeStrEE &);
	void *m_data;
};

extern BfmeStrEE g_bfmeEmptyEE;

class BfmeHoldEE
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
};

class BfmeObjEE
{
public:
	void bfmeGoEE();
	void bfmeRelEE();
	char m_00[0x34];
	BfmeHoldEE *m_34;
	char m_38[0x28];
	char m_60;
	char m_61[0x63];
	void *m_C4;
	void *m_C8;
	BfmeStrEE m_CC;
	char m_D0[0xC];
	int m_DC;
	int m_E0;
	char m_E4[0x24];
	char m_108;
};

void BfmeObjEE::bfmeGoEE()
{
	BfmeHoldEE *p = m_34;
	m_108 = 0;
	m_60 = 0;
	if (p)
	{
		bfmeRelEE();
		m_34->v7();
		m_34 = 0;
	}
	BfmeStrEE *s = &m_CC;
	m_C4 = 0;
	m_C8 = 0;
	if (s->m_data && *(short *)((char *)s->m_data + 4))
		s->set(g_bfmeEmptyEE);
	int n = -1;
	m_E0 = n;
	m_DC = n;
}
