class BfmeSubDUB
{
public:
	void bfmeCallDUB();
};

struct BfmeThingDUB
{
	void bfmeGoDUB();
	unsigned char m_bfmeHeadA[0x630];
	BfmeSubDUB m_bfmeA;
	unsigned char m_bfmeHeadB[0x1b];
	BfmeSubDUB m_bfmeB;
};

void BfmeThingDUB::bfmeGoDUB()
{
	m_bfmeA.bfmeCallDUB();
	m_bfmeB.bfmeCallDUB();
}

class BfmeSubDUC
{
public:
	void bfmeOneDUC();
};

class BfmeSubDUD
{
public:
	void bfmeTwoDUD();
};

struct BfmeThingDUC
{
	void bfmeGoDUC();
	unsigned char m_bfmeHeadA[0x104];
	BfmeSubDUC m_bfmeA;
	unsigned char m_bfmeHeadB[0x4f];
	BfmeSubDUD m_bfmeB;
};

void BfmeThingDUC::bfmeGoDUC()
{
	m_bfmeA.bfmeOneDUC();
	m_bfmeB.bfmeTwoDUD();
}
