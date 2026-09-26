// Open-BFME5 conversions.

struct BfmeObj975A
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeA975
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeStart975A(BfmeObj975A *o);
	virtual void bfmeStop975A(BfmeObj975A *o);

	void bfmeGo975A(BfmeObj975A *o);
};

void BfmeA975::bfmeGo975A(BfmeObj975A *o)
{
	if (o && !(o->m_bfmeFlags & 1)) {
		bfmeStart975A(o);
		bfmeStop975A(o);
	}
}

class BfmeMgr975B
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeV13975();
	virtual void bfmeV14975();
	virtual void bfmeV15975();
	virtual void bfmeV16975();
	virtual void bfmeV17975();
	virtual void bfmeV18975();
	virtual void bfmeV19975();
	virtual void bfmeV20975();
	virtual void bfmeV21975();
	virtual void bfmeV22975();
	virtual void bfmeV23975();
	virtual void bfmeV24975();
	virtual void bfmeV25975();
	virtual int bfmeReady975B();
};

struct BfmeHold975B
{
	char m_bfmePad[0x1fc];
	BfmeMgr975B *m_bfmeMgr;
};

class BfmeB975
{
public:
	void bfmeGo975B(int a, int b);
	void bfmeSend975B(int a, int b);

	char m_bfmePad[8];
	BfmeHold975B *m_bfmeHold;
};

void BfmeB975::bfmeGo975B(int a, int b)
{
	BfmeMgr975B *m = m_bfmeHold->m_bfmeMgr;

	if (m && m->bfmeReady975B())
		bfmeSend975B(a, b);
}

class BfmeFind975D
{
public:
	void *bfmeFind975D(int a);
};

extern BfmeFind975D *g_bfmeFind975D;

class BfmeD975
{
public:
	char bfmeGo975D(int a);
	char bfmeUse975D(void *p);
};

char BfmeD975::bfmeGo975D(int a)
{
	void *p = g_bfmeFind975D->bfmeFind975D(a);

	if (p)
		return bfmeUse975D(p);

	return 0;
}
