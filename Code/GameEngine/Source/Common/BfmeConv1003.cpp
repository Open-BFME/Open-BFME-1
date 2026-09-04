// Open-BFME5 conversions.

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
