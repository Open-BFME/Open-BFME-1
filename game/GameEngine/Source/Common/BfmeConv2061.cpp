extern char *g_bfmeTwoSJA;

class BfmeNodeGE
{
public:
	BfmeNodeGE *volatile m_bfmeNextGE;
	int m_bfmeKeyGE;
	unsigned char m_bfmeGapGE[0x24];
	volatile char m_bfmeFlagGE;
};

class BfmeVecGE
{
public:
	int bfmeIndexGE(int *key, int n);

	unsigned char m_bfmeHeadGE[4];
	int m_bfmeBeginGE;
	int m_bfmeEndGE;
};

class BfmePairGE
{
public:
	BfmeNodeGE *m_bfmeNodeGE;
	BfmeVecGE *m_bfmeVecGE;
};

class BfmeSrcGE
{
public:
	BfmePairGE bfmeFirstGE();
};

static __forceinline BfmeNodeGE *bfmeNextGE(BfmeVecGE *v, BfmeNodeGE *p)
{
	BfmeNodeGE *q = p->m_bfmeNextGE;

	if (q != 0)
		return q;

	int *key = &p->m_bfmeKeyGE;
	int i = v->bfmeIndexGE(key, (v->m_bfmeEndGE - v->m_bfmeBeginGE) >> 2);
	int m = (v->m_bfmeEndGE - v->m_bfmeBeginGE) >> 2;
	BfmeNodeGE *r = 0;

	while ((unsigned int)++i < (unsigned int)m && (r = ((BfmeNodeGE **)*(volatile int *)&v->m_bfmeBeginGE)[i]) == 0)
		;

	return r;
}

void bfmeWalkGE()
{
	BfmePairGE it = ((BfmeSrcGE *)&g_bfmeTwoSJA)->bfmeFirstGE();
	BfmeNodeGE *p = it.m_bfmeNodeGE;

	if (p != 0)
	{
		BfmeVecGE *v = it.m_bfmeVecGE;

		do
		{
			p->m_bfmeFlagGE = 0;
			p = bfmeNextGE(v, p);
		}
		while (p != 0);
	}
}
