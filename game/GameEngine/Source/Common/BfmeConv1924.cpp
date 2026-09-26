class BfmeHostCL;

class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

class BfmeGateCL
{
public:
	void bfmeStopCL();
};

class BfmePathCL
{
public:
	void bfmeDropOneCL(BfmeHostCL *o);
	void bfmeDropTwoCL(BfmeHostCL *o);
};

class AI
{
public:
	unsigned char m_bfmeHeadCL[0xc];
	BfmePathCL *m_bfmePathCL;
};

extern AI *TheAI;

class BfmeHostCL
{
public:
	void bfmeResetCL(char full);

	unsigned char m_bfmeHeadCL[0x80];
	BfmeGateCL *m_bfmeGateCL;
	unsigned char m_bfmeMidCL[0x32c];
	PartitionData *m_bfmePartCL;
	Rva009F2BA0 *m_bfmeThirdCL;
	Rva009A2350 *m_bfmeSecondCL;
};

void BfmeHostCL::bfmeResetCL(char full)
{
	if (m_bfmePartCL != 0)
		m_bfmePartCL->makeDirty();

	if (m_bfmeSecondCL != 0)
		m_bfmeSecondCL->init();

	if (m_bfmeThirdCL != 0)
		m_bfmeThirdCL->init();

	if (m_bfmeGateCL != 0)
		m_bfmeGateCL->bfmeStopCL();

	if (full != 0)
	{
		TheAI->m_bfmePathCL->bfmeDropOneCL(this);
		TheAI->m_bfmePathCL->bfmeDropTwoCL(this);
	}
}
