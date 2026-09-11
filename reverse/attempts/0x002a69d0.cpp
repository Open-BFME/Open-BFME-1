// ?bfmeFindFG@BfmeHostFG@@QAEPAVBfmeObjFG@@PBVBfmeThingFG@@@Z
// partial score=0.94 date=2026-09-08
class BfmeObjFG
{
public:
	unsigned char m_bfmeHeadFG[0x78];
	int m_bfmeIdFG;
};

class BfmeEntryFG
{
public:
	BfmeEntryFG *m_bfmeNextFG;
	unsigned int m_bfmeKeyFG;
	BfmeObjFG *m_bfmeObjFG;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadFG[0xb4];
	BfmeEntryFG **m_bfmeBeginFG;
	BfmeEntryFG **m_bfmeEndFG;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

class BfmeNodeFG
{
public:
	BfmeNodeFG *m_bfmeNextFG;
	unsigned char m_bfmeGapFG[4];
	unsigned int m_bfmeKeyFG;
};

class BfmeThingFG
{
public:
	unsigned char m_bfmeHeadFG[0x74];
	int m_bfmeIdFG;
};

class BfmeHostFG
{
public:
	BfmeObjFG *bfmeFindFG(const BfmeThingFG *t);

	unsigned char m_bfmeHeadFG[0xcc];
	BfmeNodeFG *m_bfmeListFG;
};

BfmeObjFG *BfmeHostFG::bfmeFindFG(const BfmeThingFG *t)
{
	BfmeNodeFG *head = m_bfmeListFG;

	for (BfmeNodeFG *n = head->m_bfmeNextFG; n != head; n = n->m_bfmeNextFG)
	{
		Rva00367E30Logic *g = *(Rva00367E30Logic *volatile *)&TheBfmeGameLogic;
		register unsigned int key = *(volatile unsigned int *)&n->m_bfmeKeyFG;

		if (key == 0)
			continue;

		unsigned int c = (unsigned int)(g->m_bfmeEndFG - g->m_bfmeBeginFG);
		BfmeEntryFG *e = g->m_bfmeBeginFG[key % c];

		while (e != 0 && e->m_bfmeKeyFG != key)
			e = e->m_bfmeNextFG;

		if (e == 0)
			continue;

		BfmeObjFG *o = e->m_bfmeObjFG;

		if (o == 0)
			continue;

		if (o->m_bfmeIdFG == t->m_bfmeIdFG)
			return o;
	}

	return 0;
}
