extern "C" __declspec(dllimport) long __stdcall bfmeDecESG(long *addend);

class BfmeSubESG
{
public:
	virtual void bfmeDropESG(int flag);

	long m_bfmeRefESG;
};

inline void bfmeKillESG(BfmeSubESG *sub)
{
	if (sub != 0)
		sub->bfmeDropESG(1);
}

class BfmeOwnerESG
{
public:
	unsigned char m_bfmeHeadESG[0x70];
	BfmeSubESG m_bfmeSubESG;
};

class BfmeRefESG
{
public:
	~BfmeRefESG()
	{
		if (m_bfmeOwnerESG != 0)
		{
			BfmeSubESG *sub = &m_bfmeOwnerESG->m_bfmeSubESG;

			if (bfmeDecESG(&sub->m_bfmeRefESG) <= 0)
				bfmeKillESG(sub);
		}
	}

	BfmeOwnerESG *m_bfmeOwnerESG;
};

class BfmeMemberESG
{
public:
	~BfmeMemberESG();

	unsigned char m_bfmeBodyESG[4];
};

class BfmeHostESG
{
public:
	~BfmeHostESG();

	unsigned char m_bfmeHeadESG[4];
	BfmeRefESG m_bfme04ESG;
	unsigned char m_bfmeMidESG[4];
	BfmeMemberESG m_bfmeMemberESG;
};

BfmeHostESG::~BfmeHostESG()
{
}
