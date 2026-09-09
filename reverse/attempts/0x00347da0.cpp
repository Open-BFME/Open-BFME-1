// ?bfmeDumpCG@@YGXPAVBfmeSinkCG@@@Z
// partial score=0.99 date=2026-09-09
extern "C" char _bfmeEmptyCG[];

struct BfmeKeyCG
{
	unsigned char m_bfmeHeadCG[8];
	char m_bfmeTextCG[4];
};

struct BfmeNodeCG
{
	BfmeNodeCG *m_bfme00CG;
	BfmeKeyCG *m_bfme04CG;
};

class BfmeVecCG
{
public:
	int bfmeIndexCG(void *p, int n);

	unsigned char m_bfmeHeadCG[4];
	BfmeNodeCG **m_bfme04CG;
	BfmeNodeCG **m_bfme08CG;
};

struct BfmeIterCG
{
	BfmeNodeCG *m_bfmeNodeCG;
	BfmeVecCG *m_bfmeVecCG;
};

class BfmeTableCG
{
public:
	void bfmeFirstCG(BfmeIterCG *it);
};

class ParticleSystemManager
{
public:
	unsigned char m_bfmeHeadCG[0x9c];
	BfmeTableCG m_bfme9CCG;
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeSinkCG
{
public:
	virtual void bfmeEmitCG(const char *s);
};

void __stdcall bfmeDumpCG(BfmeSinkCG *sink)
{
	BfmeIterCG it;

	TheParticleSystemManager->m_bfme9CCG.bfmeFirstCG(&it);

	BfmeNodeCG *n = it.m_bfmeNodeCG;

	if (n == 0)
		return;

	BfmeVecCG *v = it.m_bfmeVecCG;

	void *last;
	unsigned int i;
	unsigned int count;

outerCG:
	const char *s = n->m_bfme04CG != 0 ? n->m_bfme04CG->m_bfmeTextCG : _bfmeEmptyCG;

	sink->bfmeEmitCG(s);

	last = &n->m_bfme04CG;

	n = n->m_bfme00CG;

	if (n != 0)
		goto outerCG;

	i = v->bfmeIndexCG(last, v->m_bfme08CG - v->m_bfme04CG);

	count = v->m_bfme08CG - v->m_bfme04CG;

	BfmeNodeCG *p = 0;

scanCG:
	++i;

	if (i < count)
	{
		p = (*(BfmeNodeCG **volatile *)&v->m_bfme04CG)[i];

		if (p == 0)
			goto scanCG;
	}

	n = p;

	if (n != 0)
		goto outerCG;
}
