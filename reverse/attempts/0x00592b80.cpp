// ?bfmeResetABO@BfmeHostABO@@QAEXXZ
// partial score=0.90 date=2026-09-09
struct BfmeCfgABO
{
	int m_bfme00ABO;
	int m_bfme04ABO;
	int m_bfme08ABO;
	int m_bfme0CABO;
	int m_bfme10ABO;
	unsigned char m_bfme14ABO;
	unsigned char m_bfme15ABO;
};

void bfmeApplyABO(void *a, unsigned char *b, BfmeCfgABO *cfg);

class BfmeSubABO
{
public:
	void bfmeResetABO();
};

class BfmeSub2ABO
{
public:
	void bfmeClearABO();
};

class BfmeStrABO
{
public:
	void bfmeReleaseABO();

	void *m_bfmeDataABO;
};

struct BfmePairABO
{
	int m_bfmeAABO;
	int m_bfmeBABO;
};

struct BfmeOtherABO
{
	unsigned char m_bfmeHeadABO[0x1f4];
	int m_bfme1F4ABO;
};

class BfmeHostABO
{
public:
	void bfmeResetABO();

	unsigned char m_bfmeH00[0xc];
	BfmeOtherABO *m_bfme0CABO;
	unsigned char m_bfmeH10[4];
	int m_bfme14ABO;
	unsigned char m_bfmeH18[0x4c - 0x18];
	unsigned char m_bfme4CABO;
	unsigned char m_bfmeH4D[0x58 - 0x4d];
	unsigned char m_bfme58ABO;
	unsigned char m_bfmeH59[0x60 - 0x59];
	int m_bfme60ABO;
	int m_bfme64ABO;
	unsigned char m_bfmeH68[0x154 - 0x68];
	BfmeSubABO m_bfme154ABO;
	unsigned char m_bfmeH155[0x2b8 - 0x155];
	unsigned char m_bfme2B8ABO;
	unsigned char m_bfmeH2B9[3];
	int m_bfme2BCABO;
	unsigned char m_bfme2C0ABO;
	unsigned char m_bfmeH2C1[0x458 - 0x2c1];
	unsigned char m_bfme458ABO;
	unsigned char m_bfmeH459[0x468 - 0x459];
	unsigned char m_bfme468ABO;
	unsigned char m_bfmeH469[3];
	int m_bfme46CABO;
	int m_bfme470ABO;
	int m_bfme474ABO;
	int m_bfme478ABO;
	unsigned char m_bfmeH47C[0x488 - 0x47c];
	BfmeSub2ABO m_bfme488ABO;
	unsigned char m_bfmeH489[0x4c8 - 0x489];
	int m_bfme4C8ABO;
	unsigned char m_bfmeH4CC[4];
	int m_bfme4D0ABO;
	unsigned char m_bfme4D4ABO;
	unsigned char m_bfmeH4D5[3];
	BfmeStrABO m_bfme4D8ABO;
	BfmePairABO m_bfme4DCABO[4];
};

void BfmeHostABO::bfmeResetABO()
{
	m_bfme14ABO = 0;
	m_bfme154ABO.bfmeResetABO();

	BfmeCfgABO cfg;

	m_bfme458ABO = 0;
	m_bfme2B8ABO = 0;

	cfg.m_bfme00ABO = m_bfme2BCABO;
	cfg.m_bfme04ABO = 0;
	cfg.m_bfme08ABO = -1;
	cfg.m_bfme0CABO = -1;
	cfg.m_bfme10ABO = -1;
	cfg.m_bfme14ABO = 0;
	cfg.m_bfme15ABO = 0;

	bfmeApplyABO(&m_bfme2C0ABO, &m_bfme458ABO, &cfg);

	m_bfme468ABO = 0;
	m_bfme478ABO = 0;

	m_bfme488ABO.bfmeClearABO();

	m_bfme46CABO = -2;
	m_bfme470ABO = -2;
	m_bfme474ABO = -2;
	m_bfme58ABO = (unsigned char)(m_bfme58ABO & 0xc4);
	m_bfme64ABO = 1;
	m_bfme4C8ABO = 0;
	m_bfme60ABO = -1;
	m_bfme4D4ABO = 0;
	m_bfme4D0ABO = -1;

	m_bfme4D8ABO.bfmeReleaseABO();

	BfmePairABO tmp;
	*(volatile int *)&tmp.m_bfmeAABO = 0;
	*(volatile int *)&tmp.m_bfmeBABO = 0;

	BfmePairABO *p = m_bfme4DCABO;
	BfmePairABO *end = m_bfme4DCABO + 4;

	while (p != end)
	{
		*p = tmp;
		++p;
	}

	m_bfme58ABO = (unsigned char)(m_bfme58ABO & 0x3f);

	if (m_bfme0CABO != 0)
		m_bfme0CABO->m_bfme1F4ABO = 0;

	m_bfme4CABO = 1;
}
