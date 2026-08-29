// Open-BFME5 conversions.

class BfmeSinkA994
{
public:
	virtual void bfmeVX0994();
	virtual void bfmeVX1994();
	virtual void bfmeVX2994();
	virtual void bfmeVX3994();
	virtual void bfmeVX4994();
	virtual void bfmeVX5994();
	virtual void bfmeVX6994();
	virtual void bfmeVX7994();
	virtual void bfmeVX8994();
	virtual void bfmeVX9994();
	virtual void bfmeVX10994();
	virtual void bfmeVX11994();
	virtual void bfmeVX12994();
	virtual void bfmeVX13994();
	virtual void bfmeVX14994();
	virtual void bfmeVX15994();
	virtual void bfmeVX16994();
	virtual void bfmeVX17994();
	virtual void bfmeVX18994();
	virtual void bfmeVX19994();
	virtual void bfmeVX20994();
	virtual void bfmeVX21994();
	virtual void bfmeVX22994();
	virtual void bfmeVX23994();
	virtual void bfmeVX24994();
	virtual void bfmeVX25994();
	virtual void bfmeDrop994(void *t);
	virtual void bfmeFinish994();
};

class BfmeSinkB994
{
public:
	virtual void bfmeVX0994();
	virtual void bfmeVX1994();
	virtual void bfmeVX2994();
	virtual void bfmeVX3994();
	virtual void bfmeVX4994();
	virtual void bfmeVX5994();
	virtual void bfmeVX6994();
	virtual void bfmeVX7994();
	virtual void bfmeVX8994();
	virtual void bfmeVX9994();
	virtual void bfmeVX10994();
	virtual void bfmeVX11994();
	virtual void bfmeVX12994();
	virtual void bfmeVX13994();
	virtual void bfmeVX14994();
	virtual void bfmeVX15994();
	virtual void bfmeVX16994();
	virtual void bfmeVX17994();
	virtual void bfmeVX18994();
	virtual void bfmeVX19994();
	virtual void bfmeVX20994();
	virtual void bfmeVX21994();
	virtual void bfmeVX22994();
	virtual void bfmeVX23994();
	virtual void bfmeFree994(void *t);
};

extern BfmeSinkA994 *g_bfmeSinkA994;
extern BfmeSinkB994 *g_bfmeSinkB994;

struct BfmeHolder994
{
	void *m_bfmeVal;
};

class BfmeA994
{
public:
	void bfmeGo994A();

	char m_bfmePad[0x53c];
	BfmeHolder994 *m_bfmeHolder;
};

void BfmeA994::bfmeGo994A()
{
	void *t = m_bfmeHolder->m_bfmeVal;

	if (t) {
		g_bfmeSinkA994->bfmeDrop994(t);
		g_bfmeSinkB994->bfmeFree994(m_bfmeHolder->m_bfmeVal);
	}

	m_bfmeHolder->m_bfmeVal = 0;
	g_bfmeSinkA994->bfmeFinish994();
}

extern char g_bfmeVft994C[];

class BfmeC994
{
public:
	BfmeC994(char *a, int b);
	void bfmeBase994C();

	char *volatile m_bfmeVft;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	char *volatile m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile char m_bfme30;
};

BfmeC994::BfmeC994(char *a, int b)
{
	bfmeBase994C();

	m_bfmeVft = g_bfmeVft994C;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme04 = 0;
	m_bfme10 = a;
	m_bfme14 = b;
	m_bfme18 = 0;
	m_bfme28 = 0;
	m_bfme24 = 0;
	m_bfme20 = 0;
	m_bfme1c = 0;

	if (a)
		*a = 0;

	m_bfme30 = 0;
	m_bfme2c = 4;
}
