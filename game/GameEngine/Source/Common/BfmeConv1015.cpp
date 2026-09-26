// Open-BFME5 conversions.

class BfmeI1015A
{
public:
	void bfmeDo1015A(int a, int b, int c);
};

class BfmeI1015B
{
public:
	void bfmeDo1015B(int a, int b);
};

class BfmeI1015
{
public:
	void bfmeGo1015I(int a, int b, int c);

	char m_bfmePad[0x3098];
	BfmeI1015A *m_bfmeA;
	BfmeI1015B *m_bfmeB;
};

void BfmeI1015::bfmeGo1015I(int a, int b, int c)
{
	if (m_bfmeA != 0)
		m_bfmeA->bfmeDo1015A(a, b, c);

	if (m_bfmeB != 0)
		m_bfmeB->bfmeDo1015B(a, b);
}


class BfmeMgr1015
{
public:
	virtual void bfmeVM01015();
	virtual void bfmeVM11015();
	virtual void bfmeVM21015();
	virtual void bfmeFree1015(int h, int f);
};

BfmeMgr1015 *bfmeGetMgr1015(void);

class BfmeL1015
{
public:
	void bfmeGo1015L(void);
	void bfmeReset1015(void);

	char m_bfmePad[0x10];
	int m_bfmeCount;
	int m_bfmeH;
};

void BfmeL1015::bfmeGo1015L(void)
{
	if (m_bfmeH != 0)
		bfmeGetMgr1015()->bfmeFree1015(m_bfmeH, 0);

	m_bfmeH = 0;
	m_bfmeCount = 0;
	bfmeReset1015();
}

class BfmeSub1015
{
public:
	virtual void bfmeVS01015();
	virtual void bfmeVS11015();
	virtual void bfmeVS21015();
	virtual void bfmeVS31015();
	virtual void bfmeVS41015();
	virtual void bfmeVS51015();
	virtual void bfmeVS61015();
	virtual void bfmeVS71015();
	virtual void bfmeVS81015();
	virtual void bfmeVS91015();
	virtual int bfmeTry1015(int a, int b);
};

class BfmeM1015
{
public:
	void bfmeGo1015M(int a, int b);
	void bfmeFallback1015(int a, int b);

	char m_bfmePad[0x20];
	BfmeSub1015 *m_bfmeSub;
};

void BfmeM1015::bfmeGo1015M(int a, int b)
{
	if (m_bfmeSub->bfmeTry1015(a, b) == 0)
		bfmeFallback1015(a, b);
}

class BfmeReg1015
{
public:
	virtual void bfmeVR01015();
	virtual void bfmeVR11015();
	virtual void bfmeVR21015();
	virtual void bfmeVR31015();
	virtual void bfmeVR41015();
	virtual void bfmeVR51015();
	virtual void bfmeVR61015();
	virtual void bfmeVR71015();
	virtual void bfmeVR81015();
	virtual void bfmeVR91015();
	virtual void bfmeDrop1015(int h);
};

extern BfmeReg1015 *g_bfmeReg1015;

class BfmeO1015
{
public:
	void bfmeGo1015O(int h);

	char m_bfmePad[0xc4];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeO1015::bfmeGo1015O(int h)
{
	if (h != 0)
		g_bfmeReg1015->bfmeDrop1015(h);

	m_bfmeA = 0;
	m_bfmeB = 0;
}

