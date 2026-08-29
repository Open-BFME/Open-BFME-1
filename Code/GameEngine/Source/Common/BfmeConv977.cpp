// Open-BFME5 conversions.

class BfmeB977;

class BfmeMgr977
{
public:
	void *bfmeFind977B(BfmeB977 *b);
	void bfmeDo977B(int a, void *x);
};

extern BfmeMgr977 *g_bfmeMgr977;

struct BfmeRec977
{
	char m_bfmePad[4];
	short m_bfmeKind;
};

class BfmeB977
{
public:
	void bfmeGo977B(int unused);

	BfmeRec977 *m_bfmeRec;
};

void BfmeB977::bfmeGo977B(int unused)
{
	BfmeRec977 *r = m_bfmeRec;

	if (r && r->m_bfmeKind != 0) {
		void *x = g_bfmeMgr977->bfmeFind977B(this);

		if (x)
			g_bfmeMgr977->bfmeDo977B(0, x);
	}
}

class BfmeClock977
{
public:
	virtual void bfmeV0977();
	virtual void bfmeV1977();
	virtual void bfmeV2977();
	virtual void bfmeV3977();
	virtual void bfmeV4977();
	virtual void bfmeV5977();
	virtual void bfmeV6977();
	virtual void bfmeV7977();
	virtual void bfmeV8977();
	virtual void bfmeV9977();
	virtual void bfmeV10977();
	virtual void bfmeV11977();
	virtual void bfmeV12977();
	virtual void bfmeV13977();
	virtual void bfmeV14977();
	virtual void bfmeV15977();
	virtual void bfmeV16977();
	virtual void bfmeV17977();
	virtual void bfmeV18977();
	virtual void bfmeV19977();
	virtual void bfmeV20977();
	virtual void bfmeV21977();
	virtual void bfmeV22977();
	virtual void bfmeV23977();
	virtual void bfmeV24977();
	virtual void bfmeV25977();
	virtual void bfmeV26977();
	virtual void bfmeV27977();
	virtual void bfmeV28977();
	virtual void bfmeV29977();
	virtual void bfmeV30977();
	virtual void bfmeV31977();
	virtual void bfmeV32977();
	virtual void bfmeV33977();
	virtual void bfmeV34977();
	virtual void bfmeV35977();
	virtual void bfmeV36977();
	virtual void bfmeV37977();
	virtual void bfmeV38977();
	virtual void bfmeV39977();
	virtual void bfmeV40977();
	virtual void bfmeV41977();
	virtual void bfmeV42977();
	virtual int bfmeNow977C();
};

extern BfmeClock977 *g_bfmeClock977;

char bfmeFallback977C();

class BfmeC977
{
public:
	char bfmeGo977C();

	char m_bfmePad[0x19c];
	int *m_bfmeBuf;
	char m_bfmePad2[0x10];
	int m_bfmeStamp;
};

char BfmeC977::bfmeGo977C()
{
	if (m_bfmeBuf[-1] != -1 && m_bfmeStamp != 0
			&& m_bfmeStamp == g_bfmeClock977->bfmeNow977C())
		return 1;

	return bfmeFallback977C();
}
