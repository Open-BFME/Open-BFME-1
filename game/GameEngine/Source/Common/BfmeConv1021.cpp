// Open-BFME5 conversions.

class BfmeN1021
{
public:
	virtual void bfmeVN01021();
	virtual void bfmeVN11021();
	virtual void bfmeVN21021();
	virtual void bfmeVN31021();
	virtual void bfmeVN41021();
	virtual void bfmeVN51021();
	virtual void bfmeVN61021();
	virtual void bfmeVN71021();
	virtual void bfmeVN81021();
	virtual void bfmeVN91021();
	virtual void bfmeVN101021();
	virtual void bfmeVN111021();
	virtual void bfmeVN121021();
	virtual void bfmeVN131021();
	virtual void bfmeVN141021();
	virtual void bfmeVN151021();
	virtual void bfmeVN161021();
	virtual void bfmeVN171021();
	virtual void bfmeVN181021();
	virtual void bfmeVN191021();
	virtual void bfmeVN201021();
	virtual void bfmeVN211021();
	virtual void bfmeVN221021();
	virtual void bfmeVN231021();
	virtual void bfmeVN241021();
	virtual void bfmeVN251021();
	virtual void bfmeVN261021();
	virtual void bfmeVN271021();
	virtual void bfmeVN281021();
	virtual void bfmeVN291021();
	virtual void bfmeVN301021();
	virtual void bfmeVN311021();
	virtual void bfmeVN321021();
	virtual void bfmeVN331021();
	virtual void bfmeVN341021();
	virtual void bfmeVN351021();
	virtual void bfmeVN361021();
	virtual void bfmeVN371021();
	virtual void bfmeVN381021();
	virtual void bfmeVN391021();
	virtual void bfmeVN401021();
	virtual void bfmeVN411021();
	virtual void bfmeVN421021();
	virtual void bfmeVN431021();
	virtual void bfmeReg1021(void *p);
};

extern BfmeN1021 *g_bfmeN1021;

class BfmeA1021
{
public:
	void bfmeGo1021A(int unused);

	char m_bfmePad[0x50];
	void *m_bfmeP;
	char m_bfmePad2[0x54];
	int m_bfmeState;
};

void BfmeA1021::bfmeGo1021A(int unused)
{
	g_bfmeN1021->bfmeReg1021(m_bfmeP);
	m_bfmeState = 4;
}

class BfmeLog1021
{
public:
	void bfmeLog1021(int a, char *fmt, int b, int c, int d, int e, int f, int g);
};

extern BfmeLog1021 *g_bfmeLog1021;
extern char g_bfmeFmt1021B[];

class BfmeB1021
{
public:
	void bfmeGo1021B(void);

	char m_bfmePad[0x250];
	int m_bfmeId;
};

void BfmeB1021::bfmeGo1021B(void)
{
	g_bfmeLog1021->bfmeLog1021(m_bfmeId, g_bfmeFmt1021B, 0, 0, 0, 0, 0, 0);
}

class BfmeE1021
{
public:
	virtual void bfmeVE01021();
	virtual void bfmeVE11021();
	virtual void bfmeVE21021();
	virtual void bfmeVE31021();
	virtual void bfmeVE41021();
	virtual void bfmeVE51021();
	virtual void bfmeVE61021();
	virtual void bfmeVE71021();
	virtual void bfmeVE81021();
	virtual void bfmeVE91021();
	virtual void bfmeVE101021();
	virtual void bfmeVE111021();
	virtual void bfmeVE121021();
	virtual void bfmeVE131021();
	virtual void bfmeVE141021();
	virtual void bfmeVE151021();
	virtual void bfmeVE161021();
	virtual void bfmeVE171021();
	virtual void bfmeVE181021();
	virtual void bfmeVE191021();
	virtual void bfmeVE201021();
	virtual void bfmeVE211021();
	virtual void bfmeVE221021();
	virtual void bfmeVE231021();
	virtual void bfmeVE241021();
	virtual void bfmeVE251021();
	virtual int bfmeNow1021();
};

extern BfmeE1021 *g_bfmeE1021;

class BfmeD1021
{
public:
	void bfmeGo1021D(int a);

	char m_bfmePad[0x278];
	int m_bfmeFlag;
	int m_bfmeWhen;
	int m_bfmeArg;
};

void BfmeD1021::bfmeGo1021D(int a)
{
	m_bfmeWhen = g_bfmeE1021->bfmeNow1021();
	m_bfmeFlag = 0;
	m_bfmeArg = a;
}

class BfmeF1021
{
public:
	void bfmeGo1021F(int unused);
	void bfmeStart1021(int n);

	char m_bfmePad[0x188];
	int m_bfmeState;
	char m_bfmePad2[0x18];
	void *m_bfmeQ;
};

void BfmeF1021::bfmeGo1021F(int unused)
{
	bfmeStart1021(1);
	g_bfmeN1021->bfmeReg1021(m_bfmeQ);
	m_bfmeState = 3;
}

extern int g_bfmeMsg1021;
extern int g_bfmeTab1021[];
extern char g_bfmeFmt1021G[];

void bfmeGo1021G(int i)
{
	g_bfmeLog1021->bfmeLog1021(g_bfmeMsg1021, g_bfmeFmt1021G, 1, g_bfmeTab1021[i], 0, 0, 0, 0);
}
