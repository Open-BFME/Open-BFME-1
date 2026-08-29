// Open-BFME5 conversions.

class BfmeClock997
{
public:
	virtual void bfmeV0997();
	virtual void bfmeV1997();
	virtual void bfmeV2997();
	virtual void bfmeV3997();
	virtual void bfmeV4997();
	virtual void bfmeV5997();
	virtual void bfmeV6997();
	virtual void bfmeV7997();
	virtual void bfmeV8997();
	virtual void bfmeV9997();
	virtual void bfmeV10997();
	virtual void bfmeV11997();
	virtual void bfmeV12997();
	virtual void bfmeV13997();
	virtual void bfmeV14997();
	virtual void bfmeV15997();
	virtual void bfmeV16997();
	virtual void bfmeV17997();
	virtual void bfmeV18997();
	virtual void bfmeV19997();
	virtual void bfmeV20997();
	virtual void bfmeV21997();
	virtual void bfmeV22997();
	virtual void bfmeV23997();
	virtual void bfmeV24997();
	virtual void bfmeV25997();
	virtual int bfmeNow997();
};

extern BfmeClock997 *g_bfmeClock997;

class BfmeA997
{
public:
	void bfmeGo997A(int a);
	void bfmeGo997B(int a);
	void bfmeGo997C(int a, int b);
	void bfmeToggle997();

	char m_bfmePad[0x124];
	int m_bfmeMode;
	int m_bfmeZero;
	int m_bfmeArgA;
	int m_bfmeArgB;
	char m_bfmePad2[0x1d4];
	int m_bfmeStamp;
	char m_bfmePad3[0xa1];
	char m_bfmeOn;
};

void BfmeA997::bfmeGo997A(int a)
{
	if (m_bfmeOn) {
		m_bfmeOn = 0;
		bfmeToggle997();
	}

	m_bfmeMode = 4;
	m_bfmeArgA = a;
	m_bfmeZero = 0;
	m_bfmeStamp = g_bfmeClock997->bfmeNow997();
}

void BfmeA997::bfmeGo997B(int a)
{
	if (m_bfmeOn != 1) {
		m_bfmeOn = 1;
		bfmeToggle997();
	}

	m_bfmeMode = 3;
	m_bfmeArgA = a;
	m_bfmeZero = 0;
	m_bfmeStamp = g_bfmeClock997->bfmeNow997();
}

void BfmeA997::bfmeGo997C(int a, int b)
{
	if (m_bfmeOn != 1) {
		m_bfmeOn = 1;
		bfmeToggle997();
	}

	m_bfmeMode = 5;
	m_bfmeArgA = a;
	m_bfmeArgB = b;
	m_bfmeZero = 0;
	m_bfmeStamp = g_bfmeClock997->bfmeNow997();
}
