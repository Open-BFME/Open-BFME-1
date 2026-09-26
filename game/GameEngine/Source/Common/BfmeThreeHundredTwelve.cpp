class BfmeMakerRE
{
public:
	virtual void bfmeSpareRE0();
	virtual void bfmeSpareRE1();
	virtual void bfmeSpareRE2();
	virtual void bfmeSpareRE3();
	virtual void bfmeSpareRE4();
	virtual void bfmeDoRE();
};

struct BfmeHolderRE
{
	unsigned char m_bfmeHead[0x2a0];
	BfmeMakerRE *m_bfmeMaker;
};

BfmeMakerRE *bfmeMakeRE();
void Rva007E8640Copy(char *destination, unsigned int capacity, const char *source);

class BfmeThingRE
{
public:
	void bfmeRunRE();
	void bfmeRva007EA4C0SetHolderByte(unsigned char value);
	void bfmeRva007EA4D0SetHolderText(const char *text);
	unsigned char m_bfmeHead[4];
	BfmeHolderRE *m_bfmeHolder;
};

void BfmeThingRE::bfmeRunRE()
{
	BfmeHolderRE *holder = m_bfmeHolder;
	if (holder->m_bfmeMaker == 0)
		holder->m_bfmeMaker = bfmeMakeRE();
	m_bfmeHolder->m_bfmeMaker->bfmeDoRE();
}

void BfmeThingRE::bfmeRva007EA4C0SetHolderByte(unsigned char value)
{
	m_bfmeHolder->m_bfmeHead[0x230] = value;
}

void BfmeThingRE::bfmeRva007EA4D0SetHolderText(const char *text)
{
	Rva007E8640Copy((char *)&m_bfmeHolder->m_bfmeHead[0x90], 16, text);
}
