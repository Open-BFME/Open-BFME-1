extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeItemEVE
{
public:
	virtual void bfmeSlot00EVE();
	virtual void bfmeSlot01EVE();
};

class BfmeBufEVE
{
public:
	__forceinline ~BfmeBufEVE()
	{
		if (m_bfmePtrEVE != 0)
			TheBfmeFree(m_bfmePtrEVE, m_bfmeCapEVE * 4);
	}

	int m_bfmeCapEVE;
	BfmeItemEVE **m_bfmePtrEVE;
};

class BfmeVecEVE
{
public:
	~BfmeVecEVE();

	unsigned char m_bfmeHeadEVE[0x14];
	int m_bfmeCountEVE;
	BfmeBufEVE m_bfmeBufEVE;
};

BfmeVecEVE::~BfmeVecEVE()
{
	for (int i = m_bfmeCountEVE; i > 0; i--)
	{
		m_bfmeBufEVE.m_bfmePtrEVE[m_bfmeCountEVE - 1]->bfmeSlot01EVE();
		m_bfmeCountEVE = m_bfmeCountEVE - 1;
	}
}
