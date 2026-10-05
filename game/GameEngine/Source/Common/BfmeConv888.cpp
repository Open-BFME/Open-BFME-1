struct BfmeGlobEYA
{
	unsigned char m_bfmeHead[0xbd0];
	void *m_bfmeP;
};

// EA's GlobalData (Common/GlobalData.h) is only forward declared here; this
// global is retail 0x012ED5C8, defined once in
// GameEngine/Source/Common/GlobalData.cpp, so it must be spelled
// GlobalData * (class, not struct) to mangle to the same name.  The local
// view above supplies the member this TU reads.
class GlobalData;

extern GlobalData *TheWritableGlobalData;
void *__cdecl bfmeMakeEYA(unsigned int a, unsigned int b);

int bfmeGoEYA()
{
	if (TheWritableGlobalData)
		reinterpret_cast<BfmeGlobEYA *>(TheWritableGlobalData)->m_bfmeP =
			bfmeMakeEYA(0xbaadec4c, 0xbaadec4c);
	return 1;
}

extern "C" char *bfmeTabEYC[];
extern "C" unsigned char bfmeStrAEYC[];
extern "C" unsigned char bfmeStrBEYC[];

const char *__stdcall bfmeGoEYC(int i)
{
	if (i >= 0 && i < 2)
		return bfmeTabEYC[i];
	return (i == -1) ? (const char *)bfmeStrAEYC : (const char *)bfmeStrBEYC;
}

struct BfmeNodeEYE
{
	void bfmeRunEYE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEYE *m_bfmeNext;
};

struct BfmeListEYE
{
	BfmeNodeEYE *m_bfmeHead;
};

// Retail VA 0x012ED5DC holds the map-list holder pointer.
// WorldHeightMap.cpp owns it; this use retains its local view.
class BfmeMapObjectListHolder;
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
extern void *g_bfmeCurEYE;

void __cdecl bfmeGoEYE(void *a)
{
	g_bfmeCurEYE = a;
	for (BfmeNodeEYE *n = reinterpret_cast<BfmeListEYE *>(BfmeTheMapObjectListHolder)->m_bfmeHead; n; n = n->m_bfmeNext)
		n->bfmeRunEYE();
}

struct BfmeNodeEYF
{
	unsigned char m_bfmeHead[4];
	BfmeNodeEYF *m_bfmeNext;
};

BfmeNodeEYF *__cdecl bfmeMakeEYF(void *a, void *b);

struct BfmeThingEYF
{
	bool bfmeGoEYF(void *a, void *b);
	unsigned char m_bfmeHead[0xc];
	BfmeNodeEYF *m_bfmeHead2;
};

bool BfmeThingEYF::bfmeGoEYF(void *a, void *b)
{
	BfmeNodeEYF *n = bfmeMakeEYF(a, b);
	if (n)
	{
		m_bfmeHead2->m_bfmeNext = n;
		m_bfmeHead2 = n;
	}
	return true;
}

struct BfmeNodeEYG
{
	BfmeNodeEYG *m_bfmeNext;
	BfmeNodeEYG *m_bfmePrev;
	void *m_bfmeVal;
};

void __cdecl bfmeFreeEYG(void *p, unsigned int n);

struct BfmeThingEYG
{
	void *bfmeGoEYG();
	unsigned char m_bfmeHead[4];
	BfmeNodeEYG *volatile m_bfmeL;
};

void *BfmeThingEYG::bfmeGoEYG()
{
	BfmeNodeEYG *l = m_bfmeL;
	if (l->m_bfmeNext == l)
		return 0;
	BfmeNodeEYG *n = m_bfmeL->m_bfmeNext;
	BfmeNodeEYG *nx = n->m_bfmeNext;
	BfmeNodeEYG *pv = n->m_bfmePrev;
	void *v = n->m_bfmeVal;
	pv->m_bfmeNext = nx;
	nx->m_bfmePrev = pv;
	bfmeFreeEYG(n, 0xc);
	return v;
}
