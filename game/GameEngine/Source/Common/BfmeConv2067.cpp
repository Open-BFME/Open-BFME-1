extern char *g_bfme927Vft;

class BfmeThingGP
{
public:
	BfmeThingGP()
	{
		m_bfmeVftGP = &g_bfme927Vft;
		m_bfmeFlagGP = 0;
		m_bfmeA0GP = 0;
		m_bfmeA1GP = 0;
		m_bfmeA2GP = 0;
		m_bfmeA3GP = 0;
		m_bfmeA4GP = 0;
		m_bfmeA5GP = 0;
		m_bfmeA6GP = 0;
		m_bfmeB0GP = 1;
		m_bfmeB1GP = 1;
		m_bfmeB2GP = 1;
		m_bfmeB3GP = 1;
		m_bfmeOwnerGP = 0;
		m_bfmeC1GP = 0;
		m_bfmeC2GP = 0;
		m_bfmeD0GP = 2;
		m_bfmeD1GP = 0;
	}

	void *m_bfmeVftGP;
	char m_bfmeFlagGP;
	unsigned char m_bfmePadGP[3];
	int m_bfmeA0GP;
	int m_bfmeA1GP;
	int m_bfmeA2GP;
	int m_bfmeA3GP;
	int m_bfmeA4GP;
	int m_bfmeA5GP;
	int m_bfmeA6GP;
	int m_bfmeB0GP;
	int m_bfmeB1GP;
	int m_bfmeB2GP;
	int m_bfmeB3GP;
	int m_bfmeOwnerGP;
	int m_bfmeC1GP;
	int m_bfmeC2GP;
	int m_bfmeD0GP;
	int m_bfmeD1GP;
};

class BfmeHostGP
{
public:
	void bfmeMakeGP();

	unsigned char m_bfmeHeadGP[0x14];
	BfmeThingGP *m_bfmeThingGP;
	unsigned char m_bfmeGap2GP[0x18];
	int m_bfme30GP;
	int m_bfme34GP;
};

void BfmeHostGP::bfmeMakeGP()
{
	BfmeThingGP *p = new BfmeThingGP();

	m_bfmeThingGP = p;
	p->m_bfmeOwnerGP = m_bfme30GP;
	m_bfmeThingGP->m_bfmeC2GP = m_bfme34GP;
}
