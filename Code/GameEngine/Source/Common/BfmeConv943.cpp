// Open-BFME5 conversions.

void bfmeFreeRC(void *p);

extern char g_bfme943VftE1[];
extern char g_bfme943VftE2[];

class BfmeThing943E
{
public:
	void bfmeGo943E();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

void BfmeThing943E::bfmeGo943E()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftE1;
	if (p) {
		bfmeFreeRC(p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftE2;
	if (q) {
		bfmeFreeRC(q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}

extern char g_bfme943VftF1[];
extern char g_bfme943VftF2[];

class BfmeThing943F
{
public:
	void bfmeGo943F();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

void BfmeThing943F::bfmeGo943F()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftF1;
	if (p) {
		bfmeFreeRC(p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftF2;
	if (q) {
		bfmeFreeRC(q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}

extern char g_bfme943VftG1[];
extern char g_bfme943VftG2[];

class BfmeThing943G
{
public:
	void bfmeGo943G();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

void BfmeThing943G::bfmeGo943G()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftG1;
	if (p) {
		bfmeFreeRC(p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftG2;
	if (q) {
		bfmeFreeRC(q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}
