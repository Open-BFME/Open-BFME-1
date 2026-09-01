// Open-BFME5 conversions.

class BfmeXVJO;

class BfmeMsgVJO
{
public:
	void bfmeInitVJO(char *buf, int n);
	void bfmeDoneVJO();
	char m_bfmePad[0x34];
};

class BfmeAVJO
{
public:
	virtual void bfmeA00VJO();
	virtual void bfmeA04VJO();
	virtual void bfmeA08VJO();
	virtual void bfmeA0CVJO();
	virtual void bfmeA10VJO();
	virtual void bfmeA14VJO();
	virtual void bfmeA18VJO();
	virtual void bfmeA1CVJO();
	virtual void bfmeA20VJO();
	virtual void bfmeA24VJO();
	virtual void bfmeA28VJO();
	virtual void bfmeA2CVJO();
	virtual void bfmeA30VJO();
	virtual void bfmeA34VJO();
	virtual void bfmeA38VJO();
	virtual void bfmeA3CVJO();
	virtual void bfmeA40VJO();
	virtual void bfmeA44VJO();
	virtual void bfmeA48VJO(class BfmeMsgVJO *m, int id);
};

class BfmeBVJO
{
public:
	virtual void bfmeB00VJO();
	virtual void bfmeB04VJO();
	virtual void bfmeB08VJO(class BfmeMsgVJO *m, int z, void *o, int n);
};

class BfmeCVJO
{
public:
	virtual void bfmeC00VJO();
	virtual void bfmeC04VJO();
	virtual void bfmeC08VJO();
	virtual void bfmeC0CVJO();
	virtual void bfmeC10VJO();
	virtual void bfmeC14VJO();
	virtual void bfmeC18VJO();
	virtual void bfmeC1CVJO();
	virtual void bfmeC20VJO();
	virtual void bfmeC24VJO();
	virtual void bfmeC28VJO();
	virtual void bfmeC2CVJO();
	virtual void bfmeC30VJO();
	virtual class BfmeXVJO *bfmeC34VJO(int id);
	void bfmeResetVJO(class BfmeXVJO *x);
};

class BfmeDVJO
{
public:
	virtual void bfmeD00VJO();
	virtual void bfmeD04VJO();
	virtual void bfmeD08VJO();
	virtual void bfmeD0CVJO();
	virtual void bfmeD10VJO();
	virtual void bfmeD14VJO();
	virtual void bfmeD18VJO();
	virtual void bfmeD1CVJO();
	virtual void bfmeD20VJO();
	virtual void bfmeD24VJO();
	virtual void bfmeD28VJO();
	virtual void bfmeD2CVJO();
	virtual void bfmeD30VJO();
	virtual void bfmeD34VJO();
	virtual void bfmeD38VJO();
	virtual void bfmeD3CVJO();
	virtual void bfmeD40VJO();
	virtual void bfmeD44VJO(int id);
};

class BfmeRVJO
{
public:
	virtual void bfmeR00VJO();
	virtual void bfmeR04VJO();
	virtual void bfmeR08VJO();
	virtual void bfmeR0CVJO(const char *a, const char *f, int line);
};

BfmeRVJO *__cdecl bfmeReportVJO();

class BfmeThingVJO
{
public:
	void bfmeGoVJO(int id);
	char m_bfmePad00[0x10];
	BfmeAVJO *m_bfme10;
	BfmeBVJO *m_bfme14;
	char m_bfmePad18[4];
	BfmeDVJO *m_bfme1c;
	char m_bfmePad20[0x2b8];
	BfmeCVJO *m_bfme2d8;
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJO::bfmeGoVJO(int id)
{
	BfmeXVJO *p = m_bfme2d8->bfmeC34VJO(id);
	if (!p)
	{
		bfmeReportVJO()->bfmeR0CVJO("hp", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp", 0x478);
		return;
	}
	BfmeMsgVJO msg;
	msg.bfmeInitVJO(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA48VJO(&msg, id);
	m_bfme14->bfmeB08VJO(&msg, 0, this, m_bfme6dc);
	m_bfme2d8->bfmeResetVJO(p);
	m_bfme1c->bfmeD44VJO(id);
	msg.bfmeDoneVJO();
}
