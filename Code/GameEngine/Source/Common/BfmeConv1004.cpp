// Open-BFME5 conversions.

class BfmeObj1004;

class BfmeMgr1004
{
public:
	virtual void bfmeVM01004();
	virtual void bfmeVM11004();
	virtual void bfmeVM21004();
	virtual void bfmeVM31004();
	virtual void bfmeVM41004();
	virtual void bfmeVM51004();
	virtual void bfmeVM61004();
	virtual void bfmeVM71004();
	virtual void bfmeVM81004();
	virtual void bfmeVM91004();
	virtual void bfmeVM101004();
	virtual void bfmeVM111004();
	virtual void bfmeVM121004();
	virtual void bfmeVM131004();
	virtual void bfmeVM141004();
	virtual void bfmeVM151004();
	virtual void bfmeVM161004();
	virtual void bfmeVM171004();
	virtual void bfmeVM181004();
	virtual void bfmeVM191004();
	virtual void bfmeVM201004();
	virtual void bfmeVM211004();
	virtual void bfmeVM221004();
	virtual void bfmeVM231004();
	virtual void bfmeVM241004();
	virtual void bfmeVM251004();
	virtual void bfmeVM261004();
	virtual void bfmeVM271004();
	virtual void bfmeVM281004();
	virtual void bfmeVM291004();
	virtual void bfmeVM301004();
	virtual void bfmeVM311004();
	virtual void bfmeVM321004();
	virtual void bfmeVM331004();
	virtual void bfmeVM341004();
	virtual void bfmeVM351004();
	virtual void bfmeNotify1004(BfmeObj1004 *o, int n);
};

class BfmeObj1004
{
public:
	void bfmeSetA1004(int a, int b);
	void bfmeSetB1004(int a);

	char m_bfmePad[0x94];
	char m_bfmeFlags;
	char m_bfmePad2[0x167];
	BfmeMgr1004 *m_bfmeMgr;
	char m_bfmePad3[0x14];
	BfmeObj1004 *m_bfmeParent;
};

char bfmeGo1004A(BfmeObj1004 *o)
{
	BfmeObj1004 *p;

	if ((o->m_bfmeFlags & 0x10) && (p = o->m_bfmeParent) != 0) {
		BfmeObj1004 *q = p->m_bfmeParent;

		if (q)
			p = q;

		o->bfmeSetA1004(6, 1);
		o->bfmeSetB1004(0);
		p->m_bfmeMgr->bfmeNotify1004(o, 0);
		return 1;
	}

	return 0;
}

class BfmeX1004
{
public:
	virtual void bfmeVX01004();
	virtual void bfmeVX11004();
	virtual void bfmeVX21004();
	virtual void bfmeVX31004();
	virtual void bfmeStop1004(int n);
	virtual void bfmeVX51004();
	virtual void bfmeVX61004();
	virtual void bfmeVX71004();
	virtual void bfmeVX81004();
	virtual void bfmeVX91004();
	virtual void bfmeVX101004();
	virtual void bfmeVX111004();
	virtual void bfmeVX121004();
	virtual void bfmeVX131004();
	virtual void bfmeVX141004();
	virtual void bfmeVX151004();
	virtual void bfmeVX161004();
	virtual void bfmeVX171004();
	virtual void bfmeVX181004();
	virtual void bfmeVX191004();
	virtual void bfmeVX201004();
	virtual void bfmeVX211004();
	virtual void bfmeVX221004();
	virtual void bfmeVX231004();
	virtual void bfmeVX241004();
	virtual void bfmeVX251004();
	virtual void bfmeVX261004();
	virtual void bfmeVX271004();
	virtual void bfmeVX281004();
	virtual void bfmeVX291004();
	virtual void bfmeVX301004();
	virtual void bfmeVX311004();
	virtual void bfmeVX321004();
	virtual void bfmeVX331004();
	virtual void bfmeVX341004();
	virtual void bfmeVX351004();
	virtual void bfmeVX361004();
	virtual void bfmeVX371004();
	virtual void bfmeVX381004();
	virtual char bfmeAsk1004();
};

class BfmeHold1004
{
public:
	BfmeX1004 *bfmeFind1004();
};

class BfmeB1004
{
public:
	void bfmeGo1004B();

	char m_bfmePad[8];
	BfmeHold1004 *m_bfmeHold;
	char m_bfmePad2[0x32c];
	char m_bfmeFlag;
	char m_bfmePad3[0xb];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeB1004::bfmeGo1004B()
{
	if (m_bfmeB) {
		BfmeX1004 *x = m_bfmeHold->bfmeFind1004();

		if (x && x->bfmeAsk1004())
			x->bfmeStop1004(1);
	}

	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeFlag = 0;
}
