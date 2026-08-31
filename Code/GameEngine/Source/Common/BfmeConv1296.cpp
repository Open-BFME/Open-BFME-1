// Open-BFME5 conversions.

class BfmeLogSNA
{
public:
	virtual void bfmeV0SNA() = 0;
	virtual void bfmeSaySNA(const char *s) = 0;
};

class BfmeCtlSNA
{
public:
	virtual void bfmeV0SNA() = 0;
	virtual void bfmeV1SNA() = 0;
	virtual void bfmeModeSNA(int a, int b) = 0;
};

BfmeLogSNA *bfmeGetSNA(void);

class BfmeThingSNA
{
public:
	void bfmeOneSNA();
	void bfmeTwoSNA();
	char m_bfmePad[0x6a4];
	BfmeCtlSNA *m_bfmeCtl;
};

void BfmeThingSNA::bfmeOneSNA()
{
	bfmeGetSNA()->bfmeSaySNA("conn made\n");
	m_bfmeCtl->bfmeModeSNA(3, 0);
}

void BfmeThingSNA::bfmeTwoSNA()
{
	bfmeGetSNA()->bfmeSaySNA("conn broken\n");
	m_bfmeCtl->bfmeModeSNA(0, 0);
}
