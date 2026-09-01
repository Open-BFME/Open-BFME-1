// Open-BFME5 conversions.

void __cdecl operator delete(void *p);

class BfmeLockVHX
{
public:
	~BfmeLockVHX();
};

class BfmeHandleVHX
{
public:
	virtual ~BfmeHandleVHX();
	void bfmeCloseVHX();
};

class BfmeThingVHX
{
public:
	void bfmeClearVHX();
	char m_bfmePad[0x80];
	BfmeHandleVHX *m_bfmeArr[10];
	char m_bfmePad2[8];
	BfmeLockVHX *m_bfmeLock;
};

void BfmeThingVHX::bfmeClearVHX()
{
	if (m_bfmeLock)
		delete m_bfmeLock;
	m_bfmeLock = 0;
	for (int i = 0; i < 10; ++i)
	{
		BfmeHandleVHX *h = m_bfmeArr[i];
		if (h)
		{
			h->bfmeCloseVHX();
			delete m_bfmeArr[i];
			m_bfmeArr[i] = 0;
		}
	}
}

class BfmeRefVHY
{
public:
	virtual void bfmeDeleteVHY();
	void bfmeReleaseVHY()
	{
		m_bfmeRefs--;
		if (m_bfmeRefs == 0)
			bfmeDeleteVHY();
	}
	int m_bfmeRefs;
};

void __cdecl bfmeDelArrVHY(void *p);

class BfmeThingVHY
{
public:
	void bfmeClearVHY();
	BfmeRefVHY *m_bfme00;
	BfmeRefVHY *m_bfme04;
	char m_bfmePad08[8];
	void *m_bfme10;
	char m_bfmePad14[12];
	void *m_bfme20;
	void *m_bfme24;
	int m_bfme28;
	char m_bfmePad2c[4];
	char m_bfme30;
};

void BfmeThingVHY::bfmeClearVHY()
{
	if (m_bfme24)
	{
		bfmeDelArrVHY(m_bfme24);
		m_bfme24 = 0;
		m_bfme28 = 0;
	}
	if (m_bfme20)
		bfmeDelArrVHY(m_bfme20);
	if (m_bfme10 && !m_bfme30)
		bfmeDelArrVHY(m_bfme10);
	if (m_bfme00)
	{
		m_bfme00->bfmeReleaseVHY();
		m_bfme00 = 0;
	}
	if (m_bfme04)
	{
		m_bfme04->bfmeReleaseVHY();
		m_bfme04 = 0;
	}
}
