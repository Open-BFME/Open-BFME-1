// Open-BFME5 conversions.

class BfmeMgr1003
{
public:
	virtual void bfmeVM01003();
	virtual void bfmeVM11003();
	virtual void bfmeVM21003();
	virtual void bfmeVM31003();
	virtual void bfmeVM41003();
	virtual void bfmeVM51003();
	virtual void bfmeVM61003();
	virtual void bfmeVM71003();
	virtual void bfmeVM81003();
	virtual void bfmeVM91003();
	virtual void bfmeVM101003();
	virtual void bfmeVM111003();
	virtual void bfmeVM121003();
	virtual void bfmeVM131003();
	virtual void bfmeVM141003();
	virtual void bfmeVM151003();
	virtual void bfmeVM161003();
	virtual void bfmeVM171003();
	virtual void bfmeVM181003();
	virtual void bfmeVM191003();
	virtual void bfmeVM201003();
	virtual void bfmeVM211003();
	virtual void bfmeVM221003();
	virtual void bfmeVM231003();
	virtual void bfmeVM241003();
	virtual void bfmeVM251003();
	virtual void bfmeVM261003();
	virtual void bfmeVM271003();
	virtual void bfmeVM281003();
	virtual void bfmeVM291003();
	virtual void bfmeVM301003();
	virtual void bfmeVM311003();
	virtual void bfmeVM321003();
	virtual char bfmeAsk1003(void *a, int n);
};

struct BfmeOwner1003
{
	char m_bfmePad[0x1fc];
	BfmeMgr1003 *m_bfmeMgr;
};

class BfmeA1003
{
public:
	char bfmeGo1003A(void *a);
	char bfmeCheck1003(void *a);
};

char BfmeA1003::bfmeGo1003A(void *a)
{
	BfmeOwner1003 *o = *(BfmeOwner1003 **)((char *)this - 0x18);

	if (!bfmeCheck1003(a))
		return 0;

	BfmeMgr1003 *m = o->m_bfmeMgr;

	if (m && !m->bfmeAsk1003(a, 1))
		return 0;

	return 1;
}

class BfmeStop1003
{
public:
	void bfmeStop1003();
};

extern BfmeStop1003 *g_bfmeStop1003;

class BfmeB1003
{
public:
	void bfmeGo1003B(char a, char b);
	void bfmeClear1003();
	void bfmeFinish1003();

	char m_bfmePad[0x80];
	char m_bfmeOn;
};

void BfmeB1003::bfmeGo1003B(char a, char b)
{
	if (m_bfmeOn) {
		g_bfmeStop1003->bfmeStop1003();
		bfmeClear1003();
	}

	if (!a && !b)
		bfmeFinish1003();
}

class BfmeHold1003
{
public:
	void *bfmeGoalA1003();
};

class BfmeSink1003
{
public:
	virtual void bfmeVS01003();
	virtual void bfmeVS11003();
	virtual void bfmeVS21003();
	virtual void bfmeVS31003();
	virtual int bfmeRun1003();
	virtual void bfmeVS51003();
	virtual void bfmeVS61003();
	virtual void bfmeVS71003();
	virtual void bfmeVS81003();
	virtual void bfmeVS91003();
	virtual void bfmeVS101003();
	virtual void bfmeVS111003();
	virtual void bfmeVS121003();
	virtual void bfmeVS131003();
	virtual void bfmeSet1003(void *g);

	void *bfmeGoalB1003();
};

class BfmeC1003
{
public:
	int bfmeGo1003C();

	char m_bfmePad[0x1c];
	BfmeHold1003 *m_bfmeHold;
	char m_bfmePad2[4];
	BfmeSink1003 *m_bfmeSink;
};

int BfmeC1003::bfmeGo1003C()
{
	if (!m_bfmeSink)
		return -2;

	void *g = m_bfmeHold->bfmeGoalA1003();

	if (g && g != m_bfmeSink->bfmeGoalB1003())
		m_bfmeSink->bfmeSet1003(g);

	return m_bfmeSink->bfmeRun1003();
}
