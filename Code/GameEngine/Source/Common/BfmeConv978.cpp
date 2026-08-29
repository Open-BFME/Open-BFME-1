// Open-BFME5 conversions.

class BfmeMgr978
{
public:
	virtual void bfmeVM0978();
	virtual void bfmeVM1978();
	virtual void bfmeVM2978();
	virtual void bfmeVM3978();
	virtual void bfmeVM4978();
	virtual void bfmeVM5978();
	virtual void bfmeVM6978();
	virtual void bfmeVM7978();
	virtual void bfmeVM8978();
	virtual void bfmeVM9978();
	virtual void bfmeVM10978();
	virtual void bfmeVM11978();
	virtual void bfmeVM12978();
	virtual void bfmeSend978D(int a, int b);
};

class BfmeSink978
{
public:
	virtual void bfmeVS0978();
	virtual void bfmeVS1978();
	virtual void bfmeVS2978();
	virtual void bfmeVS3978();
	virtual void bfmeVS4978();
	virtual void bfmeVS5978();
	virtual void bfmeVS6978();
	virtual void bfmeVS7978();
	virtual void bfmeVS8978();
	virtual void bfmeVS9978();
	virtual void bfmeVS10978();
	virtual void bfmeVS11978();
	virtual void bfmeVS12978();
	virtual void bfmeVS13978();
	virtual void bfmeFinish978D(int a);

	char m_bfmePad[0xc];
	int m_bfmeVal;
};

struct BfmeX978
{
	char m_bfmePad[0x1fc];
	BfmeMgr978 *m_bfmeMgr;
};

class BfmeThing978;

class BfmeLook978
{
public:
	BfmeX978 *bfmeFind978D(BfmeThing978 *t);
};

extern BfmeLook978 *g_bfmeLook978;

class BfmeD978
{
public:
	void bfmeGo978D(int unused);

	char m_bfmePad[0x1c];
	BfmeSink978 *m_bfmeSink;
	char m_bfmePad2[4];
	BfmeThing978 *m_bfmeThing;
};

void BfmeD978::bfmeGo978D(int unused)
{
	BfmeThing978 *t = m_bfmeThing;

	if (t) {
		BfmeX978 *x = g_bfmeLook978->bfmeFind978D(t);

		if (x) {
			BfmeMgr978 *m = x->m_bfmeMgr;

			if (m)
				m->bfmeSend978D(m_bfmeSink->m_bfmeVal, 2);
		}
	}

	m_bfmeSink->bfmeFinish978D(0);
}
