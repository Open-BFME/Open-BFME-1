// Open-BFME5 conversions.

class BfmeSrcUDB
{
public:
	float bfmeCallUDB(int a, int b);
};

extern BfmeSrcUDB *g_bfmeObjUDB;
extern float g_bfmeKUDB;

float __stdcall bfmeGoUDB(int a, int b)
{
	if (g_bfmeObjUDB)
		return g_bfmeObjUDB->bfmeCallUDB(a, b);
	return g_bfmeKUDB;
}

class BfmeSrcUDC
{
public:
	void bfmeCloseUDC();
};

extern BfmeSrcUDC *g_bfmeObjUDC;

int bfmeGoUDC(void)
{
	if (g_bfmeObjUDC) {
		g_bfmeObjUDC->bfmeCloseUDC();
		g_bfmeObjUDC = 0;
	}
	return 1;
}

class BfmeSubUDD
{
public:
	void *bfmeFindUDD(int key);
};

class BfmeMgrUDD
{
public:
	char m_bfmePad[0x28];
	BfmeSubUDD *m_bfmeSub;
};

extern BfmeMgrUDD *g_bfmeMgrUDD;
extern char g_bfmeDefaultUDD[];

class BfmeThingUDD
{
public:
	void *bfmeGoUDD();
	char m_bfmePad[0x2c];
	int m_bfmeKey;
};

void *BfmeThingUDD::bfmeGoUDD()
{
	int k = m_bfmeKey;
	BfmeSubUDD *s = g_bfmeMgrUDD->m_bfmeSub;
	if (s)
		return s->bfmeFindUDD(k);
	return g_bfmeDefaultUDD;
}

class BfmeRecUDE
{
public:
	virtual void bfmeV0UDE() = 0;
	virtual void bfmeV1UDE() = 0;
	virtual void bfmeV2UDE() = 0;
	virtual void bfmeV3UDE() = 0;
	virtual void bfmeV4UDE() = 0;
	virtual void bfmeV5UDE() = 0;
	virtual void bfmeV6UDE() = 0;
	virtual void bfmeV7UDE() = 0;
	virtual void bfmeV8UDE() = 0;
	virtual void bfmeV9UDE() = 0;
	virtual void *bfmeGetUDE() = 0;
};

class BfmeMgrUDE
{
public:
	BfmeRecUDE *bfmeFindUDE(int key);
};

extern BfmeMgrUDE *g_bfmeMgrUDE;

class BfmeThingUDE
{
public:
	void *bfmeGoUDE();
	char m_bfmePad[0x60];
	int m_bfmeKey;
};

void *BfmeThingUDE::bfmeGoUDE()
{
	BfmeRecUDE *r = g_bfmeMgrUDE->bfmeFindUDE(m_bfmeKey);
	if (r)
		return r->bfmeGetUDE();
	return 0;
}
