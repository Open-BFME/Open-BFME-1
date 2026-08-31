// Open-BFME5 conversions.

class BfmeThingTBA
{
public:
	void bfmeGoTBA();
	void bfmeOneTBA();
	void bfmeTwoTBA();
	char m_bfmePad[0x44];
	char m_bfmeFlag;
	char m_bfmePad2[0x4f];
	int m_bfmeCount;
};

void BfmeThingTBA::bfmeGoTBA()
{
	bfmeOneTBA();
	bfmeTwoTBA();
	m_bfmeCount = 0;
	m_bfmeFlag = 0;
}

class BfmeSinkTBB
{
public:
	virtual void bfmeV0TBB() = 0;
	virtual void bfmeV1TBB() = 0;
	virtual void bfmeV2TBB() = 0;
	virtual void bfmeV3TBB() = 0;
	virtual void bfmeV4TBB() = 0;
	virtual void bfmeV5TBB() = 0;
	virtual void bfmeV6TBB() = 0;
	virtual void bfmeV7TBB() = 0;
	virtual void bfmeDoTBB(int a) = 0;
};

class BfmeThingTBB
{
public:
	void bfmeGoTBB(int a);
	void bfmeUseTBB(int a);
	char m_bfmePad[0x2c];
	BfmeSinkTBB *m_bfmeSink;
};

void BfmeThingTBB::bfmeGoTBB(int a)
{
	m_bfmeSink->bfmeDoTBB(0);
	bfmeUseTBB(a);
}
