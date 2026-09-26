// ?bfmeEachABM@@YGXPAVBfmeSinkABM@@@Z
// partial score=0.85 date=2026-09-09
extern char Rva006A16B0Empty[];

struct BfmeEntryABM
{
	unsigned char m_bfmeHeadABM[8];
	char m_bfmeNameABM[1];
};

struct BfmeNodeABM
{
	BfmeNodeABM *m_bfmeNextABM;
	unsigned int m_bfmeHashABM;
	unsigned char m_bfmeGapABM[0xc];
	BfmeEntryABM *m_bfme14ABM;
};

struct BfmeTableABM
{
	unsigned char m_bfmeHeadTABM[4];
	BfmeNodeABM **m_bfmeBucketsABM;
	BfmeNodeABM **m_bfmeEndABM;
};

struct BfmeIterABM
{
	BfmeNodeABM *m_bfmeNodeABM;
	BfmeTableABM *m_bfmeTableABM;
};

class BfmeSubBGC
{
public:
	void bfmeDoBGC(void *out);
};

struct BfmeOwnerABM
{
	unsigned char m_bfmeHeadOABM[8];
	BfmeSubBGC m_bfme08ABM;
};

extern BfmeOwnerABM *g_bfmeOwnerABM;

class BfmeSinkABM
{
public:
	virtual void bfmeVisitABM(const char *name);
};

void __stdcall bfmeEachABM(BfmeSinkABM *sink);

void __stdcall bfmeEachABM(BfmeSinkABM *sink)
{
	BfmeIterABM it;

	g_bfmeOwnerABM->m_bfme08ABM.bfmeDoBGC(&it);

	while (it.m_bfmeNodeABM != 0)
	{
		BfmeNodeABM *n = it.m_bfmeNodeABM;
		BfmeEntryABM *e = n->m_bfme14ABM;

		sink->bfmeVisitABM(e != 0 ? e->m_bfmeNameABM : Rva006A16B0Empty);

		BfmeNodeABM *nx = n->m_bfmeNextABM;

		if (nx == 0)
		{
			BfmeTableABM *t = it.m_bfmeTableABM;
			unsigned int b = n->m_bfmeHashABM % (unsigned int)(t->m_bfmeEndABM - t->m_bfmeBucketsABM);
			unsigned int cnt = (unsigned int)(t->m_bfmeEndABM - t->m_bfmeBucketsABM);

			nx = 0;

			for (++b; b < cnt; ++b)
			{
				BfmeNodeABM *c = t->m_bfmeBucketsABM[b];

				if (c != 0)
				{
					nx = c;
					break;
				}
			}
		}

		it.m_bfmeNodeABM = nx;
	}
}
