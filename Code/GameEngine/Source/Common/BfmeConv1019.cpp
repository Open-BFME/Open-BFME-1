// Open-BFME5 conversions.

class BfmeA1019
{
public:
	void bfmeStop1019(int n);
};

class BfmeB1019
{
public:
	virtual void bfmeVB01019();
	virtual void bfmeVB11019();
	virtual void bfmeVB21019();
	virtual void bfmeVB31019();
	virtual void bfmeVB41019();
	virtual void bfmeVB51019();
	virtual void bfmeVB61019();
	virtual void bfmeVB71019();
	virtual void bfmeVB81019();
	virtual void bfmeVB91019();
	virtual void bfmeVB101019();
	virtual void bfmeVB111019();
	virtual void bfmeVB121019();
	virtual void bfmeVB131019();
	virtual void bfmeVB141019();
	virtual void bfmeVB151019();
	virtual void bfmeVB161019();
	virtual void bfmeVB171019();
	virtual void bfmeVB181019();
	virtual void bfmeVB191019();
	virtual void bfmeVB201019();
	virtual void bfmeVB211019();
	virtual void bfmeVB221019();
	virtual void bfmeVB231019();
	virtual void bfmeVB241019();
	virtual void bfmeVB251019();
	virtual void bfmeVB261019();
	virtual void bfmeRun1019(int a, int b, int c);
};

extern BfmeA1019 *g_bfmeA1019;
extern BfmeB1019 *g_bfmeB1019;

void bfmeGo1019A(void)
{
	g_bfmeA1019->bfmeStop1019(0);
	g_bfmeB1019->bfmeRun1019(2, 1, 0);
}

class BfmeS1019
{
public:
	virtual void bfmeVS01019();
	virtual void bfmeVS11019();
	virtual void bfmeDoB1019(int a, int b);
	virtual void bfmeDoC1019(int a, int b);
};

extern BfmeS1019 *g_bfmeS1019;
extern char g_bfmeName1019[];
void bfmeInit1019(char *n);

void bfmeGo1019B(int a)
{
	if (g_bfmeS1019 == 0)
		bfmeInit1019(g_bfmeName1019);

	g_bfmeS1019->bfmeDoB1019(a, 0);
}

void bfmeGo1019C(int a)
{
	if (g_bfmeS1019 == 0)
		bfmeInit1019(g_bfmeName1019);

	g_bfmeS1019->bfmeDoC1019(a, 0);
}

struct BfmeT1019
{
	char m_bfmePad[0x1d];
	char m_bfmeFlag;
};

class BfmeU1019
{
public:
	virtual void bfmeVU01019();
	virtual void bfmeVU11019();
	virtual void bfmeVU21019();
	virtual void bfmeVU31019();
	virtual void bfmeVU41019();
	virtual void bfmeVU51019();
	virtual void bfmeVU61019();
	virtual void bfmeVU71019();
	virtual void bfmeVU81019();
	virtual void bfmeVU91019();
	virtual void bfmeVU101019();
	virtual void bfmeVU111019();
	virtual void bfmeTick1019();
};

extern BfmeT1019 *g_bfmeT1019;
extern BfmeU1019 *g_bfmeU1019;
void bfmeFirst1019(void);

void bfmeGo1019F(void)
{
	bfmeFirst1019();
	g_bfmeT1019->m_bfmeFlag = 1;
	g_bfmeU1019->bfmeTick1019();
}
