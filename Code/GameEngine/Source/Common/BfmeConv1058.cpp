// Open-BFME5 conversions.

class BfmeStr1058
{
public:
	void bfmeSet1058(char *t, int n);
};

class BfmeB1058
{
public:
	virtual void bfmeVB01058();
	virtual void bfmeVB11058();
	virtual void bfmeVB21058();
	virtual void bfmeVB31058();
	virtual void bfmeVB41058();
	virtual void bfmeVB51058();
	virtual void bfmeVB61058();
	virtual void bfmeVB71058();
	virtual void bfmeVB81058();
	virtual void bfmeVB91058();
	virtual void bfmeVB101058();
	virtual void bfmeVB111058();
	virtual void bfmeVB121058();
	virtual void bfmeVB131058();
	virtual void bfmeVB141058();
	virtual void bfmeVB151058();
	virtual void bfmeVB161058();
	virtual void bfmeVB171058();
	virtual void bfmeVB181058();
	virtual void bfmeKill1058(int v);
};

extern BfmeB1058 *g_bfmeB1058;
extern char g_bfmeLit1058[];

class BfmeA1058
{
public:
	void bfmeGo1058A(void);

	char m_bfmePad[0xc];
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad2[4];
	BfmeStr1058 m_bfmeStr;
	char m_bfmePad3[3];
	int m_bfme20;
	short m_bfme24;
};

void BfmeA1058::bfmeGo1058A(void)
{
	int z = 0;
	int v = m_bfme10;

	m_bfme0c = z;
	g_bfmeB1058->bfmeKill1058(v);
	m_bfme10 = 1;
	m_bfme14 = z;
	m_bfmeStr.bfmeSet1058(g_bfmeLit1058, 0);
	m_bfme20 = z;
	m_bfme24 = (short)z;
}

class BfmeJ1058
{
public:
	void bfmeSet1058J(int a, bool on);
};

extern BfmeJ1058 *g_bfmeJ1058;

class BfmeC1058
{
public:
	void bfmeGo1058C(void);

	char m_bfmePad[4];
	int m_bfme04;
	BfmeStr1058 m_bfmeStr;
	char m_bfmePad2[3];
	int m_bfme0c;
	char m_bfmePad3[8];
	int m_bfme18;
	float m_bfme1c;
	char m_bfmePad4[4];
	char m_bfme24;
};

void BfmeC1058::bfmeGo1058C(void)
{
	int z = 0;

	m_bfme0c = z;
	m_bfme18 = z;
	m_bfme1c = 1.0f;
	m_bfmeStr.bfmeSet1058(g_bfmeLit1058, 0);
	m_bfme24 = (char)z;
	g_bfmeJ1058->bfmeSet1058J(m_bfme04, true);
}

class BfmeK1058
{
public:
	void bfmeUse1058(int r);
};

extern BfmeK1058 *g_bfmeK1058;
void bfmeGet1058(int p, int *t);
int bfmeConv1058(int p, int t);

class BfmeD1058
{
public:
	void bfmeGo1058D(void);

	char m_bfmePad[0x244];
	int m_bfmeP;
};

void BfmeD1058::bfmeGo1058D(void)
{
	int t;

	bfmeGet1058(m_bfmeP, &t);
	g_bfmeK1058->bfmeUse1058(bfmeConv1058(m_bfmeP, t));
}

class BfmeSubE1058
{
public:
	virtual void bfmeVS01058();
	virtual void bfmeVS11058();
	virtual void bfmeVS21058();
	virtual void bfmeVS31058();
	virtual void bfmeVS41058();
	virtual void bfmeVS51058();
	virtual void bfmeVS61058();
	virtual void bfmeVS71058();
	virtual void bfmeVS81058();
	virtual void bfmeVS91058();
	virtual void bfmeVS101058();
	virtual void bfmeVS111058();
	virtual void bfmeVS121058();
	virtual void bfmeVS131058();
	virtual void bfmeVS141058();
	virtual void bfmeVS151058();
	virtual void bfmeVS161058();
	virtual void bfmeVS171058();
	virtual void bfmeVS181058();
	virtual void bfmeVS191058();
	virtual void bfmeVS201058();
	virtual void bfmeVS211058();
	virtual void bfmeVS221058();
	virtual void bfmeSet1058E(bool on);
};

class BfmeT1058
{
public:
	virtual void bfmeVT01058();
	virtual void bfmeVT11058();
	virtual void bfmeVT21058();
	virtual void bfmeVT31058();
	virtual void bfmeVT41058();
	virtual void bfmeVT51058();
	virtual void bfmeVT61058();
	virtual void bfmeVT71058();
	virtual void bfmeVT81058();
	virtual void bfmeVT91058();
	virtual void bfmeVT101058();
	virtual void bfmeVT111058();
	virtual void bfmeVT121058();
	virtual void bfmeVT131058();
	virtual void bfmeVT141058();
	virtual void bfmeVT151058();
	virtual void bfmeVT161058();
	virtual void bfmeVT171058();
	virtual void bfmeVT181058();
	virtual void bfmeVT191058();
	virtual void bfmeVT201058();
	virtual void bfmeVT211058();
	virtual void bfmeVT221058();
	virtual void bfmeVT231058();
	virtual void bfmeVT241058();
	virtual void bfmeVT251058();
	virtual int bfmeNow1058();
};

extern BfmeT1058 *g_bfmeT1058;
extern int g_bfmeX1058;
extern int g_bfmeY1058;

class BfmeE1058
{
public:
	void bfmeGo1058E(void);
	void bfmeBase1058(void);

	char m_bfmePad[0xc];
	BfmeSubE1058 m_bfmeSub;
	char m_bfmePad2[0x8c];
	int m_bfme9c;
	char m_bfmePad3[0x118];
	int m_bfme1b8;
};

void BfmeE1058::bfmeGo1058E(void)
{
	bfmeBase1058();
	m_bfme9c = g_bfmeX1058;
	g_bfmeY1058 = g_bfmeT1058->bfmeNow1058();
	m_bfmeSub.bfmeSet1058E(m_bfme1b8 != 0);
}
